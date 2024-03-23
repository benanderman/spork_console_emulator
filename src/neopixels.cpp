#include "spork_console/neopixels.h"
#include "renderer.h"

#include <iostream>
#include <cstdio>

const int NUM_PIXELS = 200;

static uint32_t video_buffer[NUM_PIXELS];
static int video_buffer_index = 0;

static const int CONSOLE_DISP_WIDTH = 10;
static const int CONSOLE_DISP_HEIGHT = 20;

void Neopixels::ledSetup() {
  
}

void Neopixels::sendPixel(unsigned char r, unsigned char g , unsigned char b)  {
  uint32_t pixel = (r << 16) | (g << 8) | (b << 0);
  video_buffer[video_buffer_index] = pixel;
  video_buffer_index = (video_buffer_index + 1) % NUM_PIXELS;
}


// Just wait long enough without sending any bots to cause the pixels to latch and display the last sent frame

void Neopixels::show() {
  SDL_RenderClear(renderer);

  // Declare rect of square
  SDL_Rect pixelRect;

  pixelRect.w = SCREEN_WIDTH / CONSOLE_DISP_WIDTH;
  pixelRect.h = SCREEN_HEIGHT / CONSOLE_DISP_HEIGHT;

  for (int y = 0; y < CONSOLE_DISP_HEIGHT; y++) {
    for (int x = 0; x < CONSOLE_DISP_WIDTH; x++) {
      int pixel_index = y * CONSOLE_DISP_WIDTH + x % CONSOLE_DISP_WIDTH;
      if (pixel_index >= NUM_PIXELS) {
        continue;
      }
      uint32_t pixel = video_buffer[pixel_index];

      pixelRect.x = x * pixelRect.w;
      pixelRect.y = y * pixelRect.h;

      uint8_t r = ((pixel >> 16) & 0xF) * 16;
      uint8_t g = ((pixel >>  8) & 0xF) * 16;
      uint8_t b = ((pixel >>  0) & 0xF) * 16;
      SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
      // printf("%d:%d - %d/%d/%d\n", y, x, r, g, b);

      SDL_RenderFillRect(renderer, &pixelRect);
    }
  }

  // Update screen
  SDL_RenderPresent(renderer);
  
  video_buffer_index = 0;
}
