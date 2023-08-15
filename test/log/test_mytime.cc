#include<iostream>

#include"mytime.h"

//  g++ test_mytime.cc -o test_mytime
// ./test_mytime
// 2023 7 13
// 2023_7_13
// 2023_7_13 19:3:14

int main(){
    Mytime m;
    std::cout<< m.GetYear()<<' '<< m.GetMon()<< ' '<< m.GetDay()<< "\n";
    std:: cout<< m.GetString()<< '\n';
    std::cout<< m.GetStringSec()<< '\n';
}