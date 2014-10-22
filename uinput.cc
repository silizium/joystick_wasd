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

#include "uinput.hh"

/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include "unistd.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>

#define die(str, args...) do { \
        perror(str); \
        exit(EXIT_FAILURE); \
    } while(0)

int UInput::send_event(__u16 type, __u16 code, __s32 value){
    //struct input_event event;
    memset(&event, 0, sizeof(event));
    event.type = type;
    event.code = code;
    event.value = value;

    if (write(fd, &event, sizeof(event)) != sizeof(event)) {
        fprintf(stderr, "Error on send_event");
        return -1;
    }

    return 0;
}

void UInput::initAbs(){
  for (i=0; i < ABS_MAX; i++) {
    uidev.absmax[i] = -1;
    uidev.absmin[i] = -1;
    uidev.absfuzz[i] = -1;
    uidev.absflat[i] = -1;
  }
  uidev.absmin[ABS_X]=0;
  uidev.absmax[ABS_X]=255;
  uidev.absfuzz[ABS_X]=0;
  uidev.absflat[ABS_X]=0;
}

void UInput::initRel(){
  for(i=REL_X;i<REL_MAX;i++)
    if (ioctl(fd,UI_SET_RELBIT,i) < 0)
      fprintf(stderr, "error setrelbit %d\n", i);
} 

UInput::UInput(){
  UInput("/dev/uinput");
}

UInput::~UInput(){
  if(ioctl(fd, UI_DEV_DESTROY) < 0)    die("error: ioctl");
  close(fd);
}

UInput::UInput(std::string devicePath){
  fd = open(devicePath.c_str(), O_WRONLY | O_NONBLOCK);
// 
  if(fd < 0)                           die("error: open");
//  else printf("Opened %s handle %d\n", devicePath.c_str(), fd);

	initAbs();
	initRel();
 
  memset(&uidev, 0, sizeof(uidev));
  snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "WASD Joystick");
  uidev.id.bustype = BUS_USB;
  uidev.id.vendor  = 0x1;
  uidev.id.product = 0x1;
  uidev.id.version = 1;

  if(write(fd, &uidev, sizeof(uidev)) < 0)    die("error: write");
 
  if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_W) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_A) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_S) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_D) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_SPACE) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_C) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_X) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_T) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_Z) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, BTN_LEFT) < 0)  die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE) < 0)  die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT) < 0)  die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, BTN_FORWARD) < 0)  die("error: ioctl");
  if(ioctl(fd, UI_SET_KEYBIT, BTN_BACK) < 0)  die("error: ioctl");
  if(ioctl(fd, UI_SET_EVBIT, EV_REL) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_RELBIT, REL_X) < 0)     die("error: ioctl");
  if(ioctl(fd, UI_SET_RELBIT, REL_Y) < 0)     die("error: ioctl");
  
  if(ioctl(fd, UI_DEV_CREATE) < 0)            die("error: ioctl");
}

bool UInput::isFound(){
  return fd >= 0;
}

void UInput::key(__u16 key, __s32 pressed){
  send_event(EV_KEY, key, pressed);
  send_event(EV_SYN, SYN_REPORT, 0);
}

void UInput::relXY(int dx, int dy){
  send_event(EV_REL, REL_X, dx);
  send_event(EV_REL, REL_Y, dy);
  send_event(EV_SYN, SYN_REPORT, 0);
}
