#ifndef LOG_H

#define LOG_H
#include"blockqueue.h"
#include "../buffer/buffer.h"
#include<mutex>
#include<memory>
#include<thread>
#include<chrono>
#include<cassert>
#include<cstdarg>
#include"mytime.h"

using namespace std;

class Log{
public:
    static Log* GetInstance();
    // 刷新日志线程
    static void FlushLogThread();

    void Init(int level=1, const char* path = "./log", 
        const char * suffix = ".log", int maxQueueCapacity = 1024);
    void Write(int level, const char * format,...);
    int GetLevel();
    int SetLevel(int level);

    // 单例模式
    // Log() = delete;
    Log(const Log &) = delete;
    Log & operator=(const Log &) = delete;
    void Flush();
    ~Log();

    

private:
    // functions
    Log();
    void AsyncWriteLog_();
    void AppendLogLevelTitle_(int level);
    int CreatLogFile(int file_num = 0);
    string GetFileName(int file_num = 0);


private:
    int level_;
    bool isAsync_;
    bool isOpen_;

    int today_;

    int count_line_;
    int max_line_ ;


    Buffer buff_;
    unique_ptr<BlockQueue<std::string> > pbq_;
    unique_ptr<thread> writeThread_;

    FILE * fp_;

    

    // static *Log 
    mutex mtx_;
    static const int LOG_PATH_LEN = 256;
    static const int LOG_NAME_LEN = 256;
    static const int MAX_LINES = 50000;
    const char* path_;
    const char* suffix_;

};







#endif