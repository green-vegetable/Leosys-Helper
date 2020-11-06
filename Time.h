#pragma once
#include<bits/stdc++.h>
using namespace std;
class Time {
public:
    int year,mon,day,hour,minn,sec;
    Time();
    void freshen();
    void print();
    Time(int _hour,int _minn,int _sec=0);
    friend int operator - (Time start,Time end);
};
