//
// Scroll through the addresses of a 4067, read the analog values,
// and send controller values if there has been a measurable change.
//

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13

#define MUX_BIT_0 12
#define MUX_BIT_1 11
#define MUX_BIT_2 10
#define MUX_BIT_3 9

#define NOISE_THRESHOLD 7

int channel = 1;
int controller_numbers[] = {
  1, 7, 19, 71, 74, 80, 81, 91, 2, 16,
  100, 101, 102, 103, 104, 105
};

int address, mux_bit_0, mux_bit_1, mux_bit_2, mux_bit_3;

int values[] = {0, 0, 0, 0, 
  0, 0, 0, 0, 
  0, 0, 0, 0, 
  0, 0, 0, 0};

int new_value;
void setup()
{
  pinMode(MUX_BIT_0, OUTPUT);
  pinMode(MUX_BIT_1, OUTPUT);
  pinMode(MUX_BIT_2, OUTPUT);
  pinMode(MUX_BIT_3, OUTPUT);

  pinMode(LED, OUTPUT);
  
  MIDI.begin();
}

void loop () {

  for (address = 0; address < 16; address++) {

    mux_bit_0 = bitRead(address, 0);
    mux_bit_1 = bitRead(address, 1);
    mux_bit_2 = bitRead(address, 2);
    mux_bit_3 = bitRead(address, 3);

    digitalWrite(MUX_BIT_0, mux_bit_0);
    digitalWrite(MUX_BIT_1, mux_bit_1);
    digitalWrite(MUX_BIT_2, mux_bit_2);
    digitalWrite(MUX_BIT_3, mux_bit_3);

delay(1);

    new_value = analogRead(A0);
    
    if (abs(new_value - values[address]) > NOISE_THRESHOLD) {

      digitalWrite(LED, HIGH);
      
      MIDI.sendControlChange(controller_numbers[address], new_value >> 3, channel);
      values[address] = new_value;
      
      digitalWrite(LED, LOW);
      
    }

  }

}



