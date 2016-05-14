#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <Process.h>
 
//IP Address of the sever on which there is the WS: http://www.mywebsite.com/
//IPAddress server();
 
BridgeClient client;
         
String params ="";                             //String of POST parameters
String MAC = "00:00:00:00:00:00";             //MAC Address
//const char* Host = "domiurg-lab.duckdns.org"; //Hostname of the server
const char* Host = "domiurg-home.duckdns.org"; //Hostname of the server
int Port = 8000;

void getMAC(){
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

void sendData(const char* host, int port, String params){
  if (client.connect(host, port)) {
    Serial.println("connected");
    client.println("POST / HTTP/1.1");
    client.print("Host: "); client.println(host);
    client.print("Content-length:");
    client.println(params.length());
    Serial.println(params);
    client.println("Connection: Close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.println();
    client.println(params);  
  } else {
    Serial.println("connection failed");
    delay(1000);
  }
  
  if(client.connected()){
    client.stop();   //disconnect from server
  }
}

String str(const char* chars){
  String result = "";
  int len = sizeof(chars) / sizeof(char);
  for (int i = 0; i < len; i++){
    result += chars[i];  
  }
  return result;
}
 
void setup()
{
	//Start Bridge Between Arduino and Linino
	Bridge.begin();
	Serial.begin(9600);
  
  getMAC(); 
}
 
void loop()
{
	  params = "MAC=" + MAC + "&";
    params += "par1=foo&par2=bar";
    
    sendData(Host, Port, params);
	
		delay(2000);
}
