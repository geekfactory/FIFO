#include "unity.h"
#include "FIFO.h"

void setUp(void) { }

void tearDown(void) { }

void test_FIFO_create(void) {
    fifo_t myfifo = fifo_create(10, sizeof(int));
    TEST_ASSERT(myfifo != NULL)
}

void test_FIFO_add(void) {
    unsigned int fifoSize = 10;
    fifo_t myfifo = fifo_create(fifoSize, sizeof(int));

    for (int i = 0; i < fifoSize; i++) {
        if (!fifo_add(myfifo, &i)) {
            TEST_FAIL();
        }
    }
}

void test_FIFO_addMoreThanSize(void) {
    unsigned int fifoSize = 10;
    unsigned int overflowAmount = 3;
    fifo_t myfifo = fifo_create(fifoSize, sizeof(int));

    unsigned int succeeded = 0;
    unsigned int failed = 0;
    for (int i = 0; i < fifoSize + overflowAmount; i++) {
        if (fifo_add(myfifo, &i)) {
            succeeded += 1;
        } else {
            failed += 1;
        }
    }

    TEST_ASSERT(succeeded == fifoSize);
    TEST_ASSERT(failed == overflowAmount);
}


void test_FIFO_addAndGet(void) {
    unsigned int fifoSize = 10;
    fifo_t myfifo = fifo_create(fifoSize, sizeof(int));

    for (int i = 0; i < fifoSize; i++) {
        fifo_add(myfifo, &i);
    }

    int expectedValue = 0;
    while (!fifo_is_empty(myfifo)) {
        int value;
        fifo_get(myfifo, &value);
        TEST_ASSERT(value == expectedValue);
        expectedValue += 1;
    }

    TEST_ASSERT(expectedValue == fifoSize);
}
