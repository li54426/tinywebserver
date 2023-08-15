#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H


#include<string>
#include<map>

using std::map;
using std::string;


#include"buffer.h"

class Buffer;

class HttpResponse{
public:
      enum HttpStatusCode
    {
        kUnknown,
        k200Ok = 200,
        k301MovedPermanently = 301,
        k400BadRequest = 400,
        k404NotFound = 404,
    };

    explicit HttpResponse(bool close)
        : status_code_(kUnknown),
        close_connection_(close)
    {
    }

        void setStatusCode(HttpStatusCode code)
    { status_code_ = code; }

    void setStatusMessage(const string& message)
    { status_message_ = message; }

    void setCloseConnection(bool on)
    { close_connection_ = on; }

    bool closeConnection() const
    { return close_connection_; }

    // 设置
    void setContentType(const string& contentType)
    { addHeader("Content-Type", contentType); }

    // FIXME: replace string with StringPiece
    void addHeader(const string& key, const string& value)
    { headers_[key] = value; }

    void setBody(const string& body)
    { body_ = body; }

    void appendToBuffer(Buffer* output) const;

private:
    HttpStatusCode status_code_;
    string body_;
    string status_message_;
    bool close_connection_;
    std::map<string, string> headers_;
};



#endif