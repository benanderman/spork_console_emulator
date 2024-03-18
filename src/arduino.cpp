#include <SDL.h>

#include "arduino.h"

unsigned long millis() {
  return SDL_GetTicks();
}

void delay(unsigned long millis) {
  SDL_Event e;

  // Wait indefinitely for the next available event
  SDL_PollEvent(&e);

  // User requests quit
  if (e.type == SDL_QUIT) {
      SDL_Quit();
  }

  SDL_Delay(millis);
}
