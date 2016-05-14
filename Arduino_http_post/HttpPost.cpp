#include "HttpPost.h"

HttpPost::HttpPost() {
	_MAC = "00:00:00:00:00:00";
	_host = "";
	_port = 0;
}

void HttpPost::setHost(const char* Host) {
	_host = Host;
}

void HttpPost::setPort(int Port) {
	_port = Port;
}

void HttpPost::getMAC() {
	Process wifiCheck;
	String wifi_stat;
	while (_MAC.equals("00:00:00:00:00:00")) {
		wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");
		while (wifiCheck.available() > 0) {
			char c = wifiCheck.read();
			wifi_stat.concat(c);
		}
		Serial.println(wifi_stat);
		int mac_pos = wifi_stat.lastIndexOf('M') + 13;
		_MAC = wifi_stat.substring(mac_pos, mac_pos + 17);

		delay(2500);
	}
}

void HttpPost::sendData(String data) {
	String params = "MAC=" + _MAC + "&";
	params += data;

	if (_client.connect(_host, _port)) {
		Serial.println("connected");
		_client.println("POST / HTTP/1.1");
		_client.print("Host: "); _client.println(_host);
		_client.print("Content-length:");
		_client.println(params.length());
		Serial.println(params);
		_client.println("Connection: Close");
		_client.println("Content-Type: application/x-www-form-urlencoded;");
		_client.println();
		_client.println(params);
	}
	else {
		Serial.println("connection failed");
		delay(1000);
	}

	if (_client.connected()) {
		_client.stop();   //disconnect from server
	}
}