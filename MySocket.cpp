#include<bits/stdc++.h>
#include"GetHeader.h"
#include"MySocket.h"
using namespace std;
MySocket::MySocket(){}
MySocket::MySocket(GetHeader _getm,string ip,int port){
    getm=_getm;
    InitSock(ip,port);
}
void MySocket::InitSock(string ip,int port){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("202.112.82.43");
    sockAddr.sin_port = htons(80);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    struct timeval timeout={500,0}; //超时3秒
    setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
    setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(const char*)&timeout,sizeof(timeout));
}
void MySocket::CloseSocket(){
    closesocket(sock);
    WSACleanup();
}
MySocket::~MySocket(){
    CloseSocket();
}
void MySocket::Send(){
    send(sock,getm.to_str(),getm.length(),NULL);
}
void MySocket::Send(GetHeader now){
    send(sock,now.to_str(),now.length(),NULL);
    send(sock,now.to_str(),now.length(),NULL);
}
string MySocket::Recv(){
    int cnt=3;
    int now=0;int ycnt=500;
    memset(szBuffer,0,sizeof(szBuffer));
    while(1){
        int getsize=recv(sock,szBuffer+now,BUFFER_SIZE-now-5,NULL);
        int lasterror=GetLastError();
//        cout<<"DEBUG: GetLastError()="<<lasterror<<"\tgetsize="<<getsize<<endl;
        if(lasterror==10053)
            return string("10053");
        if(getsize==-1){ //超时停止
            cnt--;
            if(cnt)continue;
            break;
        }
        for(int i=now;i<now+getsize+1;i++){
            if(szBuffer[i]==0)szBuffer[i]='#';
        }
        if(getsize==0){
            ycnt--;
            if(ycnt>0)continue;break;
        }
        now+=getsize;
    }
    return string(szBuffer);
}
string MySocket::GetToken(int i){ // csrf
    Send();
    string tmp = Recv();
    if(tmp=="10053")return tmp;
    int pos=tmp.find(R"(SYNCHRONIZER_TOKEN" value=")");
    string token = "";
    if(tmp==""){
        cout<<"Error: (1) no reply"<<endl;
    }
    else if(pos==-1){
        cout<<"Error: (1) no token found"<<endl;
    }
    else {
        token = tmp.substr(pos+27,36);
    }
//    if(tmp!="" && pos!=-1)
//        cout<<"Get token! token=("<<token<<")"<<endl;
    return token;
}
string MySocket::GetContent(int i){
    Send();
    return Recv();
}
string MySocket::GetContent(GetHeader now,int i){
    Send(now);
    return Recv();
}
string MySocket::GetResult(int i){
    Send();
    string tmp=Recv();
    int pos=tmp.find(R"(<div class="content">
    <div class="layoutSeat">
        <dl>)");
    string result="";
    if(pos!=-1){
        result=tmp.substr(pos,pos+50);
    }
    else result+="No result";
    return result;
}
string MySocket::GetResult(GetHeader now,int i){
    Send(now);
    string tmp=Recv();
    int pos=tmp.find(R"(<div class="content">)");
    string result="";
    if(pos!=-1){
        result=tmp.substr(pos+85,120);
    }
    else result+="No result";
    return result;
}
