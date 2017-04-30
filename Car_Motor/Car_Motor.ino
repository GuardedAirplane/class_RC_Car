#include "Motor.h"

Motor motor(2,4,3);
Motor motor1(5,7,6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
   for(int i = 0; i <= 1023; i++){
      for(int x = 0; x <= 1023; i++){
      int power = map(i, 0, 1023, -255, 255);
      int hot = map(x, 0, 1023, -255, 255);
      int leftPower = constrain(power+hot, -255, 255);
      int rightPower = constrain(power-hot, -255, 255);
      motor.run(leftPower);
      motor1.run(rightPower);
      }
   }
   
}
