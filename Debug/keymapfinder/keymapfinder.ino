#include <Wire.h>

const int rowPins[] = {D2, D3, D4, D5};
const int colPins[] = {D10, D9, D8, D7, D0, D1};

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Full keyboard test - press keys in order");
  // I2Cを無効化
  Wire.end();
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  
  for (int i = 0; i < 6; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int row = 0; row < 4; row++) {
    digitalWrite(rowPins[row], LOW);
    delayMicroseconds(50);
    
    for (int col = 0; col < 6; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        Serial.print("Row");
        Serial.print(row);
        Serial.print(" Col");
        Serial.println(col);
        delay(300);
      }
    }
    
    digitalWrite(rowPins[row], HIGH);
  }
  delay(10);
}
