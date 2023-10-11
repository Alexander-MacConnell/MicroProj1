#include <Arduino.h>


int counter = 0;
bool buttonPressed = false;
bool toggle1 = 0;
int ledPin = PIN_A11;

void pin_ISR() {

  buttonPressed = true;

}

void setup() {
  Serial.begin(9600);
  //Initialize pins
  pinMode(PIN_A9, INPUT);
  pinMode(PIN_A10, OUTPUT);
  pinMode(PIN_A11, OUTPUT);
  pinMode(PIN_A12, OUTPUT);

  attachInterrupt(0, pin_ISR, CHANGE);

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 7812;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts

}

ISR(TIMER1_COMPA_vect) { //timer1 interrupt 1Hz

  if (toggle1 == 1) {

    digitalWrite(ledPin, HIGH);

    toggle1 = 0;
    counter++;

  }

  else if (toggle1 == 0) {

    digitalWrite(ledPin, LOW);

    toggle1 = 1;
    counter++;

  }

}

void loop() {
  
  while(buttonPressed == false){
    
    if(counter == 0){

      digitalWrite(PIN_A12, HIGH);

    }

    else if(counter == 2){

      digitalWrite(PIN_A12, LOW);

    }

    if(counter == 4) {

      counter = 0;

    }

  }

  counter = 0;

  while(counter <= 48) {

    if(counter <= 2) {

      ledPin = 13;

      digitalWrite(PIN_A12, HIGH);

    }

    if(counter >= 42 && ledPin == 13) {

      Serial.println(counter);

      ledPin = PIN_A12;

    }

  }

  ledPin = 13;
  counter = 0;





}