# Hello World, Arduino edition

Just a simple program that is a bit different from the one that comes pre flashed for starters. Instead of alternating on/off state of builtin LED each second, it turns it on for 5 seconds then briefly turns it off for 0.1 second.

## Usage

With your arduino connected to PC via USB, you can run the following commands to build and flash this example:

```
make all
make flash
```

Make sure to check your USB port though, it may be different on your machine, you can monitor which device file appears/disappears on Debian with this command:

```
sudo udevadm monitor
```
Then just plug in/out your arduino and you'll see which device file your port corresponds to, and then change PORT variable in Makefile accordingly.
