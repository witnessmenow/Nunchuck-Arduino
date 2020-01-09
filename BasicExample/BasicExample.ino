/*******************************************************************
    A sample project for making controlling two servo motors
    with an nunchuck controller

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

#include <Servo.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <NintendoExtensionCtrl.h>
// This library is for interfacing with the Nunchuck

// Can be installed from the library manager
// https://github.com/dmadison/NintendoExtensionCtrl

#define TILT_SERVO_MIN 70
#define TILT_SERVO_MAX 180

#define PAN_SERVO_MIN 0
#define PAN_SERVO_MAX 180

#define PAN_PIN D5
#define TILT_PIN D6

// Giving the analog stick a deadzone
#define Y_DEADZONE 30
#define X_DEADZONE 30


// Default starting position for the servos
int tiltPos = 90; 
int panPos = 90;

// Resting position of the analog stick when not moved
// (This probably is not accurate)
int restY = 130;
int restX = 130;

Servo panServo; 
Servo tiltServo;

Nunchuk nchuk;

void setup() {
  Serial.begin(115200);
  nchuk.begin();

  while (!nchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }

  panServo.attach(PAN_PIN); 
  tiltServo.attach(TILT_PIN);

  delay(100);
  panServo.write(panPos); 
  tiltServo.write(tiltPos);

  nchuk.update();
  restY = nchuk.joyY();
  restX = nchuk.joyX();
}

void loop() {
  Serial.println("----- Nunchuk Test -----"); // Making things easier to read
  
  boolean success = nchuk.update();  // Get new data from the controller

  if (!success) {  // Ruh roh
    Serial.println("Controller disconnected!");
    delay(1000);
  }
  else {

    // Read a joystick axis (0-255, X and Y)
    int joyY = nchuk.joyY();
    int joyX = nchuk.joyX();

    if(restY != joyY){
      if(joyY - Y_DEADZONE > restY){
        //Tilting up
        if(tiltPos <TILT_SERVO_MAX){
          tiltPos++;
        }
        tiltServo.write(tiltPos);
      }
      else if (joyY + Y_DEADZONE < restY){
        //Tilting down
        if(tiltPos > TILT_SERVO_MIN){
          tiltPos--;
        }
        tiltServo.write(tiltPos);
      }
    }

    if(restX != joyX){
      if(joyX - X_DEADZONE > restX){
        //Panning Right?
        if(panPos < PAN_SERVO_MAX){
          panPos++;
        }
        panServo.write(panPos);
      }
      else if (joyX + X_DEADZONE < restX){
        //Panning Left?
        if(panPos > PAN_SERVO_MIN){
          panPos--;
        }
        panServo.write(panPos);
      }
    }

   
  }
}
