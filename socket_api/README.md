## socket_ api

这是对 `linux` 环境下 socket api 的尝试 

#### 0.1 网络资源

- [riba2534/TCP-IP-NetworkNote: 📘《TCP/IP网络编程》(韩-尹圣雨)学习笔记 (github.com)](https://github.com/riba2534/TCP-IP-NetworkNote)
- [qinguoyi/TinyWebServer: :fire: Linux下C++轻量级WebServer服务器 (github.com)](https://github.com/qinguoyi/TinyWebServer)
- [markparticle/WebServer: C++ Linux WebServer服务器 (github.com)](https://github.com/markparticle/WebServer)





什么是套接字

- 套接字是**网络数据传输**用的**软件**设备.
- 所谓套接字 (Socket)，就是对网络中不同主机上的应用进程之间进行双向通信的**端点的抽象**。一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制
- 在 `linux`的视角中, 套接字也是文件, 会有文件的创建, 打开, 关闭操作



socket提供了流 (stream) 和数据报(datagram) 两种通信机制,即流socket和数据报socket.

- **流socket基于TCP协议**,是一个有序、可靠、双向字节流的通道,传输数据不会丢失、不会重复、顺序也不会错乱.  用的多的是 **TCP**
- **数据报socket基于UDP协议**, 不需要建立和维持连接,可能会丢失或错乱.UDP不是一个可靠的协议,对数据的长度有限制,但是它的效率比较高. 







#### 常用 系统 头文件

- `unistd.h` 是一个 C 语言标准库头文件，定义了一些与**操作系统交互**的函数和符号常量。它提供了对 POSIX 操作系统 API 的访问。

    1. 系统调用（System Calls）：例如 `fork()`、`exec()`、`pipe()`、`dup()`、`chdir()` 等。
    2. 标准 I/O（Standard I/O）：例如 `read()`、`write()`、`close()`、`lseek()` 等。
    3. 基本数据类型和符号常量：例如 `NULL`、`STDIN_FILENO`、`STDOUT_FILENO`、`EXIT_SUCCESS`、`EXIT_FAILURE` 等。

- `<arpa/inet.h>` 是一个 C 语言标准库头文件，它提供了一些用于网络编程的**函数**和宏定义，特别是与 IP 地址和端口号之间的**转换相关**的功能。

    - 当需要 IP地址 的时候就需要引入该头文件
    - 具体来说，`<arpa/inet.h>` 头文件定义了一些用于 IPv4 和 IPv6 地址转换的函数，如 `inet_addr()`、`inet_ntoa()`、`inet_aton()`、`inet_ntop()` 和 `inet_pton()`。这些函数用于将 IP 地址字符串和二进制 IP 地址之间进行转换。
    - 此外，`<arpa/inet.h>` 还定义了网络字节序（Network Byte Order）和主机**字节序**（Host Byte Order）之间的转换函数，如 `ntohl()`、`ntohs()`、`htonl()` 和 `htons()`。这些函数用于处理网络字节序和主机字节序之间的差异。

- `stdlib.h` 是 C 语言标准库（Standard Library）中的一个头文件，提供了一些常用的函数和类型定义。在 C 语言中，该头文件通常与 `<stdio.h>` 和 `<string.h>` 等头文件一起使用。

    `stdlib.h` 包含了一些重要的函数原型和宏定义，其中一些是：

    - **内存**管理函数：`malloc()`、`calloc()`、`realloc()` 和 `free()`，用于动态内存的分配和释放。
    - 数字转换函数：`atoi()`、`atol()`、`atof()` 和 `strtol()`，用于将字符串转换为相应的数字类型。
    - 伪随机数函数：`rand()` 和 `srand()`，用于生成伪随机数。
    - **进程**控制函数：`exit()`、`system()` 和 `abort()`，用于程序的终止和进程控制。
    - 字符串转换函数：`itoa()`、`ltoa()` 和 `utoa()`，用于将数字转换为字符串。
    - 常用工具函数：`abs()`、`labs()` 和 `fabs()`，用于取绝对值。









#### 常用 C 库函数

- 什么是`FILE`:`FILE` 是在 C 语言中用于执行**文件输入和输出**操作的数据类型。它是由标准库 **stdio.h** 提供的一种结构体类型。

    `FILE` 结构体表示一个文件流，在程序中用于读取和写入文件。通过打开文件时返回的文件指针（指向 `FILE` 结构体的指针），可以使用各种文件操作函数来进行读取和写入操作。

- `fflush()` 是 C 标准库中的一个函数，用于刷新流的缓冲区。它的作用是将缓冲区中的内容立即写入到相应的输出流，确保数据及时地被写入到目标设备或文件中。

    在默认情况下，C 标准库会对输出流进行**缓冲**，即先将要输出的数据暂存在缓冲区中，然后根据需要将缓冲区的内容刷新到文件或设备上。这种缓冲机制提高了 I/O 的性能，因为批量写入比逐个字节写入更高效。

    但有时，我们需要立即将缓冲区中的数据写入到文件或设备中，而不是等待缓冲区满或程序结束时自动刷新。这时就可以使用 `fflush()` 函数来手动刷新流的缓冲区。

```c++
// fflush() 是 C 标准库函数，用于刷新流的缓冲区。
#include <stdio.h>
int fflush(FILE* stream);
// 它会返回一个非负值表示成功，返回 EOF（-1）表示失败。

// 用于打开文件并返回一个文件指针，以便后续对文件进行读取或写入操作。
FILE* fopen(const char* filename, const char* mode);
// "r"：只读模式，打开一个已存在的文本文件。如果文件不存在，打开失败。
// "w"：写入模式，创建一个新的文本文件。如果文件已存在，则清空文件内容。
// "a"：追加模式，在已有文本文件末尾添加新内容。如果文件不存在，创建一个新的文本文件。
// "rb"：二进制只读模式，类似于 "r"，但用于打开二进制文件。
// "wb"：二进制写入模式，类似于 "w"，但用于打开二进制文件。
// "ab"：二进制追加模式，类似于 "a"，但用于打开二进制文件。



// 将一个以 null 终止的字符串写入到文件中。如果出现错误，返回值为 EOF。
# include<stdio.h>
int fputs(const char *str, FILE *stream);

// 将一个字符写入到文件中。如果出现错误，返回值为 EOF。
int fputc(int c, FILE *stream);


#include<stdio.h>
// 文件操作的逻辑
FILE *fp = fopen("receive.txt", "wb");

fwrite((void *)buf, 1, read_cnt, fp);
fclose(fp);
```



```c++
// 将内存块中的每个字节都设置为 该值
# include <string.h>
void *memset(void *ptr, int value, size_t num);
// ptr：指向要设置值的内存块的指针。
// value：要设置的值，以整数形式表示。
// num：要设置的字节数。
memset(str, 'A', sizeof(str));


// 返回值是一个 size_t 类型的整数，表示字符串的长度（不包括终止空字符 '\0'）
size_t strlen(const char *str);
// 相同时，返回值为 0；
// 如果第一个字符串小于第二个字符串，返回一个负值；如果第一个字符串大于第二个字符串，返回一个正值。

int strcmp(const char *str1, const char *str2);

// 终止程序的执行并返回到操作系统。
#include<stdlib.h>
void exit(int status);

// 将字符串（ASCII 字符串）转换为相应的整数值
int atoi(const char *str);




```









```c++
// 确保一个特定的条件为真
// 为假时, 停止程序运行, 并在标准错误流输出有关错误的相关信息。
#include <cassert>

int divide(int a, int b) {
    assert(b != 0);  // 断言 b 不为0
    return a / b;
}

int main() {
    int result = divide(10, 0);
    return 0;
}

```









#### 常用的系统调用函数

- 在 Linux 世界里, **socket** 也被认为是**文件的一种**,因此在网络数据传输过程中自然可以使用文件I/O的相关函数.
- Windows 则与Linux**不同**, 是要**区分**socket和文件的.因此在Windows中需要调用特殊的数据传输相关函数.



在linux中, **文件描述符**是系统分配给文件或套接字的**整数**, 事实上, 文件描述符只不过是为了方便称呼操作系统创建的文件或套接字而赋予的数而已.

| 打开模式 | 含义                      |
| -------- | ------------------------- |
| O_CREAT  | 必要时**创建**文件        |
|          |                           |
| O_TRUNC  | 删除全部现有数据          |
| O_APPEND | 维持现有数据,保存到其后面 |
|          |                           |
| O_RDONLY | 只读打开                  |
| O_WRONLY | 只写打开                  |
| O_RDWR   | 读写打开                  |

```c++
// -----------------linux下的文件操作--------------
// Linux中套接字也是文件,因而可以通过文件I/O函数read和write进行数据传输.

// 打开文件, 成功返回文件描述符, 失败返回-1
int open(const char *path, int flag);
//* flag是文件打开模式信息, 如需传递多个参数,则应通过位或运算符组合并传递
//* fd=open("data.txt",O_CREAT|O_WRONLY|O_TRUNC);

// 关闭文件 成功返回0, 失败返回-1
int close(int fd);
// fd 是文件描述符

// 写入文件
ssize_t write(int fd, const void*buf, size_t nbytes);
// buf 是保存要 传输数据 的缓冲地址
// nbytes 要传输数据的字节数

// 读取文件
ssize_t read(int fd, void* buf, size_t nbytes);
// 成功返回接受的系结束, 时代返回-1, 遇到我那件结尾返回0
// buf 要保存 接受数据 的缓冲地址
```





```c++
// 从 buff 写入文件 fd 
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
// 如果成功读取到数据，则返回实际读取的字节数。
// 如果已到达文件末尾（EOF），则返回 0。
// 如果出现错误，则返回 - 1，并设置相应的错误码。



// 查找文件的读写位置
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);



// 设置文件读写位置
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
// offset：偏移量，可以是正数、负数或零，表示相对于 whence 参数所指定的位置的偏移量。
// whence：用于确定偏移量的参考位置，可以是以下值之一：
//	SEEK_SET：从文件起始位置开始计算偏移量。
//	SEEK_CUR：从当前文件位置开始计算偏移量。
//	SEEK_END：从文件末尾位置开始计算偏移量。

#include <sys/uio.h>
// 将数据从文件描述符 fd 关联的文件中读取，并按照 iov 数组中每个元素所指定的缓冲区位置和大小进行聚集读取。
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
//  iovcnt 是数组长度


#include <sys/uio.h>
struct iovec {
    void *iov_base; // 数据缓冲区起始地址
    size_t iov_len; // 数据缓冲区大小（字节数）
};

```



`read()` 函数会**持续读取**数据，直到满足以下任一条件：

1. 读取到**指定的字节数**。即使数据中存在空格或其他特殊字符，只要读取的字节数达到指定长度，`read()` 函数就会返回。
2. **到达文件末尾**。如果读取到文件末尾，则 `read()` 函数会读取剩余可读字节数，并返回实际读取的字节数，此时无论是否存在空格都不会停止读取。
3. 遇到错误。当发生错误时（如读取错误、文件描述符关闭等），`read()` 函数会返回 - 1，并设置相应的错误码。



`write()` 函数在遇到空格或换行符时**不会停止写入**数据，它会将这些字符视为普通的数据进行写入。

`write()` 函数**只关心写入数据的字节数，不会对数据进行解释或处理。**它将缓冲区中的数据按字节写入文件描述符，不会对其中的特殊字符进行特殊处理，包括空格和换行符。

空格字符（空格键）和换行符（回车键或换行键）实际上是普通字符的一种，它们都会被视为普通数据写入文件。只有在特定的上下文中，例如文本编辑器或终端中，这些字符才具有特殊的控制作用。

因此，`write()` 函数在执行写入操作时不关注字符的类型，无论是空格、换行符还是其他字符，它都会按字节将数据写入文件描述符，直到满足指定的写入字节数或发生错误为止。







#### 可变参数

- 递归实现, 直到可变参数全部没有

```c++
#include <iostream>

// 结束条件：当没有参数时停止递归调用
void print() {
    std::cout << std::endl;
}

// 递归调用：打印当前参数并继续处理剩余参数
template<typename T, typename... Args>
void print(T value, Args... args) {
    std::cout << value << ' ';
    print(args...);
}

int main() {
    print(1, 2, "Hello", 3.14);
    return 0;
}

```



```c++
#include <cstdarg>

void va_start(va_list ap, last_arg);
// ap：va_list 对象，用于表示变量参数列表。
// last_arg：最后一个已知的参数，用于确定变量参数列表的起始位置。

// 获得对象
type va_arg(va_list ap, type);
// ap：va_list 对象，用于表示变量参数列表。
// type：需要从变量参数列表中获取的参数的类型。

// 清理和结束使用 va_list 对象
void va_end(va_list ap);

// 函数返回实际写入的字符数（不包括结尾的 null 字符），或者在发生错误时返回负数。
int vsnprintf(char* buff, size_t size, const char* format, va_list ap);
// size：目标缓冲区的大小（包括结尾的 null 字符），用于限制写入的字符数，以防止缓冲区溢出。
// format：格式化字符串，指定了输出的形式。
// ap： va_list 对象，包含了可变参数列表。
// int result = vsnprintf(buffer, sizeof(buffer), "%s, %d", str, num);

#include <iostream>

int sum(int count, ...) {
    int total = 0;

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        int value = va_arg(args, int);
        total += value;
    }

    va_end(args);

    return total;
}

void printFormattedString(const char* format, ...) {
    char buffer[100];

    // 初始化 va_list 对象
    va_list args;
    va_start(args, format);

    // 使用 vsnprintf() 格式化可变参数列表为一个字符串
    int result = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args); // 结束参数列表的处理

    if (result >= 0 && result < sizeof(buffer)) {
        printf("Formatted string: %s\n", buffer);
    } else {
        printf("Error occurred during formatting.\n");
    }
}
```





#### linux常用命令

```bash
# 历史命令
箭头上下懂
使用 !! 符号：输入 !! 即可重新运行最近一次执行的命令。这对于快速重新运行上一条命令非常方便。
用 !-n 符号：其中 n 表示倒数第 n 条命令。例如，!-2 表示重新运行倒数第二条命令


# 进入 文件夹
cd 

# 查看所有文件
ls

# 显示当前路径
pwd

# 创建文件夹
mkdir

# 创建文件
touch filename

#删除文件
rm filename


################ 网络相关 #####################
# 获取IP地址
ifconfig
ip a

# 如果想要了解某个域名对应的信息
ping www.baidu.com
# PING www.a.shifen.com (182.61.200.6) 56(84) bytes of data.
# 打开 ip , 确实是 百度

# 下载文件
 wget https://images2015.cnblogs.com/blog/90573/201512/90573-20151230150659854-913603511.jpg


################ 编译相关 #####################
# 编译c文件
gcc filename.c -o output

# 运行程序
./filename



################ 进程相关 #####################
# 显示所有进程
ps au
```



gdb 命令

```bash
gdb -v 
```





