#include <HttpPost.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 5
HttpPost connection;

const char* Host = "domiurg-lab.duckdns.org"; //Hostname of the server
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
		int chk = DHT.read11(DHT11_PIN);
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
    
		params += "temperature=" + String(DHT.temperature) + "&";
    params += "humidity=" + String(DHT.humidity);
		
		connection.sendData(params);
		//Serial.println(connection.getMAC());
		params = "";
		delay(2000);
}

