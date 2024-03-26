#ifndef NOTIFY_H
#define NOTIFY_H

#define CONFIRM_LED_PIN 11
#define FINALIZE_LED_PIN 12
#define ERROR_LED_PIN 13

void notifyConfirmation();
void notifyError();
void notifyFinalization();

#endif
