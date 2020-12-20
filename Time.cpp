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
void Time::print(){
    printf("\r%d-%02d-%02d %02d:%02d:%02d",year,mon,day,hour,minn,sec);
}
int operator - (Time start,Time eend){
    int ans=0;
    if(start.day!=eend.day) ans=24*3600;
    return ans+start.hour*3600+start.minn*60+start.sec -eend.hour*3600-eend.minn*60-eend.sec;
}
