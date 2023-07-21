#include<iostream>

#include"thread.h"
#include<functional>



using namespace std;


// g++ test_thread.cc thread.h -o test_thread

// Thread name: print
// the number is0
// Thread has started.
// Thread has joined.

void print(int n){
    cout<<"the number is"<<  n<< '\n';
}


int main(){
    //     using ThreadFunc = function<void()>;

    // Thread(ThreadFunc, string name = string());
    int n = 0;
    Thread t(std::bind(print, n) , "print");
    cout << "Thread name: " << t.getName() << endl;    
    t.start();
    t.join();
 

    if (t.isStart()) {
        cout << "Thread has started." << endl;
    } else {
        cout << "Thread has not started." << endl;
    }

    if (t.isJoin()) {
        cout << "Thread has joined." << endl;
    } else {
        cout << "Thread has not joined." << endl;
    }


    return 0;
}