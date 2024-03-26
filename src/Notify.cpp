#include <Arduino.h>
#include "Notify.h"

void notifyConfirmation() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(CONFIRM_LED_PIN, HIGH);
        delay(100);
        digitalWrite(CONFIRM_LED_PIN, LOW);
        delay(100);
    }
}

void notifyError() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(ERROR_LED_PIN, HIGH);
        delay(100);
        digitalWrite(ERROR_LED_PIN, LOW);
        delay(100);
    }
}

void notifyFinalization() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(FINALIZE_LED_PIN, HIGH);
        delay(100);
        digitalWrite(FINALIZE_LED_PIN, LOW);
        delay(100);
    }
}