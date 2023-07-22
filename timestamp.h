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



#endif