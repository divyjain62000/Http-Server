#include"tpl.h"
#include<iostream>
#include<tmwp>
#include<ctime>
using namespace std;
using namespace tmwp;
void dispatchTime(Request &request,Response &response)
{
time_t t=time(0);
char *now=ctime(&t);
response.write("<!DOCTYPE html>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>The Clock</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>");
response.write(now);
response.write("</h1>");
response.write("<a href='now'>Refresh</a>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void getCityView(Request &request,Response &response)
{
cout<<"getCityView being processed"<<endl;
string cityCodeString=request.get("cityCode");
cout<<"("<<cityCodeString<<")"<<endl;
int cityCode=atoi(cityCodeString.c_str());
cout<<"city code: "<<cityCode<<endl;
if(cityCode==1) request.forward("Ujjain.html");
else if(cityCode==2) request.forward("Indore1234.html");
else if(cityCode==3) request.forward("Dewas.html");
else 
{
request.setKeyValue("error","Invalid choice, city not selected");
request.forward("errorPage");
}
}

void saveEnquiry(Request &request,Response &response)
{
string n=request.get("nm");
string c=request.get("ct");
string a=request.get("ad");
string m=request.get("msg");
cout<<"Data recieved"<<endl;
cout<<"Name: "<<n<<endl;
cout<<"Address: "<<a<<endl;
cout<<"City: "<<c<<endl;
cout<<"Msg: "<<m<<endl;
request.forward("saveEnquiry.html");
}

void sam(Request &request,Response &response)
{
cout<<"sam got called";
request.forward("Ujjain.html");
}

void tom(Request &request,Response &response)
{
response.write("<!DOCTYPE html>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>TOM</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>");
response.write("Response from tom,generated from sam");
response.write("</h1>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}

int main()
{
TMWebProjector server(5050);
server.onRequest("/now",dispatchTime);
server.onRequest("/getCity",getCityView);
server.onRequest("/addEnquiry",saveEnquiry);
server.onRequest("/ttt",tom);
server.onRequest("/sss",sam);
register_TPL(&server);
server.start();
return 0;
}