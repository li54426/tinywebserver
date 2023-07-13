#include"log.h"

#include<iostream>
#include<string>


using namespace std;


int main(){
    Log *log  = Log::GetInstance();
    
    log->Init(1 );
    cout<<"test get level"<< log-> GetLevel()<< endl;

    cout<< "test Write"<< '\n';
    log->Write(1, "%s %s", "test", "aaaa");
    cout<< "after Write"<< '\n';
    log->FlushLogThread();
    log-> Flush();

    return 1;
}