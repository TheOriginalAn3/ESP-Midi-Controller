#include <MIDI.h>

// Create an instance of the MIDI library
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

void setup() {
  Serial2.begin(31250); // Start MIDI communication on Serial2
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

long mapCustom(long x, long in_min, long in_max, long out_min, long out_max) {
    // Check if the input exceeds the maximum input value
    if(x > in_max) {
        return out_max; // Return the maximum output value
    }

    const long run = in_max - in_min;
    if(run == 0){
        log_e("map(): Invalid input range, min == max");
        return -1; // Error value, indicating invalid input range
    }
    const long rise = out_max - out_min;
    const long delta = x - in_min;

    // Compute the mapped value within the specified output range
    long mappedValue = (delta * rise) / run + out_min;

    // Ensure the output does not exceed out_max due to rounding
    return mappedValue > out_max ? out_max : mappedValue;
}

int lastSentValue = -1; // Initialize with an impossible value for the first comparison
void loop() {
  int faderValue = analogRead(34);
  int mappedValue = mapCustom(faderValue, 0, 3720, 0, 127);

  // Send a MIDI CC only if the value has changed
  if(mappedValue != lastSentValue) {
    MIDI.sendControlChange(1, mappedValue, 1); // CC#1 on channel 1
    lastSentValue = mappedValue; // Update the last sent value
  }
  
  delay(100);
}
