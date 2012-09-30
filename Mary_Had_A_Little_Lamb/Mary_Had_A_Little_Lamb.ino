#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
}

void loop() {
  // Write the song in 190 scale

  digitalPotWrite(1, 190);
  digitalPotWrite(0, 40);
  delay(1000);
  digitalPotWrite(0, 15);
  delay(1000);
  digitalPotWrite(0, 1);
  delay(1000);
  digitalPotWrite(0, 15);
  delay(1000);
  
  digitalPotWrite(0, 40);
  delay(1000);
  hold_silence(200);
  digitalPotWrite(0, 40);
  delay(1000);
  hold_silence(200);
  digitalPotWrite(0, 40);
  delay(1000);
  hold_silence(200);
  digitalPotWrite(0, 15);
  delay(2000);
  hold_silence(200);


}

void hold_silence(int millisecs, int scale){
  digitalPotWrite(1, 40); // Right channel 1 will go silent below around 106
  delay(millisecs);
  digitalPotWrite(1, 190); // Put it back to the scale we were on
}


int digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI:
  // http://ww1.microchip.com/downloads/en/devicedoc/11195c.pdf

  // MCP42010 - command byte, data byte in 16 bit register
  // command byte is 8 bits, to write XX01XX01 for pot0, XX01XX10 for pot1, or xx01XX11 for both
  // data byte is 8 bit 256 choice

  // for command bytes, 00010001 = 17, 00010010 = 18

  int command_byte = 0;

  if (address == 0){
    command_byte = 17;
  }
  if (address == 1){
    command_byte = 18;
  }

  SPI.transfer(command_byte);
  SPI.transfer(value);

  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH);
}
