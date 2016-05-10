#include <Bridge.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Process.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
 
//IP Address of the sever on which there is the WS: http://www.mywebsite.com/
//IPAddress server();
 
BridgeClient client;
         
String param ="";                     //String of POST parameters
String MAC = "00:00:00:00:00:00";     //MAC Address
 
void setup()
{
	//Start Bridge Between Arduino and Linino
	Bridge.begin();
	Serial.begin(9600);
  
  //Get MAC Address Info for Identification
  Process wifiCheck;
  String wifi_stat;
  while (MAC.equals("00:00:00:00:00:00")){
    wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");
    while(wifiCheck.available() > 0){
          char c = wifiCheck.read();
          wifi_stat.concat(c);
    }
    Serial.println(wifi_stat);
    int mac_pos = wifi_stat.lastIndexOf('M') + 13;
    MAC = wifi_stat.substring(mac_pos, mac_pos + 17);

    delay(2500);
  }
  
}
 
void loop()
{
	
	
	if (client.connect("domiurg-lab.duckdns.org", 8000)) {
		Serial.println("connected");
		delay(2500);
    param = "MAC=" + MAC + "&";
    
		param += "par1=foo&par2=bar";
		
		
		client.println("POST / HTTP/1.1");
		client.println("Host: domiurg-lab.duckdns.org");
		client.print("Content-length:");
		client.println(param.length());
		Serial.println(param);
		client.println("Connection: Close");
		client.println("Content-Type: application/x-www-form-urlencoded;");
		client.println();
		client.println(param);  
	}else{
		Serial.println("connection failed");
		delay(1000);
		}
		if(client.connected()){
         		client.stop();   //disconnect from server
		}
		delay(2000);
}
