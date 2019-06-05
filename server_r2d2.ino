#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char *ssid = "ESP8266 AP"; // The name of the Wi-Fi network that will be created
const char *password = "thereisnospoon";   // The password required to connect to it, leave blank for an open network

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  Serial.println();
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  String request = client.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("From the client: " + request);
  client.flush();
  Serial.print("Byte sent to the client: ");
  Serial.println(client.println("The message \"" + request + "\" is acknowledged" + "\r"));
 }
