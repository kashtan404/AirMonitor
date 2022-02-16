![PROJECT_PHOTO](https://github.com/kashtan404/Airmonitor/blob/main/project.png)
# Arduino air montor

## Description
Small air monitor with CO2, temperature and humidity sensors.

## Directories
- **firmware** - Arduino firmware
- **schemes** - wiring schemes

## Schemes
![SCHEME](https://github.com/kashtan404/Airmonitor/blob/main/schemes/scheme01.png)

## Components
- Arduino NANO https://aliexpress.ru/item/4000587268145.html
- AHT10 (5V) https://aliexpress.ru/item/33056637682.html
- MH-Z19 https://aliexpress.ru/item/4000212024923.html
- LCD 1602 i2c https://aliexpress.ru/item/32763867041.html

Misc:
- LED (pack) https://aliexpress.ru/item/32780378991.html
- Resistor (220 R) https://aliexpress.ru/item/4001066921637.html
- Photoconductive resistor https://aliexpress.ru/item/32623615207.html
- Wires https://aliexpress.ru/item/32872439317.html
- Body https://www.chipdip.ru/product/g403


## Dependencies
* [Adafruit_AHTX0](https://github.com/adafruit/Adafruit_AHTX0)
* [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
* [MHZ19_uart](https://github.com/piot-jp-Team/mhz19_uart)
* [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
* [GyverTimer](https://github.com/GyverLibs/GyverTimer)


## Variables
    SENS_TIME 30000       // sensors read period
    BRIGHT_THRESHOLD 550  // photoresistor threshold to switch brightness to min (0-1023)
    LCD_BRIGHT_MAX 255    // brightness level max
    LCD_BRIGHT_MIN 10     // brightness level min
    DISPLAY_ADDR 0x27     // display adress
    BACKLIGHT 10          // display backlight pin
    PHOTO A3              // photoresistor pin
    MHZ_RX 2              // co2 sensor TX pin 
    MHZ_TX 3              // co2 sensor RX pin
    LED 5                 // LED pin

