#ifndef TIME_STAMP_H
#define TIME_STAMP_H


#include<iostream>
#include<time.h>

class Timestamp{
    Timestamp(int64_t micro_seconds = 0);
    static Timestamp now();
    std::string toString()const;
private:
    // using int_64 = signed long;
    int64_t micro_seconds_since_epoch_;

};

Timestamp:: Timestamp(int64_t micro_seconds):micro_seconds_since_epoch_(micro_seconds){}


Timestamp Timestamp::now(){
    return Timestamp(time(nullptr));
}

std::string Timestamp::toString() const
{
    char buf[128] = {0};
    tm *tm_time = localtime(&micro_seconds_since_epoch_);
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d", 
        tm_time->tm_year + 1900,
        tm_time->tm_mon + 1,
        tm_time->tm_mday,
        tm_time->tm_hour,
        tm_time->tm_min,
        tm_time->tm_sec);
    return buf;
}

#endif