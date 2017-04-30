class Motor {
  int modePin1;
  int modePin2;
  int enablePin;

  public:
    Motor(int m1, int m2, int en) {
      modePin1 = m1;
      modePin2 = m2;
      enablePin = en;

      pinMode(modePin1, OUTPUT);
      pinMode(modePin2, OUTPUT);
      pinMode(enablePin, OUTPUT);
    }

    void run(int speed) {
      if (speed > 0) {
        digitalWrite(modePin1, HIGH);
        digitalWrite(modePin2, LOW);
        analogWrite(enablePin, speed);
      }
      else {
        digitalWrite(modePin1, LOW);
        digitalWrite(modePin2, HIGH);
        analogWrite(enablePin, -speed);
      }
    }

    void brake(int speed) {
      digitalWrite(modePin1, LOW);
      digitalWrite(modePin2, LOW);
      analogWrite(enablePin, speed);
    }
};

