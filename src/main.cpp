#include <MIDI.h>
#include "PotiInput.h" // Include the header file for the PotiInput class

// Create an instance of the MIDI library
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

// Initialize your control inputs here
PotiInput fader1(34, 0, 127); // Example fader
PotiInput fader2(35, 0, 127); // Example fader
PotiInput fader3(32, 0, 127); // Example fader
PotiInput fader4(33, 0, 127); // Example fader
// Add more controls as needed
int _analogReadResolution = 12;

void setup() {
    Serial2.begin(31250); // Start MIDI communication on Serial2
    analogReadResolution(_analogReadResolution);
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void checkAndSendMIDI(PotiInput& control, int ccNumber) {
    if (control.hasChanged()) {
        MIDI.sendControlChange(ccNumber, control.secondLastValue, 1); // Assuming MIDI channel 1
    }
}

void loop() {
    // Check each control input for changes and send MIDI CC if necessary
    checkAndSendMIDI(fader1, 1); // CC number 1 for fader1
    checkAndSendMIDI(fader2, 2); // CC number 1 for fader1
    checkAndSendMIDI(fader3, 3); // CC number 1 for fader1
    checkAndSendMIDI(fader4, 4); // CC number 1 for fader1
    // Add similar checks for other controls
    
    delay(100);
}