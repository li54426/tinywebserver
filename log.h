#ifndef LOG_H

#define LOG_H
#include"blockqueue.h"
// #include "../buffer/buffer.h"
#include"buffer.h"
#include<mutex>
#include<memory>
#include<thread>
#include<chrono>
#include<cassert>
#include<cstdarg>
#include"mytime.h"

#include"timestamp.h"

using namespace std;

// class BlockQueue<std::string>;

/**
 * 使用单例模式的日志实现
 * 使用 LOG(formate, ...), LOG_INFO, 等级别的日志系统
 * 
 * 自动添加 等级 和 时间信息
 * 只需要关注我们想写入的 字符串
 * 
 * 支持异步日志
 * 当 设置 maxQueueCapacity <= 0 的时候 为异步日志
 **/


// 定义日志的级别  DEBUG  INFO  ERROR  FATAL 
// 等级越高越是问题
enum LogLevel
{
    DEBUG, // 调试信息
    INFO,  // 普通信息
    ERROR, // 错误信息
    FATAL, // core信息
            // "core 信息" 有可能指的是 "core dump"（核心转储）的信息。
            // 核心转储是指在程序异常终止（如崩溃）时，将整个内存状态保存到一个文件中的操作。
            // 这个文件称为核心转储文件，它包含了导致程序异常终止的位置、变量值等调试相关信息。

};





// 先到 buffer中, 再从buffer-> bqu -> file

class Log{
public:
    // 单例模式
    // Log() = delete;
    Log(const Log &) = delete;    
    static Log* GetInstance();
    // 刷新日志线程
    // static void FlushLogThread();

    void Init(int level=1, const char* path = "./log", 
        const char * suffix = ".log", int maxQueueCapacity = 1024);

    // 写入日志, 先写入 level
    // 添加时间戳
    // 然后再将格式化的字符串写入
    void Write(int level, const char * format,...);
    int GetLevel();
    int SetLevel(int level);


    Log & operator=(const Log &) = delete;
    // void Flush();
    ~Log();

    

private:
    // functions
    Log();
    void AsyncWriteLog_();

    // add the level to buffer,
    void AppendLogLevelTitle_(int level);

    int CreatLogFile(int file_num = 0);
    string GetFileName(int file_num = 0);


private:
    // 默认工作在哪一级别
    int level_;
    bool isAsync_;
    bool isOpen_;

    int today_;

    int count_line_;
    int max_line_ ;

    // 替代 char *
    Buffer buff_;
    unique_ptr<BlockQueue<std::string> > pbq_;
    unique_ptr<thread> writeThread_;

    FILE * fp_;

    

    // static *Log 
    mutex fileptr_mtx_;
    static const int LOG_PATH_LEN = 256;
    static const int LOG_NAME_LEN = 256;
    static const int MAX_LINES = 50000;
    const char* path_;
    const char* suffix_;

};


// -----------宏定义---------
// 使用形式
//  LOG::INFO()


// 自动添加 等级 和 时间信息
// 只需要关注我们想写入的 字符串

#define LOG_BASE(base, logmsg_format, ...)\
do{\
    Log * log = Log::GetInstance();\
    log->Write(base, logmsg_format, ##__VA_ARGS__);\
}while(0);


#define LOG_INFO(logmsg_format, ...) LOG_BASE(INFO, logmsg_format, ##__VA_ARGS__) ;


// #define LOG_DEBUG(logmsg_format, ...)\
// do{\
//     Log * log = Log::GetInstance();\
//     log->Write(DEBUG, logmsg_format, ##__VA_ARGS__)\
// }while(0);


#define LOG_ERROR(logmsg_format, ...) LOG_BASE(ERROR, logmsg_format, ##__VA_ARGS__);
#define LOG_FATAL( logmsg_format, ...)\
do{\
    Log * log = Log::GetInstance();\
    log->Write(FATAL, logmsg_format, ##__VA_ARGS__);\
    exit(-1);\
}while(0);



#define MUDEBUG

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...)  LOG_INFO(logmsgFormat, ##__VA_ARGS__)
#else
    #define LOG_DEBUG(logmsgFormat, ...)
#endif






#endif