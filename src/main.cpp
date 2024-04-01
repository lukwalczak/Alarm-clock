#include <Arduino.h>
#include <LiquidCrystal.h>

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
  int month = 1;
  int year = 2024;
} date;

unsigned long lastTime = millis();
int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int hourDisplayMode = 0; // TODO 0 - 24h format, 1 - 12h format
int mode = 0; // 0 - clock mode, 1 - temperature mode, 2 - alarm mode, 3 - settings mode
date d;
time t;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void playSong();
void displayDateTime(date d, time t);
void displaySeconds(time t);
void updateTime(date *d, time *t);
void updateSeconds(date *d, time *t);
void measureTemperature();


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  displayDateTime(d, t);
}

void loop() {
  updateSeconds(&d, &t);
  switch (mode)
  {
  case 0:
    if(t.seconds == 0) {
      displayDateTime(d, t);
    }else{
      displaySeconds(t);
    }
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  default:
    break;
  }
}


void updateTime(date *d, time *t) {
  t->minutes++;
  if (t->minutes == 60) {
    t->minutes = 0;
    t->hours++;
    if (t->hours == 24) {
      t->hours = 0;
      d->day++;
      if (d->day > months[d->month - 1]) {
        d->day = 1;
        d->month++;
        if (d->month > 12) {
          d->month = 1;
          d->year++;
        }
      }
    }
  }
}

void updateSeconds(date *d, time *t) {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 1000) {
    lastTime = currentTime;
    t->seconds++;
  }
  if(t->seconds == 60) {
    t->seconds = 0;
    updateTime(d,t);
  } 
}


void displaySeconds(time t) {
  lcd.setCursor(12, 1);
  if (t.seconds < 10) {
    lcd.print("0");
  }
  lcd.print(t.seconds);
}

void displayDateTime(date d, time t) {
  lcd.clear();
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
  displaySeconds(t);
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