
#include"log.h"

using namespace std;

Log::Log(){
    isAsync_ = false;
    writeThread_ = nullptr;
    pbq_ = nullptr;
    fp_ = nullptr;
    count_line_ = 0;
    max_line_ = 5000;
}


Log::~Log(){
    if(fp_){
        lock_guard<mutex> locker(mtx_);
        // qu_->close();
        Flush();
        fclose(fp_);
        fp_ = nullptr;
    }
}


void Log:: Flush(){
    // 有一点职责链的意思, 将任务分派出去?
    // if(isAsync_){
    //     // 做的动作, 通知消费者
    //     pbq_->flush();
    // }
    fflush(fp_);
    cout<< "after flush"<< '\n';
}


// 负责创建
Log * Log::GetInstance(){
    // C++11 标准规定了对局部静态变量的初始化必须是线程安全的。
    // 因此不需要加锁
    static Log inst;
    return & inst;
}


int Log::GetLevel(){
    lock_guard<mutex> locker(mtx_);
    return level_;
}

int Log::SetLevel(int level){
    lock_guard<mutex> locker(mtx_);

    return level_ = level;

}


int Log:: CreatLogFile(int file_num ){
    string filename = GetFileName(file_num);

    cout<< filename<< endl;

       
    lock_guard<mutex> locker(mtx_);
    if(fp_){
        Flush();
        fclose(fp_);
    }
    fp_ = fopen(filename.c_str(), "a");
    count_line_ = 0;

    assert(fp_!= nullptr);

    return 1;
}



string Log::GetFileName(int file_num){
    Mytime t ;
    string filename(path_ );
    filename+= '/';
    filename += t.GetString() ;
    filename += suffix_;
    if(file_num){
        filename +=to_string(file_num);
    }
    return filename;
}


// 负责修改 Log
void Log::Init(int level, const char* path, const char* suffix, int maxQueueCapacity){
    isOpen_ = true;
    level_ = level;
    path_ = path;
    suffix_ = suffix;

    if(maxQueueCapacity > 0){
        isAsync_=true;
        if(!pbq_){
            cout<< "path_="<< path_<<"\tsuffix_="<< suffix_<< '\n'; 
            cout<< "make_unique"<< endl;
            pbq_ = make_unique<BlockQueue<std::string> >();
            writeThread_ = make_unique<std::thread>(FlushLogThread);
            // thread t(GetInstance);
            cout<< "afer make unique"<< '\n';

            if(!pbq_ || !writeThread_){
                cout<< "nullptr"<< '\n';
            }
            assert(pbq_ && writeThread_);
            cout<< "after assert"<< endl;
        }
    }
    else{
        isAsync_ = false;
    }

    Mytime t ;
    // cout<< "path_="<< path_<<"\tsuffix_="<< suffix_<< '\n'; 
    string filename = GetFileName();
    cout<<"filename = "<<  filename<< endl;
    today_ = t.GetDay();
    cout<< "today_ = "<< today_<< '\n';

    cout<< "run the init "<< '\n';
    CreatLogFile(0);
    cout<< "run the creat "<< '\n';

}


void Log::Write(int level, const char* format, ...){
    cout<< format<< endl;
    va_list valist;
    va_start(valist, format);
    Mytime t;
    if(today_ != t.GetDay() || count_line_ % max_line_ == 0){
        int num = count_line_ / max_line_;
        CreatLogFile(num);
    }
    cout<< t.GetString()<< '\n';
    cout<< t.GetStringSec()<< '\n';
    // 三部分文件信息, 时间, 级别, 具体的信息
    buff_.Append(t.GetStringSec());
    cout<< "getsec="<< t.GetStringSec()<< '\n';
    AppendLogLevelTitle_(level);
    
    int m = vsnprintf(buff_.BeginWrite(), buff_.WriteableBytes(), format, valist);
    buff_.HasWrite(m);
    cout<< "输入了"<< m<<'\n';
    va_end(valist);


    lock_guard<mutex> locker(mtx_);
    if(isAsync_ && !pbq_-> full()){
        string s= buff_.RetrieveAllToStr();
        cout<< "the str = "<< s<< endl;
        pbq_-> push(s);
        cout<< "after push size = "<< pbq_->size()<< '\n';
    }
    else{
        fputs(buff_.Peek(), fp_);
    }   

    buff_.RetrieveAll();


}



void Log::AppendLogLevelTitle_(int level) {
    switch(level) {
    case 0:
        buff_.Append("[debug]: ", 9);
        break;
    case 1:
        buff_.Append("[info] : ", 9);
        break;
    case 2:
        buff_.Append("[warn] : ", 9);
        break;
    case 3:
        buff_.Append("[error]: ", 9);
        break;
    default:
        buff_.Append("[info] : ", 9);
        break;
    }
}

void Log:: AsyncWriteLog_(){
    string single_log ;
    while(pbq_->pop(single_log) ){
        cout<< "the line str="<< pbq_->size();
        lock_guard<mutex> locker(mtx_);
        fputs(single_log.c_str(), fp_);
        cout<< "after fputs"<< endl;
        Flush();

    }
}

void Log::FlushLogThread() {
    Log::GetInstance()->AsyncWriteLog_();
}