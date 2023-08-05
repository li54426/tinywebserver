#ifndef HTTP_CONTEXT_H
#define HTTP_CONTEXT_H


#include"httprequest.h"
#include"buffer.h"
#include"timestamp.h"

#include<algorithm>



class HttpContext{
public:
    enum HttpRequestParseState{
        kExpectRequestLine, // 期望解析请求行
        kExpectHeaders, // 期望解析请求头部
        kExpectBody, // 期望解析请求体
        kGotAll, // 已经解析完整请求
    };

    HttpContext()
    : state_(kExpectRequestLine)
    {
    }

    bool parseRequCest(Buffer* buf, Timestamp receivetime);

    bool gotAll()const{
        return state_ == kGotAll;
    }

    void reset();

    const HttpRequest& request() const
    { return request_; }

    HttpRequest& request()
    { return request_; }
private:
    bool processRequestLine(const char * begin, const char * end);


private:
    HttpRequestParseState state_;
    HttpRequest request_;

};




#endif