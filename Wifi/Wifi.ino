#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include <NewPing.h>
#include "dGPS.h"

 
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200

char ssid[] = "Kim's iPhone";
char pass[] = "Penguin212456";
String channelKey = "4LXJJBBWV1KOT9NA";
                  // LED test pin
float desLat=12.00;                   //Destination Latitude filled by user in Serial Monitor Box
float desLon=24.00;

SoftwareSerial Serial1(8, 9);
WiFiEspClient client;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//dGPS dgps = dGPS();

unsigned long last_send_time = 0;
unsigned long sendTimeout = 30000;

void setup() {
         // Initialize LED pin
  
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

  delay(3000);
  Serial.println("Test");
  //dgps.init();
  Serial.println("Test 2");
  delay(3000);
  Serial.println("Test 3");
  
  
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
  

  //dgps.update(desLat, desLon);

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()) {
    client.stop();
  }

  if (millis() - last_send_time > sendTimeout) {
    unsigned int uS = sonar.ping_cm();
    Serial.print(uS);
    Serial.println("cm");
    delay(100);
  
    Serial.print("Latitude: ");
    //Serial.println(dgps.Lat(), 6);  // Lattitude - in DD.MMSSSS format (decimal-degrees format)  (D-Degree; M-Minute; S-Second)
    //String myLat (dgps.Lat(), 6);
    Serial.print("Longitude: ");
    //Serial.println(dgps.Lon(), 6);  // Longitude - in DD.MMSSSS format (decimal-degrees format)  (D-Degree; M-Minute; S-Second)
    //String myLon (dgps.Lon(), 6);
    delay(3000);
    
    String encoded = "key=" + channelKey + "&field1=" + String(uS);
    doWebRequest("api.thingspeak.com", "/update", encoded);
    last_send_time = millis();
  }

}
