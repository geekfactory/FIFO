/**
   GeekFactory - "INNOVATING TOGETHER"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx

   This example shows how to store structs in a FIFO buffer and
   communicate two functions.
*/
#include "FIFO.h"

// message structure that is stored on the FIFO
struct message_struct
{
  uint32_t tstamp;
  int32_t temperatures[3];
};

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
  myfifo = fifo_create(10, sizeof(struct message_struct));

  // check if FIFO was created
  if (myfifo == NULL) {
    Serial.println(F("Cannot create FIFO... halting!"));
    for (;;);
  } else {
    Serial.println(F("FIFO created successfully"));
  }
}

void loop() {
  // consumer task
  task_consumer();
  // producer task
  task_producer();
}

void task_consumer()
{
  struct message_struct fifodata;

  if (!fifo_is_empty(myfifo)) {
    fifo_get(myfifo, &fifodata);
    Serial.print(F("Consumer got item: "));
    Serial.println(fifodata.tstamp);
    Serial.print(F("Item contains: "));
    Serial.print(fifodata.temperatures[0]);
    Serial.print(' ');
    Serial.print(fifodata.temperatures[1]);
    Serial.print(' ');
    Serial.println(fifodata.temperatures[2]);
    Serial.println();
  }
}

void task_producer()
{
  static uint32_t lastTime = 0;
  struct message_struct fifodata;

  // put items on the FIFO periodically
  if (millis() - lastTime >= 5000)
  {
    lastTime = millis();

    Serial.print(F("Producer creates item: "));
    Serial.println(lastTime);

    fifodata.tstamp = lastTime;
    fifodata.temperatures[0] = 21;
    fifodata.temperatures[1] = 22;
    fifodata.temperatures[2] = 23;

    if (fifo_add(myfifo, &fifodata)) {
      Serial.println(F("Item was added to queue!"));
    }
  }
}