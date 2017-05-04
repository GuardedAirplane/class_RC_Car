#include <SPI.h>
#include "RF24.h"
#include "Motor.h"
#include <Wire.h>
#include "string.h"
#include "ctype.h"
#include "SoftwareSerial.h"
#include "dGPS.h"


Motor motor(2,4,3);
Motor motor1(5,9,6);
RF24 radio(7, 8);
dGPS dgps = dGPS(); 

const int PACKETSIZE = 6;
byte packet[PACKETSIZE];
int radioChannel = 69;
byte address[6] = {"12345"};
int ledPin = 13;                  // LED test pin
float desLat=39.00;                   //Destination Latitude filled by user in Serial Monitor Box
float desLon=-83.00;


int test = 1;


void setup() {
  Serial.end();
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(radioChannel);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, address);
  radio.startListening(); //Error here
  Wire.begin(); // join i2c bus (address optional for master)
  //Serial.println("Test 1");
  dgps.init();                   // Run initialization routine for dGPS.
  delay(1000);
  //Serial.println("Test 2");
}

void loop() {
<<<<<<< HEAD
  //Serial.println("Test 4");

//Serial.println("Test 5");
  if (test == 0) {
    motor.run(255);
    motor1.run(255);
    Serial.println("1");
    delay(3000);
    motor.run(0);
    motor1.run(255);
   Serial.println("2");
    delay(3000);
    motor.run(255);
    motor1.run(0);
    Serial.println("3");
    delay(3000);
    motor.run(-255);
    motor1.run(-255);
    Serial.println("4");
    delay(3000);
    motor.run(0);
    motor1.run(-255);
    Serial.println("5");
    delay(3000);
    motor.run(-255);
    motor1.run(0);
    Serial.println("1");
    delay(3000);
    motor.run(0);
    motor1.run(0);
    test = 1;
  }
=======
>>>>>>> master
  
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
