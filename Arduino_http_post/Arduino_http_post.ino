#include "HttpPost.h"

HttpPost connection;

const char* Host = "domiurg-home.duckdns.org"; //Hostname of the server
int Port = 8000;

String params ="";                             //String of POST parameters

void setup()
{
	Bridge.begin();
	Serial.begin(9600);

  connection.init(Host, Port);
   
}
 
void loop()
{
    params += "par1=foo&par2=bar";
    
    connection.sendData(params);
		
		params = "";
		delay(2000);
}

