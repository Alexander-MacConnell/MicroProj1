// Micro 2 Project 1
// Group 3: Alexander MacConnell, Andrew Woods, Omar Said


#include <Arduino.h>


int counter = 0;
bool buttonPressed = false;
bool toggle1 = 0;
int ledPin = 13;

void buttonFunc() {

  buttonPressed = true;

}

void setup() {

  Serial.begin(9600);

  // Initialize pins
  pinMode(PIN_A8, OUTPUT); // Buzzer
  pinMode(PIN_A10, OUTPUT); // Green LED
  pinMode(PIN_A11, OUTPUT); // Yellow LED
  pinMode(PIN_A12, OUTPUT); // Red LED

  attachInterrupt(0, buttonFunc, CHANGE); // Attach interrupt to button

  // Set up timer1 for 2Hz interrupt, adapted from code provided in specification document
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 7812; // Changed from 15624 to 7812 for 2Hz
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);
  sei();

}

// Interrupt timer, counter, and toggle for LEDs and buzzer
ISR(TIMER1_COMPA_vect) {

  if (toggle1 == 1) {

    digitalWrite(ledPin, HIGH);

    if(ledPin != 13) {

      digitalWrite(PIN_A8, HIGH);

    }

    toggle1 = 0;
    counter++;

  }

  else if (toggle1 == 0) {

    digitalWrite(ledPin, LOW);

    if(ledPin != 13) {

      digitalWrite(PIN_A8, LOW);

    }

    toggle1 = 1;
    counter++;

  }

}

void loop() {
  
  // Flash red LED 1Hz until button is pressed
  while(buttonPressed == false){
    
    if(counter == 0){ // LED on for 1 second

      digitalWrite(PIN_A12, HIGH);

    }

    else if(counter == 2){ // LED off for 1 second

      digitalWrite(PIN_A12, LOW);

    }

    if(counter == 4) {

      counter = 0;

    }

  }


  counter = 0; // Reset counter

  while(counter <= 48) {

    if(counter <= 2) {  // Turn on red LED for 21 seconds

      ledPin = 13;

      digitalWrite(PIN_A12, HIGH);

    }

    if(counter >= 42 && ledPin == 13) { // Flash red LED and beep buzzer for 3 seconds

      Serial.println(counter);

      ledPin = PIN_A12;

    }

  }

  digitalWrite(PIN_A8, LOW); // Turn off buzzer
  digitalWrite(PIN_A12, LOW); // Turn off red LED
  ledPin = 13; // Reset ledPin
  counter = 0; // Reset counter


  while(counter <= 40) {

    if(counter <= 2) { // Turn on green LED for 17 seconds

      ledPin = 13;

      digitalWrite(PIN_A10, HIGH);

    }

    if(counter >= 34 && ledPin == 13) { // Flash green LED and beep buzzer for 3 seconds

      Serial.println(counter);

      ledPin = PIN_A10;

    }

  }

  digitalWrite(PIN_A8, LOW); // Turn off buzzer
  digitalWrite(PIN_A10, LOW); // Turn off green LED
  ledPin = 13; // Reset ledPin
  counter = 0; // Reset counter


  while(counter <= 6) {

    if(counter <= 2) { // Turn on yellow LED and beep buzzer for 3 seconds

      ledPin = 14;

      digitalWrite(PIN_A11, HIGH);

    }

    Serial.println(counter);

  }

  digitalWrite(PIN_A8, LOW); // Turn off buzzer
  digitalWrite(PIN_A11, LOW); // Turn off yellow LED
  ledPin = 13; // Reset ledPin

}