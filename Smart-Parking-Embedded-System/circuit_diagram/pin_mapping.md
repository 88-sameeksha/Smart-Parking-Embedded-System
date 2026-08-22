Complete Pin Configuration


ULTRASONIC SENSOR--------
| Sensor | TRIG | ECHO |
| ------ | ---: | ---: |
| Slot 1 |   D2 |   D3 |
| Slot 2 |   D4 |   D5 |
| Slot 3 |   D6 |   D7 |
| Slot 4 |   D8 |   D9 |


| Component | Arduino pin |
| --------- | ----------: |
| Buzzer    |         D10 |
| Servo     |         D11 |
| Green LED |         D12 |
| Red LED   |         D13 |
| LCD SDA   |          A4 |
| LCD SCL   |          A5 |


WIRING-----------

HC-SR04

Sensor 1
HC-SR04 #1       Arduino UNO

VCC    --------> 5V
GND    --------> GND
TRIG   --------> D2
ECHO   --------> D3

Sensor 2
VCC    --------> 5V
GND    --------> GND
TRIG   --------> D6
ECHO   --------> D7

Sensor 3
VCC    --------> 5V
GND    --------> GND
TRIG   --------> D6
ECHO   --------> D7

Sensor 4
VCC    --------> 5V
GND    --------> GND
TRIG   --------> D8
ECHO   --------> D9


LED Connections

Arduino D12
    │
  220Ω
    │
Green LED
    │
   GND


   Arduino D13
    │
  220Ω
    │
Red LED
    │
   GND

Buzzer

Arduino D10 ───── Buzzer +
Arduino GND ───── Buzzer -


LCD I2c
LCD        Arduino UNO

VCC   →    5V
GND   →    GND
SDA   →    A4
SCL   →    A5

Servo Gate
Servo

Signal → D11
VCC    → appropriate supply
GND    → common GND

