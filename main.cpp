
#include<bits/stdc++.h>
#include"MySocket.h"
#include"GetHeader.h"
#include"Time.h"
using namespace std;

string initgetm=(R"(GET /self HTTP/1.1
Host: seat.lib.bnu.edu.cn
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:82.0) Gecko/20100101 Firefox/82.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Referer: http://seat.lib.bnu.edu.cn/
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
)");
string initpostm(R"(POST /selfRes HTTP/1.1
Host: seat.lib.bnu.edu.cn
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:82.0) Gecko/20100101 Firefox/82.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded
Content-Length: 137
Origin: http://seat.lib.bnu.edu.cn
Connection: keep-alive
Referer: http://seat.lib.bnu.edu.cn/self
Upgrade-Insecure-Requests: 1
)");

// "需要每天修改的部分:"
string yyh_jsessionid("066507B70FD3695AD7A3AEC0A6046178");
string zby_jsessionid("05B7D49F51F79386B52F68A221F8CB5C");
const int year=2020,month=11,day=5;
const int zby_st_time=8,zby_ed_time=22;
const int yyh_st_time=8,yyh_ed_time=22;

void sendonepost(string jsessionid,int seat,int year,int month,int day,int st_time,int ed_time){
    Time now;
    cout<<"<"<<now.year<<"-"<<now.mon<<"-"<<now.day<<"\t"<<now.hour<<"."<<(now.minn>=10?"":"0")<<now.minn<<"."<<(now.sec>=10?"":"0")<<now.sec<<">"<<endl;
    cout<<"<"<<"seat="<<seat<<"\tyear="<<year<<"\tmonth="<<month<<"\tday="<<day<<"\tst="<<st_time<<"\ted="<<ed_time<<">"<<endl;
    string token;
    MySocket tk(GetHeader(initgetm,jsessionid));
    token=tk.GetToken();
    GetHeader post(initpostm,jsessionid,token,seat,year,month,day,st_time,ed_time);
    string reply=tk.GetResult(post);
//    string reply=tk.GetContent(post);
    cout<<reply<<endl;
}
void CountDown(int tar_hour=19,int tar_min=30){
    Time a;
    while(1){
        a.freshen();
        sendonepost(zby_jsessionid,48918,year,month,day,zby_st_time,zby_ed_time);//66号
        sendonepost(yyh_jsessionid,48920,year,month,day,yyh_st_time,yyh_ed_time);//65号
        int left = (tar_hour-a.hour)*60*60+(tar_min-a.minn)*60-a.sec;
        if(left>=2){
            int sleeptime=min(1000*60*5, (left)*1000/2 );
            cout<<"Contral::::::: Sleep:  "<<sleeptime<<endl;
            Sleep(sleeptime);
        }
        else if(left<-5){
            cout<<"Contral::::::::  ";
            a.print();
            cout<<"\tdone\n";
            break;
        }
        Sleep(10);
    }
}
int main ()
{
//    system("chcp 65001");
//    char str[]="SYNCHRONIZER_TOKEN=15aee16b-52c0-418a-9b10-9825242f29b6&SYNCHRONIZER_URI=%2Fself&date=2020-11-05&seat=48918&start=480&end=1320&authid=-1";
//    cout<<sizeof(str)<<endl;
    Time a;
    string outname(string("Record ")+to_string(a.mon)+"-"+to_string(a.day)+"-"+to_string(a.year)+".txt");
    freopen((char*)const_cast<char*>(outname.c_str()),"a",stdout);

    CountDown(19,30);

    return 0;
}


