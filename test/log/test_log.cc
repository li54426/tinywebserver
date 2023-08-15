#include"log.h"

#include<iostream>
#include<string>


using namespace std;

//  g++ test_log.cc log.h log.cc ../buffer/buffer.cc -o  test_log
int main(){
    Log *log  = Log::GetInstance();
    
    log->Init(1 );
    cout<<"test get level"<< log-> GetLevel()<< endl;

    cout<< "test Write"<< '\n';
    log->Write(1, "%s %s", "test", "aaaa");
    LOG_INFO("%s %s", "test", "aaaa" );
    cout<< "after Write"<< '\n';
    cout<< "finished all the func"<< '\n';
    LOG_FATAL("test fatal");

    return 0;
}