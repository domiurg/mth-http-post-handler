#ifndef HttpPost_h
#define HttpPost_h

#include <Arduino.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <Process.h>

class HttpPost {
public:
	HttpPost();
	void sendData(String data);
	void init(const char*, int);
		
private:
	void getMAC();

	BridgeClient _client;
	String _MAC;
	const char* _host;
	int _port;
};

#endif