#include <Arduino.h>
#include <MIDIUSB.h>

void noteOn(byte channel, byte pitch, byte velocity);

const int N_BUTTONS = 3;
const int buttonPin[N_BUTTONS] = { 2, 3, 4 };
int buttonNote[N_BUTTONS] = { 36, 38, 42};

int buttonState[N_BUTTONS] = { 0, 0, 0 };
int buttonPreviousState[N_BUTTONS] = { 0, 0, 0 };

int Button_CH = 0;


int debounceDelay = 50;
unsigned long lastDebounceTime[N_BUTTONS] = {0};
unsigned long debounceTimer[N_BUTTONS] = {0};


void setup() {
  Serial.begin(9600);
  for(int i = 0; i < sizeof(buttonPin) / sizeof(int); i++){
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

void loop() {

  for(int i = 0; i < sizeof(buttonPin) / sizeof(int); i++){

    debounceTimer[i] = millis() - lastDebounceTime[i];

    buttonState[i] = digitalRead(buttonPin[i]);
     
    if(debounceTimer[i] > debounceDelay){
     
      if(buttonState[i] != buttonPreviousState[i]){
        
        lastDebounceTime[i] = millis();
        
        if(debounceTimer[i] > debounceDelay){
          if(buttonState[i] == LOW){
            noteOn(Button_CH, buttonNote[i], 127);   
            MidiUSB.flush();     
          }else{ // Released
            noteOn(Button_CH, buttonNote[i], 0);        
            MidiUSB.flush();
          }
        }    
     
        buttonPreviousState[i] = buttonState[i];
      }
    }
  }
}

// --------------- MIDI -----------------------------------

void noteOn(byte channel, byte pitch, byte velocity){
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void controlChange(byte channel, byte control, byte value){
  midiEventPacket_t event = {0x0B, 0x0B | channel, control, value};
  MidiUSB.sendMIDI(event);
}