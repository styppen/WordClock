# WordClock

This is the software part of the Arduino based Word Clock. The clock is a 11 x 10 matrix of white LEDs.
The clock's time is refreshed every 15 seconds.

The clock consists of the following components:
* MAX7219 LED driver: since there is 110 LEDs there two of them.
* RT3231: real time clock module that is powered with a CR2032 battery.
* Arduino Pro Mini: main controller responsible for proper orchestration. This controller is really thin and was perfect for keeping the clocks profile slim.
* Power supply module: a disassembled micro USB power charger.



