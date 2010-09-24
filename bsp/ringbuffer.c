#include "ringbuffer.h"

void initRingBuffer(ringbuffer_t* rb, uint8_t* buffer, const size_t size)
{
  rb->size = size;
  rb->writer = 0;
  rb->reader = 0;
  rb->buffer = buffer;
}

size_t usedRingBuffer(const ringbuffer_t* rb)
{
  const size_t d = rb->writer - rb->reader;
  return (d>=0) ? d : rb->size + d; 
}

size_t freeRingBuffer(const ringbuffer_t* rb)
{
  return rb->size - usedRingBuffer(rb);
}

bool writeRingBuffer(ringbuffer_t* rb, const uint8_t v)
{
  if (freeRingBuffer(rb) > 0) {
    rb->buffer[rb->writer] = v;
    rb->writer = (rb->writer + 1) % rb->size;
    return true;
  } else {
    return false;
  }
}

bool readRingBuffer(ringbuffer_t* rb, uint8_t* v)
{
  if (usedRingBuffer(rb) > 0) {
    *v = rb->buffer[rb->reader];
    rb->reader = (rb->reader + 1) % rb->size;
    return true;
  } else {
    return false;
  } 
}


