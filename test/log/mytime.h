#ifndef MYTIME_H
#define MYTIME_H

#include<ctime>
#include<vector>
#include<string>
#include<cstring>
using std::string;
using std::to_string;

class Mytime{
    int year_;
    int month_;
    int day_;
public:
    std::vector<int> Get(){
        return {year_, month_, day_};
    }

    int GetDay(){
        return day_;
    }

    int GetYear(){
        return year_;
    }

    int GetMon(){
        return month_;
    }

    string GetString(){
        string s(10, 'a');
        s.clear();
        // 4 + 2+2 +2=10
        s = to_string(year_) +"_"+ to_string(month_) + "_"+to_string(day_);
        return s;
    }
    
    string GetStringSec(){
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        string s = GetString();
        string s2 = to_string(localTime-> tm_hour) + ":" + to_string(localTime-> tm_min) +":" + to_string(localTime-> tm_sec);

        return s + ' '+ s2;
    }

    Mytime(){
        Init();
    }


    void Init(){
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        year_= localTime->tm_year +1900;
        month_ = localTime-> tm_mon + 1;
        day_ = localTime-> tm_mday;
    }
};


#endif