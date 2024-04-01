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

// Define the struct for the month
typedef struct month {
  int days;
  char name[10];
} month;

// Define the struct for the date and time
typedef struct date {
  int day = 1;
  int month = 1;
  int year = 2024;
} date;

int hourDisplayMode = 0; // 0 - 24h format, 1 - 12h format
date d;
unsigned long lastTime = millis();
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void playSong();
void displayDateTime(date d, unsigned long seconds);
void displaySeconds(unsigned long seconds);
void updateTime();


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  displayDateTime(d, lastTime);
}

void loop() {
  updateTime();
}


void updateTime(){
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 1000) {
    lastTime = currentTime;
    if (millis() / 1000 % 60 == 0){
      displayDateTime(d, currentTime);
    }
    else {
      displaySeconds(currentTime);
    }
  }
}


void displaySeconds(unsigned long miliseconds) {
  lcd.setCursor(12, 1);
  if (miliseconds / 1000 % 60 < 10) {
    lcd.print("0");
  }
  lcd.print(miliseconds / 1000 % 60);
}

void displayDateTime(date d, unsigned long miliseconds) {
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
  int seconds = miliseconds / 1000;
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds = seconds % 60;
  minutes = minutes % 60;
  if (hourDisplayMode == 1) {
    if (hours > 12) {
      hours -= 12;
      lcd.print("PM");
    } else {
      lcd.print("AM");
    }
  }
  if (hours < 10) {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  displaySeconds(miliseconds);
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