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

void getReq(HTTPClientSession& s){
    HTTPRequest request(HTTPRequest::HTTP_GET, "/", HTTPMessage::HTTP_1_1);
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
    HTTPRequest request(HTTPRequest::HTTP_POST, "/", HTTPMessage::HTTP_1_1);
    HTMLForm form;
    form.set("name", "value");
    form.set("name2", "value2");
    form.prepareSubmit(request);
    cout<<"Request Prepared"<<endl;
    HTTPResponse response;
    s.sendRequest(request);
    cout<<"Request Sent, awaiting Response..."<<endl;
    istream& rs = s.receiveResponse(response);
    cout<<"Response Received"<<endl;
    cout << response.getStatus() << endl;
}

int main(){
    HTTPClientSession s(url);
    cout<<"Connected"<<endl;
    //s.setProxy("localhost", srv.port());
    getReq(s);
    postReq(s);
    return 0;
}