#pragma once
#include<string>
using namespace std;

class GetHeader{ // ��������httpЭ���µ�get/post
public:
    bool valid;
    string strs;
    GetHeader(char str[]);
    GetHeader(string str);
    GetHeader(string str,string jsid);
    GetHeader(string str,string jsid,string token,string addition);
    GetHeader(string str,string jsid,string token,int seat,
              int year,int month,int day,int st_time_hour,int ed_time_hour);
    GetHeader(){valid=false;strs=string("EmptyGet");}
    int length(){return strs.length();}
    void Format(int flag=0);
    void print();
    char* to_str();
};
