Replace */etc/avrdude.conf* with the *avrdude.conf* file included here.

Connect to ATtiny with avrdude -c usbtiny -p t84 -U flash:w:ledtestATTINY.ino.hex 

**.hex** file is found in */tmp/build(...).temp*
