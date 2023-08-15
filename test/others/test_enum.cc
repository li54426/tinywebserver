#include<iostream>


// g++ test_enum.cc -o test_enum

enum Color{
    RED,
    GREEN,
    BULE,
};


int main(){
    Color c = RED;
    std::cout<< c<< '\n';
    if(c == 0){
        std::cout<< "c == 0"<< '\n';
    }
    return 0;
}