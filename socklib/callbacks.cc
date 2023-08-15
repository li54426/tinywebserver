#include "callbacks.h"


void defaultConnectionCallback(const TcpConnectionPtr& conn){
    LOG_INFO ("new conncetion is %s", conn->localAddress().toIpPort());
}
void defaultMessageCallback(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp receiveTime){
    // 将读取内容全部取出
    buffer->RetrieveAll();
}