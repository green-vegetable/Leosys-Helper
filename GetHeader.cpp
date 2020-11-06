#include<string>
#include"GetHeader.h"

GetHeader::GetHeader(char str[]){
    strs=string(str);
    Format();
    valid=true;
}
GetHeader::GetHeader(string str){
    strs=str;
    Format();
    valid=true;
}
GetHeader::GetHeader(string str,string jsid){
    strs=str+"Cookie: JSESSIONID="+jsid+"\n";
    Format();
    valid=true;
}
GetHeader::GetHeader(string str,string jsid,string token,string addition){
    strs=str+"Cookie: JSESSIONID="+jsid+"\n\n"
            +"SYNCHRONIZER_TOKEN="+token+addition;
    Format(1);
    valid=true;
}
GetHeader::GetHeader(string str,string jsid,
                    string token,int seat,int year,int month,int day,int st_time,int ed_time){
    st_time*=60;
    ed_time*=60;
    strs=str+"Cookie: JSESSIONID="+jsid+"\n\n"
            +"SYNCHRONIZER_TOKEN="+token+"&SYNCHRONIZER_URI=%2Fself&date="
            +to_string(year)+"-"+to_string(month)
            +(day>=10?"-":"-0")+to_string(day)+"&seat="
            +to_string(seat)+"&start="+to_string(st_time)
            +"&end="+to_string(ed_time)+"&authid=-1";
//SYNCHRONIZER_TOKEN=9e182af8-e440-45f2-8d3f-f5c49756013f&SYNCHRONIZER_URI=%2Fself&date=2020-11-04&seat=48715&start=1140&end=1200&authid=-1
    Format(1);
}
void GetHeader::Format(int flag){
    int len=length();
    for(int i=len-1;i>=1;i--){
        if(strs[i]=='\n' && strs[i-1]!='\r'){
            strs=strs.substr(0,i)+'\r'+strs.substr(i,strs.length()-i+1);
        }
    }
    if(flag==1)
        return;
    if( int(strs.find("\r\n\r\n"))!=int(strs.length()-4)){
        strs=strs+"\r\n";
    }
}
void GetHeader::print(){
    int len=length();
    printf("Get valid:%d\n",valid);
    for(int i=0;i<len;i++){
        if(strs[i]=='\n'){
            printf("\\n##\n");
        }
        else if(strs[i]=='\r'){
            printf("\\r");
        }
        else printf("%c",strs[i]);
    }
    printf("##\n");
}
char* GetHeader::to_str(){
    char* getc=const_cast<char*>(strs.c_str());
    return getc;
}

