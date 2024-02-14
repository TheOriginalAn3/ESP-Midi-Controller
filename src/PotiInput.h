// PotiInput.h
#ifndef PotiInput_h
#define PotiInput_h

#include "Arduino.h"

class PotiInput {
public:
    PotiInput(int pin, long in_min, long in_max);
    int readAndMap();
    bool hasChanged();
    int lastValue;

private:
    int pin;
    long in_min, in_max;
    long mapCustom(long x, long in_min, long in_max, long out_min, long out_max);
};

#endif
