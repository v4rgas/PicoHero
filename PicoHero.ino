// limits for the analog outputs on the virtual gamepad, used for the map function. Do not change.
const int ANALOG_MIN = -32767;
const int ANALOG_MAX = 32767;

// min/max whammy values
const int WHAMMY_MIN = 16;
const int WHAMMY_MAX = 26;

// min/max X/Y joystick axis values
const int STICK_X_MIN = 6;
const int STICK_X_MAX = 63;
const int STICK_Y_MIN = 4;
const int STICK_Y_MAX = 61;

#include <NintendoExtensionCtrl.h>
#include <PicoGamepad.h>

GuitarController guitar;
PicoGamepad gamepad;

void setup() {
	guitar.begin();

	while (!guitar.connect()) {
		delay(1000);
	}
  guitar.i2c().setClock(400000);
}

void loop() {
	boolean success = guitar.update();  // Get new data from the controller

	if (!success) {  // Ruh roh
		delay(1000);
	}
	else {
    gamepad.SetZ(map(guitar.whammyBar(), WHAMMY_MIN, WHAMMY_MAX, 0, ANALOG_MAX));            // whammy
    gamepad.SetButton(0, guitar.fretGreen());                                              // green
    gamepad.SetButton(1, guitar.fretRed());                                                // red
    gamepad.SetButton(2, guitar.fretYellow());                                             // yellow
    gamepad.SetButton(3, guitar.fretBlue());                                               // blue
    gamepad.SetButton(4, guitar.fretOrange());                                             // orange
    gamepad.SetRz(guitar.strumUp()?ANALOG_MIN:(guitar.strumDown()?ANALOG_MAX:0));         // strum
    gamepad.SetX(map(guitar.joyX(),STICK_X_MIN,STICK_X_MAX,ANALOG_MIN,ANALOG_MAX));  // joystick X axis
    gamepad.SetY(map(guitar.joyY(),STICK_Y_MIN,STICK_Y_MAX,ANALOG_MAX,ANALOG_MIN));  // joystick Y axis
    gamepad.SetButton(8, guitar.buttonPlus());                                        // star power
    gamepad.SetButton(9, guitar.buttonMinus());                                        // plus buttons
    gamepad.send_update(); // send inputs to USB gamepad  
	}
}
