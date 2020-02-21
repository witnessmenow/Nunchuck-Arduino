/*******************************************************************
    A sample project for an printing the inputs 
    from a nunchuck controller to serial.
    Works on both ESP8266 and ESP32

    Parts:
    D1 Mini ESP8266 * - http://s.click.aliexpress.com/e/uzFUnIe

 *  * = Affilate

    If you find what I do usefuland would like to support me,
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

Nunchuk nchuk;

// print values to serial every second
#define PRINT_DELAY 1000

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
}

void loop() {
  Serial.println("----- Nunchuk Test -----"); // Making things easier to read

  boolean success = nchuk.update();  // Get new data from the controller

  if (!success) {  // Ruh roh
    Serial.println("Controller disconnected!");
    delay(1000);
  }
  else {

    // -------------------
    // Buttons
    // -------------------

    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();

    Serial.print("Buttons pressed: ");
    if (zButton) {
      Serial.print("z");
    }

    if (cButton) {
      Serial.print("c");
    }
    Serial.println("");

    // -------------------
    // Joystick
    // -------------------

    // Read the joystick axis (0-255)
    // Note: I havent seen it go near 0 or 255
    // I've seen ranges closer to 30-210
    int joyY = nchuk.joyY();
    int joyX = nchuk.joyX();

    Serial.print("Joystick Value (x,y): ");
    Serial.print(joyX);
    Serial.print(",");
    Serial.println(joyY);

    // -------------------
    // Joystick
    // -------------------


    // Read the accelerometer (0-1023)
    int accelX = nchuk.accelX();
    int accelY = nchuk.accelY();
    int accelZ = nchuk.accelZ();

    Serial.print("Accelerometer Value (x,y,z): ");
    Serial.print(accelX);
    Serial.print(",");
    Serial.print(accelY);
    Serial.print(",");
    Serial.println(accelZ);
  }

  delay(PRINT_DELAY);
}
