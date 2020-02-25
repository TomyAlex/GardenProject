#include "LiquidCrystal.h"

// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

unsigned int pin12 = 12; // Port 1 Relay
unsigned int pin13 = 13; // Port 2 Relay
unsigned long int timerOpened = 8000; // Delay for opened channel
unsigned long int timerClosed = 259200000; // Delay for closed channel
const int delayTime = 1000; // Delay time

void countingDownOpenedChannel() {
  while (timerOpened != 0) {
    lcd.setCursor(0, 0);
    lcd.print("Opened : ");
    lcd.setCursor(6, 1);
    lcd.print(timerOpened);
    lcd.setCursor(7, 1);
    lcd.print(":s ");
    timerOpened = timerOpened - delayTime;
    delay(delayTime);
  }
  if (timerOpened == 0) {
    lcd.setCursor(6, 1);
    lcd.print(0);
    delay(500);
    timerOpened = 8000; // Reinitialize timeOpened
  }
  lcd.clear();
}

void countingDownClosedChannel() {
  // days, hours, minutes, seconds
  int days;
  int hours;
  int minutes;
  unsigned long int seconds;

  while (timerClosed != 0) {
    days = timerClosed / 24 / 60 / 60 / 1000;
    hours = timerClosed / 60 / 60 / 1000 % 24;
    minutes = timerClosed / 60 / 1000 % 60;
    seconds = (timerClosed / 1000 % 3600) % 60;

    lcd.setCursor(0, 0);
    lcd.print("Closed! ");
    if (days <= 1) {
      lcd.setCursor(8, 0);
      lcd.print(days);
      lcd.setCursor(9, 0);
      lcd.print(":day ");
    } else {
      lcd.setCursor(8, 0);
      lcd.print(days);
      lcd.setCursor(9, 0);
      lcd.print(":days ");
    }
    if (hours < 10) {
      lcd.setCursor(0, 1);
      lcd.print(hours);
      lcd.setCursor(1, 1);
      lcd.print(":h  ");
    } else {
      lcd.setCursor(0, 1);
      lcd.print(hours);
      lcd.setCursor(2, 1);
      lcd.print(":h ");
    }
    if (minutes < 10) {
      lcd.setCursor(5, 1);
      lcd.print(minutes);
      lcd.setCursor(6, 1);
      lcd.print(":m  ");
    } else {
      lcd.setCursor(5, 1);
      lcd.print(minutes);
      lcd.setCursor(7, 1);
      lcd.print(":m ");
    }
    if (seconds < 10) {
      lcd.setCursor(10, 1);
      lcd.print(seconds % 10);
      lcd.setCursor(11, 1);
      lcd.print(":s ");

    } else {
      lcd.setCursor(10, 1);
      lcd.print(seconds);
      lcd.setCursor(12, 1);
      lcd.print(":s");
    }
    delay(delayTime); // DelayTime
    timerClosed = timerClosed - delayTime;
  }
  if (timerClosed == 0) {
    lcd.setCursor(0, 1);
    lcd.print(0);
    delay(500);
    timerClosed = 259200000; // Reinitialize timer from beginning
  }
  lcd.clear();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pin12, OUTPUT);
  pinMode(pin13, OUTPUT);

  // LCD initialize
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin12, LOW);
  digitalWrite(pin13, LOW);
  countingDownOpenedChannel();

  // Deactivate pumps for 3 days
  digitalWrite(pin12, HIGH);
  digitalWrite(pin13, HIGH);
  countingDownClosedChannel();
}
