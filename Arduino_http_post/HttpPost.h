#ifndef HttpPost_h
#define HttpPost_h

#include <Arduino.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <Process.h>

class Connection {
public:
	Connection();
	void sendData(String)
	void setHost(const char*)
	void setPort(int)
		
private:
	void getMAC();

	BridgeClient client;
	String MAC;
	const char* host;
	int port;
};

#endif