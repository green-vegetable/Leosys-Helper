#pragma once
#include<bits/stdc++.h>
#include"GetHeader.h"
using namespace std;

const int BUFFER_SIZE = 100000;
class MySocket{ //SOCKET的壳子
public:
    GetHeader getm;
    SOCKET sock;
    char szBuffer[BUFFER_SIZE];
    MySocket();
    MySocket(GetHeader _getm,string ip="202.112.82.43",int port=80);// 图书馆现行ip/port 2020.11.4
    void InitSock(string ip,int port);
    void CloseSocket();
    ~MySocket();
    void Send();
    void Send(GetHeader now);
    string Recv();
    string GetToken(int i=0);
    string GetContent(int i=0);
    string GetContent(GetHeader now,int i=0);
    string GetResult(int i=0);
    string GetResult(GetHeader now,int i=0);
};
