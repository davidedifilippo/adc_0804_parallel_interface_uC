#include <Arduino.h>

#include<IO_Port_8bit.h>


IO_Port_8bit myport(3,4,5,6,7,8,9,10,'I');

//assegnazione dei pin
const int chipselectPin = 11;
const int writePin = 12;
const int readPin = 13;
const int interruptPin = 2;


bool read = false;

void ready()
{
read = true;  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
   
  //turn on pullup resistor and attach interrupt to pin 2

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ready, FALLING);

  digitalWrite(chipselectPin, HIGH);
  digitalWrite(writePin, HIGH);
  delay(10);
  digitalWrite(chipselectPin, LOW);
  digitalWrite(writePin, LOW);
  Serial.println("Linea interrupt: "+ digitalRead(interruptPin));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (read)
  {
    Serial.println("Reading...");
    Serial.println("Linea interrupt: "+ digitalRead(interruptPin));
    digitalWrite(readPin, LOW);
    
    //Leggo il dato

    int input_byte;
    input_byte = myport.get_8bit_data();
    Serial.print("received input = ");
    Serial.println(input_byte);

    read = false;
    digitalWrite(chipselectPin, HIGH);
    digitalWrite(writePin, HIGH);
    delay(10);
    digitalWrite(chipselectPin, LOW);
    digitalWrite(writePin, LOW);
  }
  delay(1000);
}
