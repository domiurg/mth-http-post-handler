#include <HttpPost.h>

HttpPost::Connection() {
	MAC = "00:00:00:00:00:00";
	host = "";
	port = 0;
}

void setHost(const char* Host) {
	host = Host;
}

void setPort(int Port) {
	port = Port;
}

void HttpPost::getMAC() {
	Process wifiCheck;
	String wifi_stat;
	while (MAC.equals("00:00:00:00:00:00")) {
		wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");
		while (wifiCheck.available() > 0) {
			char c = wifiCheck.read();
			wifi_stat.concat(c);
		}
		Serial.println(wifi_stat);
		int mac_pos = wifi_stat.lastIndexOf('M') + 13;
		MAC = wifi_stat.substring(mac_pos, mac_pos + 17);

		delay(2500);
	}
}

void sendData(String data) {
	String params = "MAC=" + MAC + "&";
	params += data;

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
	}
	else {
		Serial.println("connection failed");
		delay(1000);
	}

	if (client.connected()) {
		client.stop();   //disconnect from server
	}
}