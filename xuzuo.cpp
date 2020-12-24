#include<bits/stdc++.h>
#include <winsock2.h>
#include <windows.h>
#include"MySocket.h"
#include"GetHeader.h"
#include"Time.h"
using namespace std;

ofstream output;
const char UserFile[]="UJessionid&seatid.txt"; //最好用不同的txt，当心退掉当前的座位！

string cancelgetm=(R"(GET /reservation/cancel/4431233 HTTP/1.1
Host: seat.lib.bnu.edu.cn
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:84.0) Gecko/20100101 Firefox/84.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://seat.lib.bnu.edu.cn/history?type=SEAT
Upgrade-Insecure-Requests: 1
)");
//daily-modify
const int default_st_time=8,default_ed_time=22;
struct User{
    string jsessionid;
    string name="";
    int seat_num;
    int st_time;
    int ed_time;
    User(){
        jsessionid="";
        name="";
        seat_num=-1;
        st_time=default_st_time;
        ed_time=default_ed_time;
    }
    User(string _jsessioinid,int _seat_num=-1,string _name=""){
        jsessionid=_jsessioinid;
        seat_num=_seat_num;
        name=_name;
        st_time=default_st_time;
        ed_time=default_ed_time;
    }
    void show(){
        cout<<name<<"\t"<<jsessionid<<"\t"<<seat_num<<"\t"<<st_time<<"-"<<ed_time<<endl;
        output<<name<<"\t"<<jsessionid<<"\t"<<seat_num<<"\t"<<st_time<<"-"<<ed_time<<endl;
    }
};
vector<User> users;
DWORD WINAPI Fun1(LPVOID lpParamter) //自动续约
{
    while(1){
        Time a;
        a.freshen(); //当前时间
        cout<<a.hour<<":"<<a.minn<<":"<<a.sec<<endl;
        Sleep(1000); //休息1秒
        for(auto i:users){
            //枚举每个人
            cout<<i.name<<":"<<i.jsessionid<<endl;
            GetHeader message(cancelgetm,i.jsessionid);//得到发送内容
            message.print();
            MySocket tk(message);//建立链接
            tk.Send();
            auto reply=tk.Recv();//得到回复
            cout<<reply<<endl;
        }
    }
    return 0L;
}

void getUser(){
    freopen(UserFile,"r",stdin);
    users.clear();
    string tj,tn;int ts;
    while(cin>>tn>>tj>>ts){
        users.push_back(User(tj,ts,tn));
    }
    for(auto&i:users){
        i.show();
    }
}
main (){
    getUser();

    CreateThread(NULL,0,Fun1,NULL,0,NULL);//唤醒自动续座线程
}
