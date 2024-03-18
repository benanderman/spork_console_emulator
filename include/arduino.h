#ifndef __ARDUINO_H
#define __ARDUINO_H

#include <stddef.h>
#include <time.h>

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2

#define HIGH 1
#define LOW 0

#define A0 0

#define PROGMEM 

typedef unsigned char uint8_t;
typedef uint8_t byte;

unsigned long millis();

void delay(unsigned long millis);

inline void digitalWrite(uint8_t pin, uint8_t val) {
  
}

inline bool digitalRead(uint8_t pin) {
  return false;
}

inline int random(int min, int max = 0) {
  return 4;
}

inline uint8_t analogRead(uint8_t pin) {
  return 0;
}

inline void analogWrite(uint8_t pin, uint8_t val) {
}

inline void tone(uint8_t pin, uint8_t pitch, uint8_t duration) {
}

inline void randomSeed(int seed) {
  
}

inline void delayMicroseconds(int microSeconds) {

}

inline uint8_t pgm_read_byte(const char *byte) {
  return *byte;
}

inline void pinMode(uint8_t pin, int mode) {

}

#endif
