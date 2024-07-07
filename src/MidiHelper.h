#ifndef MISIHELPER_H
#include <MIDIUSB.h>

void noteOn(byte channel, byte pitch, byte velocity){
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void controlChange(byte channel, byte control, byte value){
  midiEventPacket_t event = {0x0B, 0x0B | channel, control, value};
  MidiUSB.sendMIDI(event);
}

#define MIDIHELPER_H
#endif