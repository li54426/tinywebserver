#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H





#include "timestamp.h"







#include<map>
#include<string>
using std::string;
using std::map;


class HttpRequest{
public:
    using HttpMap= map<string, string> ;

    enum Method{
        kInvalid, kGet, kPost, kHead, kPut, kDelete
    };

    enum Version{
        kUnkown, kHttp10 , kHttp11
    };


    HttpRequest()
    : method_(kInvalid), version_( kUnkown)
    {
    }

    void setVersion(Version);
    Version getVersion() const;

    bool setMethod(const string &);
    Method getMethod();

    void setPath(const string &);
    const string &getPath();

    void setQuery(const string &);
    const string & getQuery();

    void addHeader(const string &filed, const string value);
    const string & getHeader(const string & field)const;

    const HttpMap & getHeaders();

    void setReceiveTime(Timestamp );
    Timestamp getReceiveTIme();




private:
    Method method_;
    Version version_;    

    std::string path_;
    std::string query_;
    Timestamp receiveTime_;
    std::map<string, string> headers_;

};










#endif