#include <SPI.h>
#include "RF24.h"

RF24 radio(7, 8);

const int PACKETSIZE = 6;
byte packet[PACKETSIZE];
int radioChannel = 40;
byte address[6] = {"12345"};

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(radioChannel);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, address);
  radio.startListening(); //Error here
}

void loop() {
  if (radio.available()) {
    int *intPacket = (int *)packet;
    radio.read(packet, 6);
    Serial.print(intPacket[0]);
    Serial.print(":");
    Serial.print(intPacket[1]);
    Serial.print(":");
    Serial.println(intPacket[2]);
    Serial.flush();
  }
}
