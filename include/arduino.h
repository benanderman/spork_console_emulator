#ifndef __ARDUINO_H
#define __ARDUINO_H

#include <algorithm>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2

#define HIGH true
#define LOW false

#define A0 0

#define PROGMEM 

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))

typedef unsigned char uint8_t;
typedef uint8_t byte;

unsigned long millis();

void delay(unsigned long millis);

void digitalWrite(uint8_t pin, bool val);

bool digitalRead(uint8_t pin);

void pinMode(uint8_t pin, int mode);

inline int random(int min, int max) {
  return min + int(rand() % (max - min));
}

inline int random(int max) {
  return random(0, max);
}

inline uint8_t analogRead(uint8_t pin) {
  return random(256);
}

inline void analogWrite(uint8_t pin, uint8_t val) {
}

inline void tone(uint8_t pin, uint8_t pitch, uint8_t duration) {
}

inline void randomSeed(int seed) {
  srand(seed);
}

inline void delayMicroseconds(int microSeconds) {

}

inline uint8_t pgm_read_byte(const char *byte) {
  return *byte;
}

#endif
