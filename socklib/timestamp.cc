#include"timestamp.h"

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