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
ofstream output;
int s[300];

// "需要每天修改的部分:"
string yyh_jsessionid("E8202CB7B6F6B1667930A6D5207029E5");
string zby_jsessionid("041B6D75EE63DE865B5FFAD44270548F");
const int year=2020,month=11,day=7;
const int yyh_seat=81,zby_seat=82;
const int zby_st_time=8,zby_ed_time=22;
const int yyh_st_time=8,yyh_ed_time=22;
void SingleSendAndPost(string jsessionid,int seat,int year,int month,int day,int st_time,int ed_time,int threadid){
    MySocket tk(GetHeader(initgetm,jsessionid));
    string token = tk.GetToken();
    GetHeader postm(initpostm,jsessionid,token,seat,year,month,day,st_time,ed_time);
    string reply=tk.GetResult(postm);
    Time a;
    a.freshen();
    cout<<threadid<<" Single One ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSeat:"<<seat<<"\t"<<"Token:"<<token<<endl;
    output<<threadid<<" Single One ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSeat:"<<seat<<"\t"<<"Token:"<<token<<endl;
    cout<<threadid<<" reply:"<<reply<<endl;
    output<<threadid<<" reply:"<<reply<<endl;
    tk.CloseSocket();
}

bool OneThread(string jsessionid,int seat,int year,int month,int day,int st_time,int ed_time,int threadid=0,Time target = Time(19,30)){
    //Create Link
    MySocket tk(GetHeader(initgetm,jsessionid));
    Time a;
    a.freshen();
    string token=tk.GetToken();
    if(token==""){
        cout<<threadid<<" Error: Init Token Dismiss!"<<endl;
        output<<threadid<<" Error: Init Token Dismiss!"<<endl;
    }
    cout<<threadid<<" Init ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\t"<<"Token:"<<token<<endl;
    //Keep Link
    int yu = target-a;
//    cout<<"\n剩余时间："<<yu<<"秒"<<endl;

    srand(time(0)*threadid);
    const int FinishKeepCountDown=rand()%20+20;
    while(yu>=FinishKeepCountDown-1){
        string tmp=tk.GetToken();
        if(tmp=="10053"){
            cout<<" ERROR: 10053 timeout ------> Shall create  another thread\n";
            return false;
        }
        token=tmp==""? token:tmp;
        a.freshen();
        yu=target-a;
        if(yu<=FinishKeepCountDown+1)break;
        int maxSleep=60*1;
//        maxSleep=1;
        cout<<threadid<<" Keep alive ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<min(yu-FinishKeepCountDown,maxSleep)<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<" FinishTime="<<FinishKeepCountDown<<endl;
        output<<threadid<<" Keep alive ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<min(yu-FinishKeepCountDown,maxSleep)<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<" FinishTime="<<FinishKeepCountDown<<endl;
        Sleep( max(0,min(yu-FinishKeepCountDown,maxSleep) *1000) );
        a.freshen();
        yu=target-a;
    }
    if(GetLastError()==10053){
        cout<<" ERROR: 10053 timeout ------> Shall create  another thread\n";
        return false;
    }


    //Do post
    GetHeader postm(initpostm,jsessionid,token,seat,year,month,day,st_time,ed_time);
    a.freshen();
    yu=target-a;
    cout<<threadid<<" Ready do post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<1+yu<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<endl;
    output<<threadid<<" Ready do post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<1+yu<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<endl;
    Sleep( max(1+yu,0)*1000);
    string reply=tk.GetResult(postm);
    a.freshen();
    cout<<threadid<<" Sended post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\t"<<"Token:"<<token<<endl;
    output<<threadid<<" Sended post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\t"<<"Token:"<<token<<endl;
    cout<<threadid<<" reply:"<<reply<<endl;
    output<<threadid<<" reply:"<<reply<<endl;
    tk.CloseSocket();

    //Insurance
    Sleep(500);
    cout<<threadid<<" Insurance! ------ "<<endl;
    output<<threadid<<" Insurance! ------ "<<endl;
    SingleSendAndPost(jsessionid,s[82],year,month,day,st_time,ed_time,threadid);
    Sleep(500);
    SingleSendAndPost(jsessionid,s[81],year,month,day,st_time,ed_time,threadid);
    Sleep(500);
    SingleSendAndPost(jsessionid,s[80],year,month,day,st_time,ed_time,threadid);
    Sleep(500);
    SingleSendAndPost(jsessionid,s[77],year,month,day,st_time,ed_time,threadid);
    Sleep(500);
    SingleSendAndPost(jsessionid,s[79],year,month,day,st_time,ed_time,threadid);
//    SingleSendAndPost(jsessionid,66,year,month,day,st_time,ed_time);
//    SingleSendAndPost(jsessionid,65,year,month,day,st_time,ed_time);
    return true;
}

int cnt=0;
DWORD WINAPI Fun1(LPVOID lpParamter)
{
    int nowcnt=cnt++;
    while(OneThread(yyh_jsessionid,s[yyh_seat],year,month,day,yyh_st_time,yyh_ed_time,nowcnt+=100)==false);
    cnt--;
    return 0L;
}
DWORD WINAPI Fun2(LPVOID lpParamter)
{
    int nowcnt=cnt++;
    while(false==OneThread(zby_jsessionid,s[zby_seat],year,month,day,zby_st_time,zby_ed_time,nowcnt+=100));
    cnt--;
    return 0L;
}

int main ()
{
    s[82]=52967;s[81]=52291;s[80]=52337;s[77]=52969;s[78]=52968;s[79]=52293;s[66]=48918;s[65]=48920;
//    system("chcp 65001");
//    char str[]="SYNCHRONIZER_TOKEN=15aee16b-52c0-418a-9b10-9825242f29b6&SYNCHRONIZER_URI=%2Fself&date=2020-11-05&seat=48918&start=480&end=1320&authid=-1";
//    cout<<sizeof(str)<<endl;
    Time a;
    string outname(string("Record ")+to_string(a.mon)+"-"+to_string(a.day)+"-"+to_string(a.year)+".txt");
    output.open (outname,ios::app);
    a.freshen();
    output<<"Start: ====== "<<a.mon<<"-"<<a.day<<" "<<a.hour<<"."<<a.minn<<"."<<a.sec<<endl;
    cout<<"Start: ====== "<<a.mon<<"-"<<a.day<<" "<<a.hour<<"."<<a.minn<<"."<<a.sec<<endl;

    for(int i=0;i<=6;i++){
//        Sleep(1000);
        if(i%2==0){
            HANDLE hThread = CreateThread(NULL, 0, Fun1, NULL, 0, NULL);
        }
        else{
            HANDLE hThread = CreateThread(NULL, 0, Fun2, NULL, 0, NULL);
        }
    }

    Sleep(3000);
    while(cnt>0)Sleep(1000*60*10);
    cout<<"Finish all"<<endl;
    output<<"Finish all"<<endl;
    return 0;
}


