# Geek Factory FIFO Library #
This is a generic FIFO buffer that can be used to store any kind of items. It is written in C language and can be compiled and used on almost any architecture. It was designed to be used on memory limited architectures such as microcontrollers. Examples of the applications that can be built with this library include:

* Work queues.
* Message queues.
* FIFO buffers for data I/O.
* Program synchronization.
* Any other applications that requires FIFO style data storage.

As with most of our libraries, it is designed to run on the popular Arduino platform as well as other common architectures, such as the PIC16 and PIC 18 microcontrollers from Microchip.

## Basic library usage ##

The following example ilustrates the library usage.


```c
#include "FIFO.h"

// Array of test data
char data[] = "Hola Mundo!!!!";

void setup() {
  Serial.begin(115200);

  // Create a FIFO (queue) capable of storing 10 items
  fifo_t myfifo = fifo_create(10, sizeof(char));

  // Check if FIFO was created
  if (myfifo == NULL) {
    Serial.println(F("Cannot create FIFO... stopping"));
    for (;;);
  }

  // Put data to FIFO
  for (int i = 0; i < sizeof(data); i++)
  {
    char c = data[i];
    Serial.print(F("Adding item to fifo: "));
    Serial.print(c);
    if (fifo_add(myfifo, &c)) {
      Serial.println(F(" ...OK"));
    } else {
      Serial.println(F(" ...FAIL"));
    }
  }

  // Get data from FIFO
  Serial.println(F("\r\nNow get data from FIFO"));
  // Dump data from FIFO to serial monitor
  while (!fifo_empty(myfifo)) {
    char c;
    fifo_get(myfifo, &c);
    Serial.print(c);
  }

  // Check for empty FIFO
  Serial.println();
  if (fifo_empty(myfifo)) {
    Serial.println(F("FIFO Empty"));
  } else {
    Serial.println(F("FIFO NOT Empty"));
  }

  // End of test program
  Serial.println(F("Done."));
}

void loop() {
  // Do nothing here

}
```

## Project objectives ##

* Improve program modularity and reliability by creating common data structures.
* Provide a portable implementation of a FIFO data structure.
* Strong portability, especially on embedded systems, by using C language.
* Provide functions for static memory allocation applications.
* Easy to configure, use and understand.

## Supported devices ##

This library was developed/tested on the following boards

* Arduino UNO R3
* Arduino Mega 2560 R3

## Contact me ##

* Feel free to write for any inquiry: ruben at geekfactory.mx 
* Check our website: https://www.geekfactory.mx

