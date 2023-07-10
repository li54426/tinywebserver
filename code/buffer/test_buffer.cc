#include"buffer.h"
#include<unistd.h>
#include<fcntl.h>
#include<string>
#include<iostream>


int main(){
    Buffer buffer;
    int fd = open("./test", O_CREAT|O_RDWR, 0644);
    if(fd <=0 ){
        std::cout<< "unsuccess"<< '\n';
    }
    std::cout<< "fd = "<< fd<< '\n';
    std::string s (5000, 'a');
    
    for(int i = 0; i<10; ++i){
        std::cout<< s[i]<< ' ';
    }
    std::cout<< '\n';
    char *  a = static_cast<char*> (s.data() );
    buffer.Append(a, 10);



    for(int i =10; i<15; ++i){
        *(const_cast<char*> (buffer.Peek() +i))  = 'b';
    }

    std::cout<< "test_buffe=r"<< '\n';



    for(int i =0; i<15; ++i){
        
        std::cout<< *(buffer.Peek() +i)<< ' ';
    }
    std::cout<<'\n';


    int saveError = 0;
    int writesize = buffer.WriteFd(fd, &saveError);
    std::cout<< "write size ="<< writesize<< '\n';

    // 文件读写时要注意 偏移量在哪
    off_t offset = lseek(fd, 0, SEEK_SET); 
    int c = buffer.ReadFd(fd, &saveError);

    std::cout<< "buffer can read"<< c<< '\n';

    close(fd);
    return 0;
}
