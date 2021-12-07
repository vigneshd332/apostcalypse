#include <iostream>
#include <string>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>

using namespace std;
using namespace Poco::Net;
string url = "";
string ip = "";
int port = 0;
string route = "/";
string method = "POST";
bool loop = false;
bool response = true;

void getReq(HTTPClientSession& s){
    HTTPRequest request(HTTPRequest::HTTP_GET, route, HTTPMessage::HTTP_1_1);
    cout<<"GET Request Prepared"<<endl;
    s.sendRequest(request);
    HTTPResponse response;
    cout<<"Request Sent, awaiting Response..."<<endl;
    istream& rs = s.receiveResponse(response);
    cout<<"Response Received"<<endl;
    cout << response.getStatus() << endl;
    //Poco::StreamCopier::copyStream(rs, cout);
}

void postReq(HTTPClientSession& s, bool loop){
    int count = 0;
    HTTPRequest request(HTTPRequest::HTTP_POST, route, HTTPMessage::HTTP_1_1);
    cout<<"POST Request Prepared"<<endl;
    HTMLForm form;
    form.set("username", "hecker@heckerwerks.com");
    form.set("password", "totallyasafepassword");
    form.prepareSubmit(request);
    while(true){
        form.write(s.sendRequest(request));
        //cout<<"FORM Prepared"<<endl;
        //request.write(cout);
        //cout<<"Request Sent, awaiting Response... ";
        if(response==true){
            HTTPResponse res;
            istream& iStr = s.receiveResponse(res);
            //cout<<"Response Received"<<endl;
            cout<<"Status : "<<res.getStatus()<<" Count : "<<count++;
            //cerr << iStr.rdbuf();
        }else{
            cout<<count++;
        }
        cout<<endl;
        if(!loop) break;
    }
}

int main(int argc, char *argv[]){
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],"-u")==0){
            url = argv[i+1];
        }
        if(strcmp(argv[i],"-i")==0){
            ip = argv[i+1];
        }
        if(strcmp(argv[i],"-p")==0){
            port = atoi(argv[i+1]);
        }
        if(strcmp(argv[i],"-r")==0){
            route = argv[i+1];
        }
        if(strcmp(argv[i],"-m")==0){
            method = argv[i+1];
        }
        if(strcmp(argv[i],"-l")==0){
            loop = true;
        }
        if(strcmp(argv[i],"-nr")==0){
            response = false;
        }
    }
    if(url.length()==0 && ip.length()==0){
        cout<<"No URL/IP Specified"<<endl;
        return 0;
    }
    if(port==0 && ip.length()!=0){
        cout<<"No Port Specified"<<endl;
        return 0;
    }
    if(ip.length()!=0 && port!=0){
        HTTPClientSession s(ip,port);
        s.getKeepAlive();
        cout<<"Connected"<<endl;
        //s.setProxy("localhost", srv.port());
        if(method=="GET"){
            getReq(s);
        }
        if(method=="POST"){
            postReq(s, loop);
        }
    }
    else{
        HTTPClientSession s(url);
        s.getKeepAlive();
        cout<<"Connected"<<endl;
        //s.setProxy("localhost", srv.port());
        if(method=="GET"){
            getReq(s);
        }
        if(method=="POST"){
            postReq(s, loop);
        }
    }
    return 0;
}