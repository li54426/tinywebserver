#include "httpserver.h"

using namespace std::placeholders;


void defaultHttpCallback(const HttpRequest &, HttpResponse *resp){
    resp-> setStatusCode(HttpResponse::k404NotFound);
    resp-> setStatusMessage("Not Found");
    resp-> setCloseConnection(true);
}



HttpServer::HttpServer(EventLoop *loop, const InetAddress &listen_addr, 
    const string &name, TcpServer::Option option):
    server_(loop, listen_addr, name, option ),
    http_callback_(defaultHttpCallback)
{
    server_.setConnectionCallback(std::bind(&HttpServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&HttpServer::onMessage, this, _1, _2, _3));
    
}

EventLoop *HttpServer::getLoop() const
{
    return server_.getLoop();
}

void HttpServer::start()
{
    LOG_DEBUG("httpserver %s start, listen on %s", server_.name(), server_.ipPort());
    server_.start();
}

void HttpServer::onConnection(const TcpConnectionPtr &conn)
{
    if(conn-> connected()){
        conn->setContext();
    }
}

void HttpServer::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp receive_time)
{
    HttpContext context;
    bool ok =  context.parseRequCest(buf, receive_time);
    if(!ok){
        conn-> send(string("HTTP/1.1 400 Bad Request\r\n\r\n"));
        conn-> shutdown();
    }

    if(context.gotAll()){
        onRequest(conn, context.request());
        context.reset();
    }



}

void HttpServer::onRequest(const TcpConnectionPtr &conn, const HttpRequest &req)
{
    const string &connection = req.getHeader("Connection");
    bool isclose = connection=="close" || 
        (req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");

    HttpResponse response(isclose);
    http_callback_(req, &response);
    Buffer buf;
    response.appendToBuffer(&buf);
    conn->send(&buf);

    if(response.closeConnection()){
        conn-> shutdown();
    }



}
