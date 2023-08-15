#ifndef TIMESTAMP_H
#define TIMESTAMP_H


#include<time.h>
// 为了 int64_t
#include<cstdint>
#include<string>
using std::string;
#include<unistd.h>
class Timestamp{
public:
    explicit Timestamp(int64_t micro_seconds_since_epoch = 0):
        micro_seconds_since_epoch_(micro_seconds_since_epoch){}

    void swap();
    string toString()const;
    string toFormattedString()const;

    static Timestamp now();


    inline bool operator<(Timestamp rhs){
        return micro_seconds_since_epoch_< rhs.micro_seconds_since_epoch_;
    }
    inline bool operator==(Timestamp rhs){
        return micro_seconds_since_epoch_== rhs.micro_seconds_since_epoch_;
    }
private:
    int64_t micro_seconds_since_epoch_;

};

Timestamp Timestamp :: now(){
    time_t t = time(NULL);
    return Timestamp(t);
}

string Timestamp ::toString()const{
    time_t t = time(nullptr);
    char buf[64]={};
    tm* tm_time = localtime(&t);
    snprintf(buf, 64, "%4d/%02d/%02d %02d:%02d:%02d", 
        tm_time->tm_year+ 1900, tm_time->tm_mon+1, tm_time-> tm_mday, 
        tm_time-> tm_hour, tm_time->tm_min, tm_time->tm_sec);
    return string(buf);
}

#endif