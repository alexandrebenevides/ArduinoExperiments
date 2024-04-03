#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Erro ao inicializar o RTC.");
    while(true);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Falha ao inicializar o display OLED.");
    while(true);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC não está funcionando corretamente! Configurando data e hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  DateTime now = rtc.now();
  display.clearDisplay();
  display.setCursor(18, 8);
  display.println(formatTime(now.hour()) + ":" + formatTime(now.minute()) + ":" + formatTime(now.second()));
  display.display();
  delay(1000);
}

String formatTime(int timeValue) {
  char timeBuffer[3];
  sprintf(timeBuffer, "%02d", timeValue);
  return String(timeBuffer);
}
