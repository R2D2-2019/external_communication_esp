/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "ESP8266 AP";           // SSID of your AP
char pass[] = "thereisnospoon";         // password of your AP

double counter = 0;
double ackcount = 0;

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;
String msg = "Hello";
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}



void loop() {
  client.connect(server, 80);
  long rssi = WiFi.RSSI();
  Serial.println("********************************");
  Serial.println("Message sent to the AP: " + msg + counter);
  unsigned long before = millis();
  client.print(msg + counter + '\r');
  counter++;
  String answer = client.readStringUntil('\r');
  if(answer != ""){
    ackcount++;
  }
  unsigned long after = millis();
  Serial.println("From the AP: " + answer);
  client.flush();
  client.stop();
  Serial.print("Took ");
  Serial.print(after - before);
  Serial.println("ms");
  Serial.print("Strength: ");
  Serial.print(rssi);
  Serial.println("dBm");
  Serial.println("Packets send: " + String(counter));
  Serial.println("Packets lost: " + String(counter - ackcount));
  Serial.println("packet loss: " + String(((counter - ackcount) * 100) / counter) + "%");
  delay(2000);
}
