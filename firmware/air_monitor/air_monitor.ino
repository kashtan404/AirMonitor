#define SENS_TIME 30000       // sensors read period
#define BRIGHT_THRESHOLD 550  // photoresistor threshold to switch brightness to min (0-1023)
#define LCD_BRIGHT_MAX 255    // brightness level max
#define LCD_BRIGHT_MIN 10     // brightness level min
#define DISPLAY_ADDR 0x27     // display adress
#define BACKLIGHT 10          // display backlight pin
#define PHOTO A3              // photoresistor pin
#define MHZ_RX 2              // co2 sensor TX pin 
#define MHZ_TX 3              // co2 sensor RX pin
#define LED 5                 // LED pin

// display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(DISPLAY_ADDR, 16, 2);

// temp+humidity sensor
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

// co2 sensor
#include <MHZ19_uart.h>
MHZ19_uart mhz19;

// timers
#include <TimerMs.h>
TimerMs sensorsTimer(SENS_TIME, 1, 0);
TimerMs drawSensorsTimer(SENS_TIME, 1, 0);
TimerMs brightTimer(2000, 1, 0);
TimerMs co2LEDTimer(2000, 1, 0);

// output vars
float dispTemp;
byte dispHum;
int dispCO2;

// LED blink vars
long interval = 1000;
long previousInterval = 0;

void checkBrightness() {
  if (analogRead(PHOTO) < BRIGHT_THRESHOLD) {
    analogWrite(BACKLIGHT, LCD_BRIGHT_MIN);
  } else {
    analogWrite(BACKLIGHT, LCD_BRIGHT_MAX);
  }
}

void readSensors() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  dispTemp = temp.temperature;
  dispHum = humidity.relative_humidity;
  dispCO2 = mhz19.getPPM();
}

void drawSensors() {
  lcd.setCursor(0, 0);
  lcd.print("CO2: " + String(dispCO2) + "ppm ");
  lcd.setCursor(13, 0);
  if (dispCO2 < 700) lcd.print("OK ");
  else lcd.print("WRN");
  lcd.setCursor(0, 1);
  lcd.print("t: " + String(dispTemp, 1));
  lcd.write(223);
  lcd.setCursor(9, 1);
  lcd.print("h: " + String(dispHum) + "% ");
}

void setup() {
  Serial.begin(9600);

  pinMode(BACKLIGHT, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, 0);
  analogWrite(BACKLIGHT, LCD_BRIGHT_MAX);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  mhz19.begin(MHZ_TX, MHZ_RX);
  mhz19.setAutoCalibration(false);
  aht.begin(&Wire);

  readSensors();
  drawSensors();
}

void loop() {
  if (brightTimer.tick()) checkBrightness();
  if (sensorsTimer.tick()) readSensors();
  if (drawSensorsTimer.tick()) drawSensors();

  if (dispCO2 < 700) {
    co2LEDTimer.stop();
    digitalWrite(LED, 0);
    previousInterval = 0;
  }
  else {
    if (dispCO2 < 1000) interval = 1000;
    else if (dispCO2 < 1200) interval = 600;
    else if (dispCO2 >= 1500) interval = 300;
    if (previousInterval != interval) {
      previousInterval = interval;
      co2LEDTimer.setTime(interval);
    }
    if (co2LEDTimer.tick()) digitalWrite(LED, !(digitalRead(LED)));
  }
}
