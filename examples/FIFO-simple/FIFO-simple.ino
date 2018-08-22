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
