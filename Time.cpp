#include<bits/stdc++.h>
#include"time.h"
using namespace std;
Time::Time(){
    freshen();
}
Time::Time(int _year,int _mon,int _day,int _hour,int _minn,int _sec){
    year=_year,mon=_mon,day=_day;hour=_hour;minn=_minn;sec=_sec;
}
void Time::freshen(){
    time_t nowTime = time(NULL);
    struct tm *t = localtime(&nowTime);
    year=t->tm_year+1900,mon=t->tm_mon+1,day=t->tm_mday,hour=t->tm_hour,minn=t->tm_min,sec=t->tm_sec;
}
void Time::SetStart(int _hour,int _minn,int _sec){
    hour=_hour,minn=_minn,sec=_sec;
}
void Time::getnext(){
    int run=0;
    if(year%4==0 && year%100!=0) yue[1]=29;
    else yue[1]=28;
    day++;
    // printf("%d %d %d\n",year,month,day);
    if(day>yue[mon-1]){
        day=1;
        mon++;
    }
    if(mon>12){
        mon=1;
        year++;
    }
}
void Time::print(){
    printf("\r%d-%02d-%02d %02d:%02d:%02d",year,mon,day,hour,minn,sec);
}
int operator - (Time start,Time eend){
    int ans=0;
    int tian=0;
    if(start.day!=eend.day){
        if(start.mon==eend.mon) tian = start.day-eend.day;
        else tian = start.day+Time::yue[eend.mon-1]-eend.day;
    }
    ans=tian*24*3600;
    return ans+start.hour*3600+start.minn*60+start.sec -eend.hour*3600-eend.minn*60-eend.sec;
}
int Time::yue[12]{31,28,31,30,31,30,31,31,30,31,30,31};
