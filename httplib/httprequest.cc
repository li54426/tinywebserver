#include "httprequest.h"

void HttpRequest::setVersion(HttpRequest::Version version)
{
    version_ = version;
}

HttpRequest::Version HttpRequest::getVersion() const
{
    return version_;
}

bool HttpRequest::setMethod(const string &m)
{
    if (m == "GET")
    {
      method_ = kGet;
    }
    else if (m == "POST")
    {
      method_ = kPost;
    }
    else if (m == "HEAD")
    {
      method_ = kHead;
    }
    else if (m == "PUT")
    {
      method_ = kPut;
    }
    else if (m == "DELETE")
    {
      method_ = kDelete;
    }
    else
    {
      method_ = kInvalid;
    }
    return method_ != kInvalid;
}

HttpRequest::Method HttpRequest::getMethod()
{
    return method_;
}

void HttpRequest::setPath(const string &path)
{
    path_ = path;
}

const string &HttpRequest::getPath()
{
    // TODO: 在此处插入 return 语句
    return path_;
}

void HttpRequest::setQuery(const string & query)
{
    query_ = query;
}

const string &HttpRequest::getQuery()
{
    // TODO: 在此处插入 return 语句
    return query_ ;
}

void HttpRequest::addHeader(const string &field, const string value)
{
    headers_[field] = value;
}

const string&  HttpRequest::getHeader(const string &field) const
{
    // return headers_[field];
    string result;
    std::map<string, string>::const_iterator it = headers_.find(field);
    if (it != headers_.end())
    {
      result = it->second;
    }
    return result;
}

const HttpRequest::HttpMap  & HttpRequest::getHeaders()
{
    return headers_;
}

void HttpRequest::setReceiveTime(Timestamp receivetime)
{
    receiveTime_ = receivetime;
}

Timestamp HttpRequest::getReceiveTIme()
{
    return receiveTime_;
}
