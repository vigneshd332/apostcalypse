#include <iostream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>

using namespace std;
using namespace Poco::Net;


int main(){
    HTTPClientSession s("www.example.com");
    cout<<"Connected"<<endl;
    //s.setProxy("localhost", srv.port());
    HTTPRequest request(HTTPRequest::HTTP_GET, "/");
    //HTMLForm form;
    //form.add("entry1", "value1");
    //form.prepareSubmit(request);
    cout<<"Request Prepared"<<endl;
    s.sendRequest(request);

    cout<<"Request Sent, awaiting Response..."<<endl;
    HTTPResponse response;
    istream& rs = s.receiveResponse(response);
    cout<<"Response Received"<<endl;
    Poco::StreamCopier::copyStream(rs, cout);
    return 0;
}