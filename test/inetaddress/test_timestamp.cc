#include"timestamp.h"


#include<iostream>
using std::cout;

/*
g++ test_timestamp.cc timestamp.h -o t_timestamp
test tostring2023/07/20 11:30:49
test operator<0
*/



int main(){
    Timestamp tp= Timestamp::now();

    Timestamp tp2= Timestamp::now();

    cout<<"test tostring"<< tp.toString()<< '\n';
    cout<< "test operator<" << (tp< tp2 )<< '\n';
    return 0;
}


