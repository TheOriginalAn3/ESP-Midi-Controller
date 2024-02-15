#include <MIDI.h>
#include "PotiInput.h" // Include the header file for the PotiInput class
#include <Wire.h>

// Create an instance of the MIDI library
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

// Initialize your control inputs here
// PotiInput fader1(34, 0, 3720); // Example fader

// AS5600 I2C address (check your sensor's datasheet)
#define AS5600_ADDRESS 0x36

void setup() {
    Serial2.begin(31250); // Start MIDI communication on Serial2
    Serial.begin(115200);
    // MIDI.begin(MIDI_CHANNEL_OMNI);
    Wire.begin(); // Initialize I2C
}


void requestAngle() {
// Request raw angle value from AS5600
  Wire.beginTransmission(AS5600_ADDRESS);
  Wire.write(0x0C); // AS5600 raw angle register address
  Wire.endTransmission(false);
  Wire.requestFrom(AS5600_ADDRESS, 2); // Request 2 bytes
  while (Wire.available() < 2); // Wait for 2 bytes to be available
  uint16_t angle = Wire.read() << 8 | Wire.read(); // Read 2 bytes and combine them

  // Convert raw angle to degrees (optional)
  float angleDegrees = (angle / 4096.0) * 360.0; // The AS5600 has 4096 positions

  Serial.print("Angle: ");
  Serial.print(angleDegrees);
  Serial.println(" degrees");
}

// void checkAndSendMIDI(PotiInput& control, int ccNumber) {
//     if (control.hasChanged()) {
//         MIDI.sendControlChange(ccNumber, control.lastValue, 1); // Assuming MIDI channel 1
//     }
// }

void loop() {
    // // Check each control input for changes and send MIDI CC if necessary
    // checkAndSendMIDI(fader1, 1); // CC number 1 for fader1
    // Add similar checks for other controls
    requestAngle();
    delay(100);
}