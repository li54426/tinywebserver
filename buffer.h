#ifndef BUFFER_H
#define BUFFER_H
#include <cstddef> // 为了引入size_t
#include<string>
#include<vector>
#include<atomic>
#include<cstring>

class Buffer{
public:
    Buffer(int initsize = 1024);
    ~Buffer() = default;
    size_t writeableBytes()const;
    size_t  ReadableBytes() const;
    size_t PrependableBytes()const;

    const char* Peek();
    const char* BeginWriteConst()const;
    char * BeginWrite();

    void Append(const std:: string& str);
    void Append(const char*str, size_t len);
    void Append(void * str, size_t len);
    void Append(Buffer & buffer);

    void HasWrite(int n);

    void EnsureWriteable(size_t len);
    
    size_t ReadFd(int fd, int *saveErrno);
    size_t WriteFd(int fd, int *savaError);
    void RetrieveAll();
    std::string RetrieveAllToStr();


private:
    // 一定记得写 std
    std::vector<char> buffer_;
    // 不知道有什么作用
    std:: atomic<std::size_t> readPos_, writePos_;

    char* BeginPtr();
    void MakeSpace_(size_t len);
    
    
};






#endif