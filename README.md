# joystick_wasd

![stable](http://badges.github.io/stability-badges/dist/stable.svg)

A Linux joystick/joypad to WASD keyboard event transformer

# usage

Compiling: 

./build-test.sh 

Calling: 

./joystick_wasd

The joystick will dump a view random "sddddd", which you can stop by turning the left stick. After that the joypad will insert the characters needed to control a Tank in the World Of Tanks game by Wargaming.com for example. Still no commandline parameters, you have to change the source if you want to change the keysettings. 

# key setup

- left stick - drive and turn
- right stick - turret rotation and aim
- left upper button - left mousebutton
- left lower button - right mousebutton
- jumppad - fast lookaround (in work)
- right upper button - zoom in (in work)
- right lower button - zoom out (in work)
- button 1 - hold & fire
- button 2 - reload
- button 3 - lock
- button 4 - zoom
- button 9 - T
- button 10 - Z (menu)

# how it's done

The program fetches from /dev/input/js0 and outputs into /dev/uinput. If you don't want to start the program as root, you will have access issues to /dev/uinput. Just do this:

Make a file "14-uinput.rules" and put it into /etc/udev/rules.d/

KERNEL=="uinput", GROUP:="uinput", MODE:="0660"

Then add the group uinput and add your user. Restart.

sudo groupadd uinput && sudo usermod -a -G uinput <USERNAME>

It's good to have a uinput group anyway to control access to the uinput device.

The analog input from the sticks on the pad is transformed into pulsed keyboard hits. So the further you push the stick the longer will the key be pressed in its 20ms timeframe until it's hold down at full throttle or left up when the stick is centered. So while you in reality have just a digital "drive" or "not drive" by the keyboard the stick simulated analog movement by pulsing those digital states rapidly. While the technic works fine with throttle the turning may occur a bit pulsed, because there is less momentum in turning. But to smooth this out I would have to make the pulses faster and shorter and that would collide with the inertia of objects as well as it would launch very many keyboard events. 

This might be an issue of change in future by demand.

# tested

- Kubuntu 14.04 64bit, PlayOnLinux, World Of Tanks

# license

Released under [LGPL v3](http://www.gnu.org/copyleft/lesser.html).

Copyright [Hanno Behrens](http://pebbles.schattenlauf.de) 2014.
