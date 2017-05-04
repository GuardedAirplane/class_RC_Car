#include <SPI.h>
#include "RF24.h"
#include "Motor.h"

Motor motor(0,2,1);
Motor motor1(3,5,4);
RF24 radio(7, 8);

const int PACKETSIZE = 6;
byte packet[PACKETSIZE];
int radioChannel = 69;
byte address[6] = {"12345"};

<<<<<<< HEAD
int test = 1;

=======
>>>>>>> parent of b2a7858... Fix motor
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

    int power = map(intPacket[0]-10, 0, 1023, -255, 255);
    int hot = map(intPacket[1], 0, 1023, -255, 255);
    int leftPower = constrain(power+hot, -255, 255);
    int rightPower = constrain(power-hot, -255, 255);
    motor.run(leftPower);
    motor1.run(rightPower);
  }
  
}
