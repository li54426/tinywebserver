# tinywebserver

本项目分三部分
- 首先实现一个线程池`ThreadPool`
- 其次实现网络库`NetLib`
- 最后实现上层的`webserver`



其他项目

- [衍生项目, 剖析muduo源码(未做)]()
- [设计模式](https://github.com/li54426/Design_patterns_cpp)
- [STL笔记](https://github.com/li54426/STL_Notes)
- [c语言]()


[note: ] 不到100行的代码就只有一个`.h`文件, 就直接在头文件中实现
[note2: ]只有.h 文件，没有.cc 文件，cmake 默认忽略么, 所以上一条忽略. 因此添加了一个章节 声明和定义分离的好处







muduo 库中的线程池并不是传统意义上的线程池。muduo 库的线程池使用了一个线程池汇总器（ThreadPool），其中包含一个任务队列和一组线程，这些线程是动态增长和缩减的。当提交一个任务时，线程池会根据当前负载情况自动创建或销毁线程来执行任务，以充分利用系统资源。

线程池**实现**可以看`./thread_pool`文件夹



### 0 代码风格
- [C++ 风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)
- Cpplint 是一个 Python 脚本，作为一款开源免费的代码静态检测工具，Google 也使用它作为自己的 C++ 代码检测工具，也就是说，只要你想代码遵从 Google C++ 代码规范，那么 Cpplint 将会提供很好的代码静态检测支持。


#### 1. 命名规则

- **文件名要全部小写**, 可以包含下划线 (\_) 或连字符 (-), 依照项目的约定. 如果没有约定, 那么“_”更好.
- **内联函数**必须放在 .h 文件中. 如果内联函数比较短, 就直接放在 .h 中.
- 
- **类名**称的每个单词**首字母均大写**, 不包含下划线: 形如`MyExcitingClass`, MyExcitingEnum.
- **变量** (包括函数参数) 和数据成员名一律小写, 单词之间用下划线连接. 类的成员变量以下划线结尾,
- **常量** 声明为 constexpr 或 const 的变量, 或在程序运行期间其值始终保持不变的, 命名时以“k”开头, 大小写混合.`const int kDaysInAWeek = 7;`
- 函数名的每个单词**首字母大写** (即“驼峰变量名”或“帕斯卡变量名”), 没有下划线. 对于首字母**缩写**的单词, 更倾向于将它们视作一个单词进行首字母大写 (例如, 写作 StartRpc() 而非 StartRPC()).



较好的起名

```c++
int price_count_reader; // 用于读取价格计数器

int num_errors; // 错误数量

int num_dns_connections; // DNS 连接数量

int count; // 计数器

int error_count; // 错误数量

int num_completed_connections; // 完成的连接数量

int web_gateway_connections; // Web 网关连接数量

int page_cache_reader; // 用于读取页面缓存

int customer_id; // 客户 ID


// 类内变量名的规范
string table_name; // 好 - 用下划线.
string tablename; // 好 - 全小写.
string tableName; // 差 - 混合大小写


// 常量命名规范
const int kDaysInAWeek = 7;
```








#### 0.2 注释风格

下面的规则描述了如何注释以及在哪儿注释

三层的注释

- 文件注释
- 类注释
- 函数注释
- 变量注释/ 实现注释

- 使用 // 或 /* */, **统一**就好.
- **文件注释**描述了该文件的内容. 如果一个文件只声明, 或实现, 或测试了一个对象, 并且这个对象已经在它的声明处进行了详细的注释, 那么就没必要再加上文件注释. 除此之外的其他文件都需要文件注释



我们使用空格缩进. **不要在代码中使用制表符**. 你应该设置**编辑器**将制表符转为空格.

```c++
ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
    Type par_name1,
    // 4 space indent
    Type par_name2,
    Type par_name3) {
  DoSomething();
  // 2 space indent
...
}
```

#### 0.3 写代码时尽可能突出逻辑

- 在本项目代码中, 几乎没有在声明时就定义了函数, 方便以后重新梳理代码逻辑
- 


#### 0.4 不懂的地方是如何注释

如果在源码中有不懂得地方, 会用以下方式注释

```c++
// ###################[Question]#######################
```


#### 0.5 如果在写某一个模块的时候, 出现了 没有写过 的模块的代码怎么办

- 给未知模块上声明你需要的函数, 并注明其作用
- 当你写到未知模块上, 再写具体的实现
- 原因可能是 模块是紧耦合的, 例如, Channel 是用于封装文件描述符的事件和回调，并与 EpollPoller（基于 epoll 的事件循环）一起使用。它们之间存在紧密的关系，以便实现事件驱动的网络编程。











#### 0.6 在 C++ 项目中，什么时候该用 Boost，什么时候该用 STL 呢？

优先使用 STL，项目允许使用 boost 可以用 boost 作 STL **补充**。

这是使用C++11重写的muduo网络库，比原版简单的多。
https://github.com/Cdreamfly/CmfNetLib
这是使用上面重写的网络库写的集群聊天服务器，也比较简单。
https://github.com/Cdreamfly/ClusterChatServer
我GitHub上还有一些简单的项目欢迎Start







### 1 概论

[Note]  1.2- 1.5都来自陈硕大大的书中

#### 1.1 类图

![img-uml](./img/uml_class.jpg)


图片来自网络, 侵删. 


#### 1.2 公开接口

- Buffer仿Netty ChannelBuffer的buffer class，数据的读写通过buffer进行。用户代码不需要调用read(2)/write(2)，只需要处理收到的数据和准备好要发送的数据（§7.4）。
- InetAddress封装IPv4地址（end point），注意，它不能解析域名，只认IP地址。因为直接用gethostbyname(3)解析域名会阻塞IO线程。
- EventLoop事件循环（反应器Reactor），每个线程只能有一个EventLoop实体，它负责IO和定时器事件的分派。它用eventfd(2)来异步唤醒，这有别于传统的用一对pipe(2)的办法。它用TimerQueue作为计时器管理，用Poller作为IO multiplexing。
- EventLoopThread启动一个线程，在其中运行EventLoop::loop()。
- TcpConnection整个网络库的核心，封装一次TCP连接，注意它不能发起连接。
- TcpClient用于编写网络客户端，能发起连接，并且有重试功能。
- TcpServer用于编写网络服务器，接受客户的连接。



#### 1.3 生命周期

- 在这些类中，TcpConnection的生命期依靠shared_ptr管理（即用户和库共同控制）。
- Buffer的生命期由TcpConnection控制。其余类的生命期由用户控制。
- Buffer和InetAddress具有值语义，可以拷贝；其他class都是对象语义，不可以拷贝。



#### 1.4 内部实现

- Channel是selectable IO channel，负责注册与响应IO事件，注意它不拥有filedescriptor。它是Acceptor、Connector、EventLoop、TimerQueue、TcpConnection的成员，生命期由后者控制。
- Socket是一个RAIIhandle，封装一个filedescriptor，并在析构时关闭fd。它是Acceptor、TcpConnection的成员，生命期由后者控制。EventLoop、TimerQueue也拥有fd，但是不封装为Socket class。
- SocketsOps封装各种Sockets系统调用。
- Poller是PollPoller和EPollPoller的基类，采用“电平触发”的语意。它是EventLoop的成员，生命期由后者控制。
- PollPoller和EPollPoller封装poll(2)和epoll(4)两种IO multiplexing后端。poll的存在价值是便于调试，因为poll(2)调用是上下文无关的，用strace(1)很容易知道库的行为是否正确。
- Connector用于发起TCP连接，它是TcpClient的成员，生命期由后者控制。
- Acceptor用于接受TCP连接，它是TcpServer的成员，生命期由后者控制。
- TimerQueue用timerfd实现定时，这有别于传统的设置poll/epoll_wait的等待时长的办法。TimerQueue用std::map来管理Timer，常用操作的复杂度是O(logN)，N为定时器数目。它是EventLoop的成员，生命期由后者控制。
- EventLoopThreadPool用于创建IO线程池，用于把TcpConnection分派到某个EventLoop线程上。它是TcpServer的成员，生命期由后者控制。



#### 1.5 网络编程的本质论

我认为，TCP网络编程最本质的是处理三个半事件：

- 1．连接的建立，包括服务端接受（accept）新连接和客户端成功发起（connect）连接。TCP连接一旦建立，客户端和服务端是平等的，可以各自收发数据。
- 2．连接的断开，包括主动断开（close、shutdown）和被动断开（read(2)返回0）。
- 3．消息到达，文件描述符可读。这是最为重要的一个事件，对它的处理方式决定了网络编程的风格（阻塞还是非阻塞，如何处理**分包**，应用层的缓冲如何设计，等等）。
- 3.5 消息发送完毕，这算半个。对于低流量的服务，可以不必关心这个事件；另
    外，这里的“发送完毕”是指将数据写入操作系统的缓冲区，将由TCP协议栈负责数据的发
    送与重传，不代表对方已经收到数据。





### 回顾`muduo`的使用


- 创建了一个基于 muduo 库的简单 TCP 服务器。服务器在指定的地址和端口上监听连接，并打印新连接和**收到的消息**。
- 在这个`demo`中, 我们可以看出, 我们只需要重新设计`TcpServer::onConnection(const TcpConnectionPtr& conn) `以及`TcpServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)`这两个函数. (实际上也可以不需要重新设计 `onConnection()`函数, 也能正常运行), 然后再使用 `set`方法绑定进去就可以了 
- 只要能保证函数类型固定, 也可以用 `lambda`表达式来设计, 甚至还可以用两个类**重载**`operator()`的方法



#### 类内函数( bind )版本

```c++
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <iostream>

using namespace muduo;
using namespace muduo::net;

class MyServer {
public:
    MyServer(EventLoop* loop, const InetAddress& listenAddr)
        : server_(loop, listenAddr, "MyServer") {
        server_.setConnectionCallback(
            std::bind(&MyServer::onConnection, this, _1)
        );
        server_.setMessageCallback(
            std::bind(&MyServer::onMessage, this, _1, _2, _3)
        );
    }

    void start() {
        server_.start();
    }

private:
    void onConnection(const TcpConnectionPtr& conn) {
        if (conn->connected()) {
            std::cout << "New connection from "
                      << conn->peerAddress().toIpPort() << std::endl;
        } else {
            std::cout << "Connection " << conn->name()
                      << " is down" << std::endl;
        }
    }

    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
        std::string msg(buf->retrieveAllAsString());
        std::cout << "Received message from "
                  << conn->peerAddress().toIpPort()
                  << ": " << msg << std::endl;
        
        conn-> send(msg);
    }

    TcpServer server_;
};

int main() {
    EventLoop loop;
    InetAddress listenAddr(8888);
    MyServer server(&loop, listenAddr);

    server.start();
    loop.loop();

    return 0;
}

```



#### 以下是lambda表达式版本

```c++
// lambda表达式版本
class MyServer {
public:
    MyServer(EventLoop* loop, const InetAddress& listenAddr)
        : server_(loop, listenAddr, "MyServer") {
        server_.setConnectionCallback(
            [this](const TcpConnectionPtr& conn) {
                if (conn->connected()) {
                    std::cout << "New connection from "
                              << conn->peerAddress().toIpPort() << std::endl;
                } else {
                    std::cout << "Connection " << conn->name()
                              << " is down" << std::endl;
                }
            }
        );
        server_.setMessageCallback(
            [this](const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
                std::string msg(buf->retrieveAllAsString());
                std::cout << "Received message from "
                          << conn->peerAddress().toIpPort()
                          << ": " << msg << std::endl;
            }
        );
    }

    void start() {
        server_.start();
    }

private:
    TcpServer server_;
};
```







#### 重载 `operator()`版本

```c++
class ConnectionCallback {
public:
    void operator()(const TcpConnectionPtr& conn) {
        if (conn->connected()) {
            std::cout << "New connection from "
                      << conn->peerAddress().toIpPort() << std::endl;
        } else {
            std::cout << "Connection " << conn->name()
                      << " is down" << std::endl;
        }
    }
};

class MessageCallback {
public:
    void operator()(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
        std::string msg(buf->retrieveAllAsString());
        std::cout << "Received message from "
                  << conn->peerAddress().toIpPort()
                  << ": " << msg << std::endl;
    }
};

class MyServer {
public:
    MyServer(EventLoop* loop, const InetAddress& listenAddr)
        : server_(loop, listenAddr, "MyServer") {
        server_.setConnectionCallback(ConnectionCallback());
        server_.setMessageCallback(MessageCallback());
    }

    void start() {
        server_.start();
    }

private:
    TcpServer server_;
};
```





#### 一个问题: 如何主动给客户端发消息

我们首先要明白:

- `using TcpConnectionPtr = std::shared_ptr<TcpConnection>;`

```c++
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <iostream>

using namespace muduo;
using namespace muduo::net;

class MyServer {
public:
    MyServer(EventLoop* loop, const InetAddress& listenAddr)
        : server_(loop, listenAddr, "MyServer") {
        server_.setConnectionCallback(
            [this](const TcpConnectionPtr& conn) {
                if (conn->connected()) {
                    std::cout << "New connection from "
                              << conn->peerAddress().toIpPort() << std::endl;

                    // 发送信息到客户端
                    conn->send("Hello from server!\r\n");

                    // 添加连接到列表中
                    connections_.insert(conn);
                } else {
                    std::cout << "Connection " << conn->name()
                              << " is down" << std::endl;

                    // 从列表中移除连接
                    connections_.erase(conn);
                }
            }
        );
        server_.setMessageCallback(
            [this](const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
                std::string msg(buf->retrieveAllAsString());
                std::cout << "Received message from "
                          << conn->peerAddress().toIpPort()
                          << ": " << msg << std::endl;

                // 收到消息后回复客户端
                conn->send("Received your message: " + msg);
            }
        );
    }

    void start() {
        server_.start();
    }

    void sendToAllClients(const std::string& message) {
        // 遍历所有连接，发送消息给每个客户端
        for (const auto& conn : connections_) {
            conn->send(message);
        }
    }

private:
    TcpServer server_;
    std::set<TcpConnectionPtr> connections_;
};

int main() {
    EventLoop loop;
    InetAddress listenAddr(8888);
    MyServer server(&loop, listenAddr);

    server.start();
    loop.loop();

    return 0;
}
```






