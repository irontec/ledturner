LedTurner
=========

Turns on/off keyboard leds writing directly to input device.

(It works with multiple keyboards separately)


## Compiling ##

```
gcc -o ledturner ledturner.c
```


## Using ##

```
./ledturner --input /dev/input/event* [OPTIONS]
```


```
	--num, -n [0|1]    Turn OFF (0) , ON (1) Num Lock LED
	--caps, -c [0|1]   Turn OFF (0) , ON (1) Caps Lock LED
	--scroll, -s [0|1] Turn OFF (0) , ON (1) Scroll Lock LED
```

## Examples ##

Assuming our keyboard is on /dev/input/event8

Turn OFF "Num Lock" LED
```
./ledtuner --input /dev/input/event8 --num 0
```


Turn On "Caps Lock" LED
Turn Off "Scroll Lock" LED
```
./ledtuner --input /dev/input/event8 --caps 1 --scroll 0
```

Turn them all OFF
```
./ledtuner --input /dev/input/event8 -c 0 -s 0 -n 0
```


## Tips ##

* You probably must be root to be able to write on input devices.
* Use xinput to find out your devices:
```
xinput --list
```
```
xinput --list-props "HID 046a:0001"
```