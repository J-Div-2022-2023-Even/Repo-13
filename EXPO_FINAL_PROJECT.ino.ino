#include <avr/sleep.h>
#include <LowPower.h>

const int wakeUpPin = 10;  // Change this to the pin that you want to use to wake up the Arduino from standby.



void setup() {
  // put your setup code here, to run once:


  pinMode(10, INPUT);  //IR sensor 1

  pinMode(3, OUTPUT);  //DC Motor 1 for strip cut
  pinMode(4, OUTPUT);

  pinMode(8, OUTPUT);  //DC Motor 2 for strip cut
  pinMode(9, OUTPUT);

  pinMode(6, OUTPUT);  //DC Motor for bin
  pinMode(7, OUTPUT);

   pinMode(wakeUpPin, INPUT_PULLUP);

  Serial.begin(9600);  // Serial communication for debugging

  Serial1.begin(9600);  // Bluetooth module communication

}

void loop() {
  // put your main code here, to run repeatedly:

  int status = digitalRead(10);
  char receivedChar;
  receivedChar = '0';
  printf(receivedChar);
  printf(status);

  if (status == 0) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    delay(2000);
  } else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    delay(2000);
  }

  if (Serial1.available()) {
    receivedChar = Serial1.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);

    if (receivedChar == 'B') {
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      delay(2000);  ////                                              change accordingly
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      receivedChar = '0';

    }
    if (receivedChar == '1') {
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      delay(3000);  ////                                              change accordingly
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      receivedChar = '0';
    }
    
  }
  else
  {
    printf("did n't receive");
  }

// Put the Arduino to sleep mode if the wake-up pin is not triggered.
  if (digitalRead(wakeUpPin) == HIGH) {
    // Enter standby mode to save power.
    LowPower.standby();
    // After waking up, the code will continue from here.
  }
}

