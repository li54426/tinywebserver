#ifndef CALLBACK_h
#define CALLBACK_H


#include"tcpconnection.h"
#include"buffer.h"
#include"timestamp.h"


class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

using ConnectionCallback = function<void(const TcpConnectionPtr &)>;
using CloseCallback  = function<void(const TcpConnectionPtr &)>;
using WriteCompleteCallback = function<void(const TcpConnectionPtr &)>;
using MessageCallback = function<void(const TcpConnectionPtr&, Buffer *, Timestamp)>;


void defaultConnectionCallback(const TcpConnectionPtr& conn);
void defaultMessageCallback(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp receiveTime);

#endif





