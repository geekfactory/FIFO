/**
   GeekFactory - "INNOVATING TOGETHER"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx

   This example shows the basic usage of the FIFO library. We create a FIFO,
   then we fill it with some data and then dump the data to the serial monitor.
*/
#include "FIFO.h"

// array of test data
char data[] = "Hola Mundo!!!!";
// type to store a FIFO reference
fifo_t myfifo;

void setup() {
  // prepare serial interface
  Serial.begin(115200);
  while (!Serial);

  // show message on serial monitor
  Serial.println(F("----------------------------------------------------"));
  Serial.println(F("             FIFO LIBRARY TEST PROGRAM              "));
  Serial.println(F("             https://www.geekfactory.mx             "));
  Serial.println(F("----------------------------------------------------"));

  // create a FIFO (queue) capable of storing 10 items
  myfifo = fifo_create(10, sizeof(char));

  // check if FIFO was created
  if (myfifo == NULL) {
    Serial.println(F("Cannot create FIFO... halting!"));
    for (;;);
  } else {
    Serial.println(F("FIFO created successfully"));
  }

  // put some data on the fifo buffer
  Serial.println(F("\r\nFILLING FIFO WITH DATA..."));
  for (unsigned int i = 0; i < sizeof(data); i++)
  {
    Serial.print(F("Add item to FIFO: "));
    Serial.print(data[i]);
    if (fifo_add(myfifo, &data[i])) {
      Serial.println(F(" (OK)"));
    } else {
      Serial.println(F(" (FAIL)"));
    }
  }

  // get data from FIFO
  Serial.println(F("\r\nGETTING DATA FROM FIFO..."));
  // dump data from FIFO to serial monitor
  while (!fifo_is_empty(myfifo)) {
    char c;
    fifo_get(myfifo, &c);
    Serial.print(c);
  }

  // end of test program
  Serial.println(F("DONE"));
}

void loop() {
  // Do nothing here

}