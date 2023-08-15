#include"httplib/httpserver.h"





#include <iostream>

using namespace std;

 






 

int main()

{

    EventLoop loop;

    InetAddress listenaddr(8888);

    // HttpServer(EventLoop *loop, const InetAddress & linten_addr, 

    //           const string & name, TcpServer::Option option = TcpServer::kNoReusePort);

    HttpServer server(&loop, listenaddr, "default_http");

    cout << "created the server"<< endl; 

    server.start();

    loop.loop();

    

    return 0;

}