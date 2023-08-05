#include "httpcontext.h"

bool HttpContext::parseRequCest(Buffer *buf, Timestamp receivetime)
{
    bool ok = true;
    bool has_more = true;
    while(has_more){
        if(state_ ==kExpectRequestLine){
            // 找到第一行结束的位置
            const char *crlf = buf->findCRLF();

            if(crlf){
                // 处理 请求行
                ok = processRequestLine(buf-> Peek(), crlf);

                if(ok){
                    // 设置时间戳
                    request_.setReceiveTime(receivetime);
                    buf-> Retrieve(crlf + 2 - buf-> Peek());
                    // 处理完请求行, 处理 headers
                    state_ = kExpectHeaders;
                }
                else{// !ok
                    // 遇到错误, 处理失败
                    has_more = false;
                }
            }
            else{// ! crlf
                // 没有找到 crlf, 非法报文
                has_more = false;
            }
        }

        // 处理 头部, 本身没有循环, 通过外部循环来**逐行** 处理
        else if (state_ == kExpectHeaders){// state_ != kExpectRequestLine
            const char* crlf = buf->findCRLF();

            if(crlf){
                const char * colon = std::find(buf-> Peek(), crlf, ':');
                if(colon != crlf){
                    ++colon;
                    while(*colon == ' '){
                        colon++;
                    }
                    request_.addHeader(string(buf-> Peek(), colon), string(colon, crlf));
                }
                // 有一个空行, 头部处理完毕
                else{
                    state_ = kGotAll;
                    has_more = false;
                }
                buf-> Retrieve(crlf + 2 - buf-> Peek());
            }
            // 没找到回车换行, 非法报文
            else{
                has_more = false;
            }
        }

        // body 部分依旧留在 buf中, 
        // 空语句, 在这里不处理, 只是为了逻辑上更顺畅
        else if (state_ == kExpectBody){

        }

    }
    return ok;
}


void HttpContext::reset()
{
    state_ = kExpectRequestLine;
    HttpContext dump;
    std::swap(dump, *this);
}

bool HttpContext::processRequestLine(const char *begin, const char *end)
{
    // 传进来的数据就是一行, 不用找 crlf
    // 以空格为准
    bool succeed = false;
    const char * start = begin;
    const char * space = std::find(start, end, ' ');

    // 设置方法名
    if(space != end && request_.setMethod(string(start, space))){
        start = space +1;

        // 继续查找下一个空格
        space = std::find(start, end, ' ');
        if(space != end){
            const char * question = std::find(start, space, '?');
            if(question != space){
                request_.setPath(string(start, question));
                request_.setQuery(string(question, space));
            }
            else{
                request_.setPath(string(start, space));
            }

            start = space+1;
            succeed = end - start == 8 && std::equal(start, end-1, "HTTP/1.");

            if(succeed ){
                if(*(end-1) == '1'){
                    request_.setVersion(HttpRequest::kHttp11);
                }
                if(*(end-1) == '0'){
                    request_.setVersion(HttpRequest::kHttp10);
                }
                else{
                    succeed = false;
                }
            }

        }// space != end
    
        
    }// set method
    return succeed;
}
