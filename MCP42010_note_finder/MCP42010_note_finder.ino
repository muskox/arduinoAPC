#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  Serial.begin(9600);
}

void loop() {

  // If you hold the left channel, sound does start until 112, 109, 112, 116
  
  digitalPotWrite(1, 175);
  run256loop(0,175);
/*
  digitalPotWrite(1, 180);
  run256loop(0,180);



  digitalPotWrite(1, 240);
  run256loop(0,240);
*/
 



}


void run256loop(int selectChannel, int otherVal){

  for (int level = 0; level < 256; level++) {
    Serial.print("CHANNEL ");
    Serial.print(selectChannel);
    Serial.print("LEVEL ");
    Serial.print(level);
    Serial.print("                other:");
    Serial.print(otherVal);
    Serial.println(" ");
    digitalPotWrite(selectChannel, level);
    delay(500);

  }

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
