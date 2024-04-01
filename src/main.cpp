#include <Arduino.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <DHT.h>

// LCD pinout settings
#define RS 12
#define E 11
#define D7 7
#define D6 6
#define D5 5
#define D4 4

// Temperature sensor pinout settings
#define TEMP_SENSOR 8

// Buzzer pinout settings
#define BUZZER 9

// Switches pinout settings
#define SW0 0 // inc switch 
#define SW1 1 // selecting switch
#define SW2 2 // save switch
#define SW3 3 // change mode switch

typedef struct time {
  int hours = 23;
  int minutes = 59;
  int seconds = 30;
} time;

// Define the struct for the date and time
typedef struct date {
  int day = 1;
  int month = 4;
  int year = 2024;
} date;

unsigned long lastTime = millis();
int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
float temperature[20] = {0};
float humidity[20] = {0};
int tempHumIndex = 0;
int hourDisplayMode = 0; // TODO 0 - 24h format, 1 - 12h format
int mode = 1; // 0 - clock mode, 1 - temperature mode, 2 - alarm mode, 3 - settings mode
date d;
time t;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
DHT dht(TEMP_SENSOR, DHT11);

void playSong();
void displayDateTime();
void displaySeconds();
void updateTime();
void updateSeconds();
void measureTemperature();
void changeMode();
void displayTemperature();
void displayTemperatureText();
void displaySettings();
void displayAlarm();

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.clear();
  pinMode(BUZZER, OUTPUT);
  pinMode(SW0, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(TEMP_SENSOR, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SW3) == LOW) {
    changeMode();
  }
  updateSeconds();
  measureTemperature();
  switch (mode)
  {
  case 0: // clock mode
    if(t.seconds == 0) {
      displayDateTime();
    }else{
      displaySeconds();
    }
    break;
  case 1: // temperature mode
    displayTemperature();
    break;
  case 2: // alarm mode
    break;
  case 3: // settings mode
    break;
  default:
    break;
  }
  delay(500);
}

void displaySettingsText() {
  lcd.print("Settings");
}

void displayAlarmText() {
  lcd.print("Alarm");
}

void displayTemperatureText() {
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
}

void displayTemperature() {
  float temp = 0, hum = 0;
  for(int i = 0; i < 10; i++){
    temp += temperature[i];
    hum += humidity[i];
  }
  temp /= 10;
  hum /= 10.0;
  lcd.setCursor(6, 0);
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(5, 1);
  lcd.print(hum);
  lcd.print("%");
}

void measureTemperature() {
  temperature[tempHumIndex] = dht.readTemperature();
  humidity[tempHumIndex] = dht.readHumidity();
  tempHumIndex = (tempHumIndex + 1) % 10;
}

void changeMode() {
  lcd.clear();
  mode = (mode + 1) % 4;
  switch (mode)
  {
  case 0:
    displayDateTime();
    break;
  case 1:
    displayTemperatureText();
    break;
  case 2:
    displayAlarmText();
    break;
  case 3:
    displaySettingsText();
    break;
  default:
    break;
  }
}

void updateTime() {
  t.minutes++;
  if (t.minutes == 60) {
    t.minutes = 0;
    t.hours++;
    if (t.hours == 24) {
      t.hours = 0;
      d.day++;
      if (d.day > months[d.month - 1]) {
        d.day = 1;
        d.month++;
        if (d.month > 12) {
          d.month = 1;
          d.year++;
        }
      }
    }
  }
}

void updateSeconds() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 1000) {
    lastTime = currentTime;
    t.seconds++;
  }
  if(t.seconds >= 60) {
    t.seconds -= 60;
    updateTime();
  } 
}


void displaySeconds() {
  lcd.setCursor(12, 1);
  if (t.seconds < 10) {
    lcd.print("0");
  }
  lcd.print(t.seconds);
}

void displayDateTime() {
  lcd.print("Date: ");
  if (d.day < 10) {
    lcd.print("0");
  }
  lcd.print(d.day);
  lcd.print("/");
  if (d.month < 10) {
    lcd.print("0");
  }
  lcd.print(d.month);
  lcd.print("/");
  lcd.print(d.year);
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (t.hours < 10) {
    lcd.print("0");
  }
  lcd.print(t.hours);
  lcd.print(":");
  if (t.minutes < 10) {
    lcd.print("0");
  }
  lcd.print(t.minutes);
  lcd.print(":");
  displaySeconds();
}

void playSong() {
  tone(BUZZER, 262, 200);
  delay(200);
  tone(BUZZER, 294, 200);
  delay(200);
  tone(BUZZER, 330, 200);
  delay(200);
  tone(BUZZER, 349, 200);
  delay(200);
  tone(BUZZER, 392, 200);
  delay(200);
  tone(BUZZER, 440, 200);
  delay(200);
  tone(BUZZER, 494, 200);
  delay(200);
  tone(BUZZER, 523, 200);
  delay(200);
}