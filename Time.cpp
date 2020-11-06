#include<bits/stdc++.h>
#include"time.h"
using namespace std;
Time::Time(){
    freshen();
}
Time::Time(int _hour,int _minn,int _sec){
    hour=_hour;minn=_minn;sec=_sec;
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
    return start.hour*3600+start.minn*60+start.sec -eend.hour*3600-eend.minn*60-eend.sec;
}
