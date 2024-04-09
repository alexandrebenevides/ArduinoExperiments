#include <LedControl.h>

#define ROWS 4
#define COLUMNS 4
#define DIN_PIN 11
#define CS_PIN 12
#define CLK_PIN 13

const String password = "123456";
String passwordDigited = "";

int rowsPin[ROWS] = {2, 3, 4, 5};
int columnsPin[COLUMNS] = {6, 7, 8, 9};

char keysMap[ROWS][COLUMNS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < COLUMNS; i++) {
    pinMode(columnsPin[i], OUTPUT);
    digitalWrite(columnsPin[i], HIGH);
  }

  for (int i = 0; i < ROWS; i++) {
    pinMode(rowsPin[i], INPUT_PULLUP);
  }

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  displayLocked();
}

void loop() {
  for (int column = 0; column < COLUMNS; column++) {
    digitalWrite(columnsPin[column], LOW);

    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowsPin[row]) == LOW) {
        passwordDigited += keysMap[row][column];
        checkPassoword();

        while (digitalRead(rowsPin[row]) == LOW) true;

        delay(50);
      }
    }

    digitalWrite(columnsPin[column], HIGH);
  }
}

void checkPassoword() {
  Serial.println(passwordDigited);
  if (passwordDigited.length() >= 6) {
    if (passwordDigited == password) {
      displayUnlocked();
      passwordDigited = "";
      return;
    }

    displayLocked();
    passwordDigited = "";
  }
}

void displayLocked() {
  byte locked[8] = {
    B11111111,
    B11000011,
    B10100101,
    B10011001,
    B10011001,
    B10100101,
    B11000011,
    B11111111
  };

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, locked[i]);
  }
}

void displayUnlocked() {
  byte unlocked[8] = {
    B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111
  };

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, unlocked[i]);
  }
}
