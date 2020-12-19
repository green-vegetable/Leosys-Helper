#include<bits/stdc++.h>
#include"MySocket.h"
#include"GetHeader.h"
#include"Time.h"
using namespace std;

//daily-modify
//日常修改的部分
const int year=2020,month=12,day=20;
const int default_st_time=8,default_ed_time=22;

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
map<int,int> seat;
int seat_ed;
const char UserFile[]="UJessionid&Seatid.txt";
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
void SingleSendAndPost(string jsessionid,int seat,int year,int month,int day,int st_time,int ed_time,int threadid){
    MySocket tk(GetHeader(initgetm,jsessionid));
    string token = tk.GetToken();
    GetHeader postm(initpostm,jsessionid,token,seat,year,month,day,st_time,ed_time);
    string reply=tk.GetResult(postm);
    Time a;
    a.freshen();
//    cout<<threadid<<" Single One ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSeat:"<<seat<<"\t"<<"Token:"<<token<<endl;
//    output<<threadid<<" Single One ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSeat:"<<seat<<"\t"<<"Token:"<<token<<endl;
//    cout<<threadid<<" reply:"<<reply<<endl;
//    output<<threadid<<" reply:"<<reply<<endl;
    tk.CloseSocket();
}

bool OneThread(
    string jsessionid,int seat,int st_time, int ed_time,int year,int month,int day,int threadid=0,Time target = Time(19,30)){
    //Create Link
    cout<<"jin"<<endl;
    MySocket tk(GetHeader(initgetm,jsessionid));
    Time a;
    a.freshen();
    string token=tk.GetToken();
    if(token==""){
        cout<<threadid<<" Error: Init Token Dismiss!"<<endl;
        output<<threadid<<" Error: Init Token Dismiss!"<<endl;
    }
    cout<<threadid<<" Init ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<" seat:"<<seat<<" target:"<<month<<"-"<<day<<" "<<st_time<<"~"<<ed_time<<"\t"<<"Token:"<<token<<endl;
    output<<threadid<<" Init ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<" seat:"<<seat<<" target:"<<month<<"-"<<day<<" "<<st_time<<"~"<<ed_time<<"\t"<<"Token:"<<token<<endl;
    //Keep Link
    int yu = target-a;
    cout<<"\n剩余时间："<<yu<<"秒"<<endl;

    srand(time(0)*threadid);
    const int FinishKeepCountDown=rand()%20+20;
    while(yu>=FinishKeepCountDown-1){
        string tmp=tk.GetToken();
        if(tmp=="10053"){
//            cout<<" ERROR: 10053 timeout ------> Shall create  another thread\n";
//            output<<" ERROR: 10053 timeout ------> Shall create  another thread\n";
            return false;
        }
        token=tmp==""? token:tmp;
        a.freshen();
        yu=target-a;
        if(yu<=FinishKeepCountDown+1)break;
        int maxSleep=60*6;
//        maxSleep=1;
//        cout<<threadid<<" Keep alive ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<min(yu-FinishKeepCountDown,maxSleep)<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<" FinishTime="<<FinishKeepCountDown<<endl;
//        output<<threadid<<" Keep alive ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<min(yu-FinishKeepCountDown,maxSleep)<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<" FinishTime="<<FinishKeepCountDown<<endl;
        Sleep( max(0,min(yu-FinishKeepCountDown,maxSleep) *1000) );
        a.freshen();
        yu=target-a;
    }
    if(GetLastError()==10053){
//        cout<<" ERROR: 10053 timeout ------> Shall create  another thread\n";
        return false;
    }


    //Do post
    GetHeader postm(initpostm,jsessionid,token,seat,year,month,day,st_time,ed_time);
    a.freshen();
    yu=target-a;
//    cout<<threadid<<" Ready do post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<1+yu<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<endl;
//    output<<threadid<<" Ready do post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\tSleep:"<<1+yu<<"\t"<<"Token:"<<token<<"\tyu="<<yu<<endl;
    Sleep( max(1.0+yu,0.0)*1000);
    string reply=tk.GetResult(postm);
    a.freshen();
//    cout<<threadid<<" Sended post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\t"<<"Token:"<<token<<endl;
//    output<<threadid<<" Sended post ------ "<<a.mon<<"-"<<a.day<<"\t"<<a.hour<<"."<<a.minn<<"."<<a.sec<<"\t"<<"Token:"<<token<<endl;
//    cout<<threadid<<" reply:"<<reply<<endl;
//    output<<threadid<<" reply:"<<reply<<endl;
    tk.CloseSocket();

    //Insurance
    cout<<threadid<<" Insurance! ------ "<<endl;
    output<<threadid<<" Insurance! ------ "<<endl;
    for(int i=82-(rand()%10);i>=seat_ed;i--){
        SingleSendAndPost(jsessionid,seat[i],year,month,day,st_time,ed_time,threadid);
    }
//    SingleSendAndPost(jsessionid,66,year,month,day,st_time,ed_time);
//    SingleSendAndPost(jsessionid,65,year,month,day,st_time,ed_time);
    return true;
}

int cnt=0;
DWORD WINAPI Fun1(LPVOID lpParamter)
{
    int nowcnt=cnt++;
    int id=100*nowcnt;
    cout<<"Call FUN1: "<<nowcnt<<" cnt="<<cnt<<endl;
    while(OneThread(users[nowcnt].jsessionid,users[nowcnt].seat_num,users[nowcnt].st_time,users[nowcnt].ed_time,year,month,day,id+=100)==false);
    cnt--;
    cout<<"End Fun1: "<<nowcnt<<" cnt="<<cnt<<endl;
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
int main ()
{
    seat[82]=52967;seat[81]=52291;seat[80]=52337;seat[77]=52969;seat[78]=52968;seat[79]=52293;
    seat[79]=52293;seat[76]=52970;seat[73]=52296;seat[71]=52971;seat[70]=52973;seat[75]=52294;
    seat[69]=52966;seat[67]=52299;seat[74]=52965;seat[72]=52972;seat[68]=52343;
    seat_ed=68;
//    system("chcp 65001");
//    char str[]="SYNCHRONIZER_TOKEN=15aee16b-52c0-418a-9b10-9825242f29b6&SYNCHRONIZER_URI=%2Fself&date=2020-11-05&seat=48918&start=480&end=1320&authid=-1";
//    cout<<sizeof(str)<<endl;
    Time a;
    string outname(string("Record ")+to_string(a.mon)+"-"+to_string(a.day)+"-"+to_string(a.year)+".txt");
    output.open (outname,ios::app);
    a.freshen();
    output<<"Start: ====== "<<a.mon<<"-"<<a.day<<" "<<a.hour<<"."<<a.minn<<"."<<a.sec<<endl;
    cout<<"Start: ====== "<<a.mon<<"-"<<a.day<<" "<<a.hour<<"."<<a.minn<<"."<<a.sec<<endl;

    getUser();

    for(int i=0;i<users.size();i++){
        Sleep(1000);
        HANDLE hThread = CreateThread(NULL, 0, Fun1, NULL, 0, NULL);
    }

    Sleep(5000);
    while(cnt>0)Sleep(1000*60*10);
    cout<<"Finish all"<<endl;
    output<<"Finish all"<<endl;
    return 0;
}


