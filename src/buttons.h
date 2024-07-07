#include <Arduino.h>
#include <MidiHelper.h>

bool BUTTONS_ENABLE = true;
const int N_BUTTONS = 3;
const int buttonPin[N_BUTTONS] = { 2, 3, 4 };
int buttonNote[N_BUTTONS] = { 36, 38, 42};

int buttonState[N_BUTTONS] = { 0, 0, 0 };
int buttonPreviousState[N_BUTTONS] = { 0, 0, 0 };

int Button_CH = 0;


int debounceDelay = 50;
unsigned long lastDebounceTime[N_BUTTONS] = {0};
unsigned long debounceTimer[N_BUTTONS] = {0};

void SetButtonEnable(int x){
    BUTTONS_ENABLE = x;
}

void SetupButtons(){
    if(!BUTTONS_ENABLE)
        return;
    for(int i = 0; i < sizeof(buttonPin) / sizeof(int); i++){
        pinMode(buttonPin[i], INPUT_PULLUP);
    }
}

void ButtonsLoop(){

    if(!BUTTONS_ENABLE)
        return;

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