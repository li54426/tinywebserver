#include "tcpserver.h"
#include"poller.h"
#include"epollpoller.h"

#include <string>

class EchoServer {
public:
    EchoServer(EventLoop *loop,
               const InetAddress &addr,
               const std::string &name)
            : server_(loop, addr, name), loop_(loop) {
        //注册回调函数
        server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));

        server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2,std::placeholders::_3));

        //设置合适的loop线程数量 loopthread
        server_.setNumThread(3);
    }

    void Start() {
        server_.start();
    }

private:
    //连接建立或者断开的回调
    void onConnection(const TcpConnectionPtr &conn) {
        // if (conn->connecting()) {
        //     LOG_INFO("Connection UP : %s", conn->PeerAddress().ToIpPort().c_str());
        // } else {
        //     LOG_INFO("Connection DOWN : %s", conn->PeerAddress().ToIpPort().c_str());
        // }
        LOG_INFO("Connection UP : %s", conn->peerAddress().toIpPort().c_str());
    }

    //可读写事件回调
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time) {
        std::string msg = buf->RetrieveAllToStr();
        conn->send(msg);
        conn->shutdown(); // 写端   EPOLLHUP =》 closeCallback_
    }

private:
    EventLoop *loop_;
    TcpServer server_;
};

int main() {

    EventLoop loop;
     InetAddress addr(8000);
    // TcpServer server(&loop, addr, "name");
     EchoServer server(&loop, addr, "EchoServer-01");//Acceptor non-blocking listenfd  create bind
     server.Start();//listen  loopthread  listenfd => acceptChannel => mainLoop =>
     loop.loop();//启动mainLoop的底层Poller
    return 0;
}