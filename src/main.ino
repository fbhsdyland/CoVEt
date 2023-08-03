#include <Arduino.h>
#include <Tone.h>

#define JOYSTICK_PIN A0
#define BUTTON_PIN 2
#define SPEAKER_PIN 9

Tone tone1;

#define FREQ_MIN 1
#define FREQ_MAX 1023

// button state variable for toggling sound
bool buttonState = false;

void setup() {
  pinMode(JOYSTICK_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  tone1.begin(SPEAKER_PIN);
  
  Serial.begin(9600); // start serial communication on 9600 baud
}

void loop() {
  int joystickVal = analogRead(JOYSTICK_PIN);
  int buttonVal = digitalRead(BUTTON_PIN);
  
  if (buttonVal == LOW) {
    buttonState = !buttonState;
    delay(200); // debounce
  }

  if (buttonState) {
    int mappedFrequency = map(joystickVal, 0, 1023, FREQ_MIN, FREQ_MAX);
    tone1.play(mappedFrequency);
  } else {
    tone1.stop();
  }

  Serial.println(joystickVal); // prints joystick position to serial monitor
}



