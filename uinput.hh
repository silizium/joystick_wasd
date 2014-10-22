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

#ifndef __UINPUT_HH__
#define __UINPUT_HH__

#include <string>
#include <linux/input.h>
#include <linux/uinput.h>
/*
#define JS_EVENT_BUTTON 0x01 // button pressed/released
#define JS_EVENT_AXIS   0x02 // joystick moved
#define JS_EVENT_INIT   0x80 // initial state of device
*/

/**
 * Represents a keyboard/mouse device. Allows data to be injected into it.
 */
class UInput {
private: 
  int                    fd;
  struct uinput_user_dev uidev;
  struct input_event     event;
  int                    dx, dy;
  int                    i;
  
  int send_event(__u16 type, __u16 code, __s32 value);
  void initAbs();
  void initRel();
  
public:
  ~UInput();

  /**
   * Initialises an instance for the first joystick: /dev/input/js0
   */
  UInput();

  /**
   * Initialises an instance for the joystick with the specified,
   * zero-indexed number.
   */
  
  /**
   * Initialises an instance for the joystick device specified.
   */
  UInput(std::string devicePath);
 
  /**
   * Returns true if the joystick was found and may be used, otherwise false.
   */
  bool isFound();
  
  /**
   * Attempts to populate the provided JoystickEvent instance with data
   * from the joystick. Returns true if data is available, otherwise false.
   */
  void key(__u16 key, __s32 pressed);
  void relXY(int dx, int dy);
};

#endif
