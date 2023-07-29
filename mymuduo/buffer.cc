#include "buffer.h"
#include<cassert>
#include<unistd.h>

#include<sys/uio.h>

Buffer::Buffer(int initsize ):
    buffer_(initsize), readPos_(0), writePos_(0){}

size_t Buffer::ReadableBytes()const{
    return writePos_ - readPos_;
}

size_t Buffer::writeableBytes()const{
    return buffer_.size()-writePos_;
}

size_t Buffer::PrependableBytes() const{
    return readPos_;
}

char *Buffer:: BeginPtr() {
    return &*buffer_.begin();
}


const char* Buffer::Peek(){
    return (BeginPtr() + readPos_);
}

char * Buffer::BeginWrite(){
    char * res = BeginPtr() + writePos_;
    return res;
}


/// @brief 进行调整, 将已经读入的内容向前移动
/// @param len 
void Buffer::MakeSpace_(size_t len){
    if(PrependableBytes() + writeableBytes() >=len){
        std::copy(BeginPtr()+ readPos_, BeginPtr()+ writePos_, BeginPtr());
        writePos_ =writePos_- readPos_ ;
        readPos_ = 0;

        //sssert(ReadableBytes() == )
        
    }
    else{
        // 请求空间
        buffer_.resize(writePos_ + len +1);
    }
}

void Buffer::EnsureWriteable(size_t len){
    if(len> writeableBytes()){
        MakeSpace_(len);
    }
    assert(len<= writeableBytes());
}




void Buffer::Append(const char* s, size_t len){
    assert(s);
    EnsureWriteable(len);
    std::copy(s, s+len, BeginWrite());
    writePos_ +=len;

}

void Buffer::Append(void * p, size_t len){
    Append(static_cast<char*> (p), len);
}


void Buffer::Append(const std::string &str){
    Append(str.data(), str.size());
}

size_t Buffer::WriteFd(int fd, int * saveErrno){
    size_t readSize = ReadableBytes();
    int len = write(fd, Peek(), readSize);
    if(len<0 ){
        *saveErrno = errno;
        return len;
    }
    else{
        readPos_ += len;
        return len;
    }
}

size_t Buffer::ReadFd(int fd, int *saveErrno){
    char buff[65535];
    struct iovec iov[2];
    
    size_t writeable =  writeableBytes() ;
    iov[0].iov_base = BeginWrite();
    iov[0].iov_len = writeable;
    iov[1].iov_base = buff;
    iov[1].iov_len = 65536;

    int len = readv(fd, iov, 2);

    if(len <0){
        *saveErrno = errno;
    }
    else if(len <= writeable ){
        writePos_ += len;
    }
    else{
        writePos_ = buffer_.size();
        Append(buff, len - writeable);
    }
    return len;

}

void Buffer::Retrieve(int n){
    readPos_ += n;
}



void Buffer::RetrieveAll(){
    memset(&buffer_[0], 0, buffer_.size());
    readPos_ = 0;
    writePos_ = 0;
}


std::string Buffer::RetrieveAllToStr(){
    std::string str(Peek(), ReadableBytes());
    RetrieveAll();
    return str;

}

void Buffer:: HasWrite(int n){
    if(writeableBytes() >= n){
        writePos_ += n;
    }

    else{
        MakeSpace_(n);
    }
    assert(writeableBytes() >= n);
}