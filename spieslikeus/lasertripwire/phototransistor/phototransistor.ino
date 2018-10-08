// Project 1 – Photo transistor

#include "pitches.h"

int LED = 13;                         //define LED digital pin 13
int val = 0;            //define the voltage value of photo diode in digital pin 0
int speaker = 2;

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup(){
  pinMode(LED,OUTPUT);                // Configure LED as output mode
  Serial.begin(9600);                 //Configure baud rate 9600
}

void loop(){
  val = analogRead(0);                // Read voltage value ranging from 0 -1023
  Serial.println(val);                         // read voltage value from serial monitor
  
  if(val<600){                                  // If lower than 1000, turn off LED
    digitalWrite(LED,HIGH);
    digitalWrite(speaker,HIGH);
    soundAlarm();    
  }
  else{                                              // Otherwise turn on LED
    digitalWrite(LED,LOW);    
    noTone(speaker);
  }
  delay(100);                                      // delay for 10ms
}

void soundAlarm() {  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speaker, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speaker);
  }
}

