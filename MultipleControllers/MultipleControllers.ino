/*******************************************************************
    A sketch for using multiple nunchuck controllers
    on the ones ESP8266.

    This also requires a second nunchuck adaptor.

    This is achieved by changing the Wire library pins
    before we read from the controller

    This a bit different than the multiple bus example
    as it only uses one instance of the nunchuck.
    The example in the nunchuck library is set up 
    for devices that have multiple i2c instances.
    The ESP8266 wire library keeps the pins stored in
    static variables, so you can only have one instance. 

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

#include <Wire.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <NintendoExtensionCtrl.h>
// This library is for interfacing with the Nunchuck

// Can be installed from the library manager
// https://github.com/dmadison/NintendoExtensionCtrl


// Controller1 connected directly to the shield
Nunchuk nchuk;   // Controller on bus #1

#define ONE_SDA D2
#define ONE_SCL D1


// Controller2 connected to a second adaptor
//Nunchuk nchuk2;  // Controller on bus #2

#define TWO_SDA D6
#define TWO_SCL D5

void setup() {

  Serial.begin(115200);
  Serial.println("Attempting connection to controllers...");

  // nunchuck.begin just calls Wire.begin, but we can't 
  // control which pins it uses.
  //nchuk1.begin();
  Wire.begin(ONE_SDA, ONE_SCL);
  while (!nchuk.connect()) {
    Serial.println("Nunchuk on bus #1 not detected!");
    delay(1000);
  }

  // nchuk2.begin();
  Wire.begin(TWO_SDA, TWO_SCL);
  while (!nchuk.connect()) {
    Serial.println("Nunchuk on bus #2 not detected!");
    delay(1000);
  }
}

void loop() {
  Serial.println("------ Checking for Z press -------");
  // This changes the Wire library to be talking to 
  // the nunchuck connected directly to the Shield
  // This needs to be called every time you are reading
  // from the other nunchuck
  Wire.begin(D2, D1);
  if (nchuk.update()) {
    if (nchuk.buttonZ()) {
      Serial.println("Bus #1 Z pressed");
    }
  }
  else {
    Serial.println("Bus #1 Disconnected");
  }
  // Changing to the nunchuck connected to the 
  // external adaptor
  Wire.begin(D6, D5);
  if (nchuk.update()) {
    if (nchuk.buttonZ()) {
      Serial.println("Bus #2 Z pressed");
    }
  }
  else {
    Serial.println("Bus #2 Disconnected");
  }

  delay(1000);
}
