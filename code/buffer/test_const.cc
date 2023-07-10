
#include<iostream>

const char *getString() {
    char *message = "Hello";
    return message;  // 正确，返回指向只读字符串的常量指针
}

void test_const(){
    char c = '0';
    const char* cc1 = &c;
    std::cout<< "const char *="<< *cc1<< '\n'; 

    std::cout<< "test const"<< std::endl; 
    char data[10]="assfgsdfg";
    const char * cc = data+2;
    std::cout<< cc<< '\n';

    // std::cout<<
    
}



int main(){
    test_const();
    const char * c = getString();
    std::cout<< c<< '\n';
    return 0;
}