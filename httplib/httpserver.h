#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include"tcpserver.h"

#include"httpresponse.h"
#include"httprequest.h"
#include"httpcontext.h"

#include<functional>
using std::function;
class HttpServer{
public:
    using HttpCallback = function<void(const HttpRequest &, HttpResponse * )> ;

    // 实际就是进行 server_的初始化操作
    HttpServer(EventLoop *loop, const InetAddress & linten_addr, 
                const string & name, TcpServer::Option option = TcpServer::kNoReusePort);
    EventLoop * getLoop()const;
    void setHttpCallback(const HttpCallback & cb){
        http_callback_ = cb;
    }

    void setThreadNum(int num_thread){
        server_.setNumThread(num_thread);
    }

    void start();

    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp receive_time);

    void onRequest(const TcpConnectionPtr& conn, const HttpRequest & req);


private:
    TcpServer server_;
    HttpCallback http_callback_;
};

#endif