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
string url = "www.example.com";
string route = "/";

void getReq(HTTPClientSession& s){
    HTTPRequest request(HTTPRequest::HTTP_GET, route, HTTPMessage::HTTP_1_1);
    cout<<"GET Request Prepared"<<endl;
    HTTPResponse response;
    s.sendRequest(request);
    cout<<"Request Sent, awaiting Response..."<<endl;
    istream& rs = s.receiveResponse(response);
    cout<<"Response Received"<<endl;
    cout << response.getStatus() << endl;
    //Poco::StreamCopier::copyStream(rs, cout);
}

void postReq(HTTPClientSession& s){
    HTTPRequest request(HTTPRequest::HTTP_POST, route, HTTPMessage::HTTP_1_1);
    cout<<"POST Request Prepared"<<endl;
    string reqBody("username=user1@yourdomain.com&password=mypword");
    cout<<"FORM Prepared"<<endl;
    request.setContentLength( reqBody.length() );
    ostream& myOStream = s.sendRequest(request);
    myOStream << reqBody;
    request.write(cout);
    cout<<"Request Sent, awaiting Response..."<<endl;
    HTTPResponse res;
    istream& iStr = s.receiveResponse(res);
    cout<<"Response Received"<<endl;
    cout<<res.getStatus()<<endl;
    //cerr << iStr.rdbuf();
}

int main(){
    HTTPClientSession s(url);
    s.getKeepAlive();
    cout<<"Connected"<<endl;
    //s.setProxy("localhost", srv.port());
    //getReq(s);
    postReq(s);
    return 0;
}