#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ringbuffer {
  size_t size;
  size_t writer;
  size_t reader;
  uint8_t* buffer;
} ringbuffer_t;

void initRingBuffer(ringbuffer_t* rb, uint8_t* buffer, const size_t size);
size_t usedRingBuffer(const ringbuffer_t* rb);
size_t freeRingBuffer(const ringbuffer_t* rb);
bool readRingBuffer(ringbuffer_t* rb, uint8_t* v);
bool writeRingBuffer(ringbuffer_t* rb, const uint8_t v);

#endif /* __RINGBUFFER_H__ */
