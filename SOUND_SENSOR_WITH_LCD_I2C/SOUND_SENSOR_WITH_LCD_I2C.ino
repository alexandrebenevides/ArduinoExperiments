#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_SOUND_SENSOR 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

int maxPoints = 6;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_SOUND_SENSOR, INPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  int soundValue = digitalRead(PIN_SOUND_SENSOR);

  if (soundValue == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("Detectando som");
    lcd.setCursor(0, 1);

    for (int i=0; i < maxPoints; i++) {
      delay(400);
      lcd.print(".");
    }

    delay(400);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Som detectado!");
  }
}
