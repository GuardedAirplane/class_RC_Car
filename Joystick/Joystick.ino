#include <SPI.h>
#include "RF24.h"

RF24 radio(7, 8);

const int PACKETSIZE = 6;
byte packet[PACKETSIZE];
int joySelPin = 9;
int joyXPin = A0;
int joyYPin = A1;
int radioChannel = 40;
byte address[6] = {"12345"};

void setup() {
  pinMode(joySelPin, INPUT_PULLUP);
  radio.begin();
  radio.setChannel(radioChannel);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(address);
}

void loop() {
  int *intPacket = (int *) packet;
  intPacket[0] = analogRead(joyXPin);
  intPacket[1] = analogRead(joyYPin);
  intPacket[2] = digitalRead(joySelPin);
  radio.write((void*)packet, PACKETSIZE, false);
}
