// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#include "joystick.hh"
#include "uinput.hh"
#include "pulsekey.hh"
#include <unistd.h>

int main(int argc, char** argv)
{
  // Create an instance of Joystick
  Joystick joystick("/dev/input/js0"); //("/dev/input/js0");
  UInput input("/dev/uinput");
  JoystickEvent event;
  PulseKey movekey(input, KEY_S, KEY_W);
  PulseKey turnkey(input, KEY_D, KEY_A);
  int dx=0, dy=0, jmpx=0 /*, jmpy=0*/;
  // Ensure that it was found and that we can use it
  if(!joystick.isFound())  {
    printf("open joystick failed.\n");
    exit(1);
  }
  if(!input.isFound()){
    printf("open uinput failed.\n");
    exit(1);
  }
  
  while (true)  {
    // Restrict rate
    usleep(1000*5); //5 ms * 10 Steps=50 ms = 20 Hz
	 
		movekey.tick();
		turnkey.tick();
		input.relXY(dx, dy);
		

    // Attempt to sample an event from the joystick
    if (joystick.sample(&event)){
      if (event.isButton()){
			switch(event.number){
				case 0: // 1 Anhalten & Feuern
					input.key(KEY_SPACE, event.value);
					break;
				case 1: // 2 Reload C
					input.key(KEY_C, event.value);
					break;
				case 2: // 3 Lock
					input.key(KEY_X, event.value);
					break;
				case 3: // 4 Umschalt Links/Zoom
					input.key(KEY_LEFTSHIFT, event.value);
					break;
				case 4: //left upper
					input.key(BTN_LEFT, event.value);
					break;
				case 5: //right upper
					input.key(BTN_FORWARD, event.value);
					break;
				case 6: //left lower
					input.key(BTN_RIGHT, event.value);
					break;
				case 7: //right lower
					input.key(BTN_BACK, event.value);
					break;
				case 8: //9
					input.key(KEY_T, event.value);
					break;
				case 9: //10
					input.key(KEY_Z, event.value);
					break;
				default:
//        printf("Button %u is %s\n",
//          event.number,
//          event.value == 0 ? "up" : "down");
					break;
			}
      }else if (event.isAxis()){
		  switch(event.number){
			  // left stick
			case 0: 
				turnkey.setPulse(event.value);
				break;
			case 1: 
				movekey.setPulse(event.value);
				break;
				//right stick
			case 2:
				dx=event.value/8000;
				break;
			case 3: 
				dy=event.value/8000;
				break;
				//jumppad left-right
			case 4: 
				if(event.value==0){
					input.relXY(-jmpx, 0);
					input.key(BTN_RIGHT, 0);
					jmpx=0;
				}else if(event.value>0){
					jmpx=700;
					input.key(BTN_RIGHT, 1);
					input.relXY(jmpx, 0);
				}else {
					jmpx=-700;
					input.key(BTN_RIGHT, 1);
					input.relXY(jmpx, 0);
				}
				break;
				//jumppad up-down
			case 5:
				/*
				if(event.value==0){
					input.relXY(-jmpy, 0);
					input.key(BTN_RIGHT, 0);
					jmpy=0;
				}else if(event.value>0){
					jmpy=1000;
					input.key(BTN_RIGHT, 1);
					input.relXY(jmpy, 0);
				}else {
					jmpy=-1000;
					input.key(BTN_RIGHT, 1);
					input.relXY(jmpy, 0);
				}
				*/
				break;
			default: //printf("Axis %u is at position %d\n", event.number, event.value);
				break;
		  }
      }
    }
  }
}
