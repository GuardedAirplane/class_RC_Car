#include "WiFiEsp.h"
#include "SoftwareSerial.h"

<<<<<<< HEAD
char ssid[] = "Kim's iPhone";
<<<<<<< HEAD
char pass[] = "Penguin212456";
=======
char ssid[] = "change";
char pass[] = "change";
>>>>>>> parent of c1a39e0... Wifi Push
=======
char pass[] = "puffypenguin";
>>>>>>> parent of f89750b... Wifi Combined
String channelKey = "GF7H3XRXYNLE5ZFK";

SoftwareSerial Serial1(9, 10);
WiFiEspClient client;

unsigned long last_send_time = 0;
unsigned long sendTimeout = 30000;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Retrying");
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
}

bool doWebRequest(String server, String path, String params) {

  if (client.connect(server.c_str(), 80)) {
    client.println("POST "+ path +" HTTP/1.1");
    client.println("Host: " + server);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println("Content-Length: " + String(params.length()));
    client.println();
    client.print(params);
    return true;
  }

  return false;
  
}

void loop() {

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()) {
    client.stop();
  }

  if (millis() - last_send_time > sendTimeout) {
    int data = analogRead(A0);
    String encoded = "key=" + channelKey + "&field1=" + String(data);
    doWebRequest("api.thingspeak.com", "/update", encoded);
    last_send_time = millis();
  }
  
}
