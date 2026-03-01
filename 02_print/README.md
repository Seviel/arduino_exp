# The real "Hello World"

Since the easiest thing to do with Arduino is playing with LEDs, that's what we chose as first example, now we're adding ability to print stuff, and we can do real hello world application. :D

## Usage

The standard procedure:

```
make all
make flash
```

Now, to be able to see this message, we must connect to serial terminal somehow. I used program called mobaxterm. Start the program, click "Session", pick "Serial", pick the appropriate port and set the speed to 9600. That should do it, you should finally see a printed message sent from Arduino.


