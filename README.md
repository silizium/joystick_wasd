# joystick_wasd

![stable](http://badges.github.io/stability-badges/dist/stable.svg)

A Linux joystick/joypad to WASD keyboard event transformer

# usage

Compiling: 

./build-test.sh 

Calling: 

./joystick_wasd

The joystick will dump a view random "sddddd", which you can stop by turning the left stick. After that the joypad will insert the characters needed to control a Tank in the World Of Tanks game by Wargaming.com for example. Still no commandline parameters, you have to change the source if you want to change the keysettings. 

# how it's done

The program fetches from /dev/input/js0 and outputs into /dev/uinput. If you don't want to start the program as root, you will have access issues to /dev/uinput. Just do this:

Make a file "14-uinput.rules" and put it into /etc/udev/rules.d/

KERNEL=="uinput", GROUP:="uinput", MODE:="0660"

Then add the group uinput and add your user. Restart.

sudo groupadd uinput && sudo usermod -a -G uinput <USERNAME>

It's good to have a uinput group anyway to control access to the uinput device.

# license

Released under [LGPL v3](http://www.gnu.org/copyleft/lesser.html).

Copyright [Hanno Behrens](http://pebbles.schattenlauf.de) 2014.
