/*******************************************************************
    A sample project for creating a BLE keypad using a nunchuck.

    Works only on ESP32

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/


// ----------------------------
// Standard Libraries
// ----------------------------

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <NintendoExtensionCtrl.h>
// This library is for interfacing with the Nunchuck

// Can be installed from the library manager
// https://github.com/dmadison/NintendoExtensionCtrl

#include <BleGamepad.h>
// This library is for using the ESP32 as BLE gamepad

// Can be installed from the library manager
//https://github.com/lemmingDev/ESP32-BLE-Gamepad

Nunchuk nchuk;
BleGamepad bleGamepad;

void setup() {
  Serial.begin(115200);

  // The D1 Nunchuck shield uses the deafault i2c pins
  // SCL == D1 == GPIO5
  // SDA == D2 == GPIO4
  // The address of the nunchuck is 0x52

  nchuk.begin();
  while (!nchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }

  bleGamepad.begin(false); //setting "auto report" to false
}

void loop() {

  if (bleGamepad.isConnected())
  {
    boolean success = nchuk.update();  // Get new data from the controller

    if (!success) {  // Ruh roh
      Serial.println("Controller disconnected!");
      delay(1000);
    }
    else {

     
      // -------------------
      // Accelormeter
      // -------------------

      // Read the accelerometer (0-1023)
      int accelX = nchuk.accelX();
      int accelY = nchuk.accelY();
      int accelZ = nchuk.accelZ();

      // Arduino Map function to covert one range to another
      // https://www.arduino.cc/reference/en/language/functions/math/map/
      // map(value, fromLow, fromHigh, toLow, toHigh)
      int mapX = map(accelX, 0, 1023, -32767, 32767);
      int mapY = map(accelY, 0, 1023, -32767, 32767);
      int mapZ = map(accelZ, 0, 1023, -32767, 32767);

      Serial.print("Accelerometer Value (x,y,z): ");
      Serial.print(accelX);
      Serial.print(",");
      Serial.print(accelY);
      Serial.print(",");
      Serial.println(accelZ);

      // Using the thumb axis as our transmission vessel
      bleGamepad.setLeftThumb(mapX, mapY);
      bleGamepad.setRightThumb(mapZ, 0);
      bleGamepad.sendReport();
    }
  }

}
