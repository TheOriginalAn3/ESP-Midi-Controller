// PotiInput.cpp
#include "PotiInput.h"

PotiInput::PotiInput(int pin, long in_min, long in_max) : pin(pin), in_min(in_min), in_max(in_max), lastValue(-1) {
    pinMode(pin, INPUT);
}

int PotiInput::readAndMap() {
    int value = analogRead(pin);
    int mappedValue = mapCustom(value, in_min, in_max, 0, 127);
    return mappedValue;
}

bool PotiInput::hasChanged() {
    int currentValue = readAndMap();
    if (currentValue != lastValue) {
        lastValue = currentValue;
        return true;
    }
    return false;
}

long PotiInput::mapCustom(long x, long in_min, long in_max, long out_min, long out_max) {
    if (x > in_max) {
        return out_max;
    }
    const long run = in_max - in_min;
    if (run == 0) {
        log_e("mapCustom(): Invalid input range, min == max");
        return -1; // Error value
    }
    const long rise = out_max - out_min;
    const long delta = x - in_min;
    long mappedValue = (delta * rise) / run + out_min;
    return mappedValue > out_max ? out_max : mappedValue;
}
