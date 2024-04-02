#include <Arduino.h>
#include "Notify.h"

void notifyBLEOn() {
    digitalWrite(BLE_LED_PIN, HIGH);
    delay(100);
    for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
    }

}

void notifyBLEConnected() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
        delay(50);
    }
    delay(100);
    digitalWrite(BLE_LED_PIN, LOW);
}

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
        delay(200);
        digitalWrite(FINALIZE_LED_PIN, HIGH);
        delay(100);
        digitalWrite(FINALIZE_LED_PIN, LOW);
        delay(200);
        digitalWrite(FINALIZE_LED_PIN, HIGH);
        delay(100);
    }
}