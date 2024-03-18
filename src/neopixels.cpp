#include "spork_console/neopixels.h"
#include "renderer.h"

#include <iostream>

static uint32_t video_buffer[200];
static int video_buffer_index = 0;

static const int CONSOLE_DISP_WIDTH = 10;
static const int CONSOLE_DISP_HEIGHT = 20;

void Neopixels::ledSetup() {
  
}

void Neopixels::sendPixel(unsigned char r, unsigned char g , unsigned char b)  {
  uint32_t pixel = (r << 16) | (g << 8) | (b << 0);
  video_buffer[video_buffer_index] = pixel;
  video_buffer_index++;
}


// Just wait long enough without sending any bots to cause the pixels to latch and display the last sent frame

void Neopixels::show() {
	// Declare rect of square
	SDL_Rect pixelRect;

	pixelRect.w = SCREEN_WIDTH / CONSOLE_DISP_WIDTH;
	pixelRect.h = SCREEN_HEIGHT / CONSOLE_DISP_HEIGHT;

	// Event loop
	for (int y = 0; y < CONSOLE_DISP_HEIGHT; y++) {
		for (int x = 0; x < CONSOLE_DISP_HEIGHT; x++) {
			uint32_t pixel = video_buffer[y * CONSOLE_DISP_WIDTH + x % CONSOLE_DISP_WIDTH];

			pixelRect.x = x * pixelRect.w;
			pixelRect.y = y * pixelRect.h;

	    SDL_SetRenderDrawColor(renderer, ((pixel >> 16) & 0xF) * 16, ((pixel >> 8) & 0xF) * 16, (pixel & 0xF) * 16, 0xFF);

	    SDL_RenderFillRect(renderer, &pixelRect);
		}
	}

  // Update screen
  SDL_RenderPresent(renderer);
  
  video_buffer_index = 0;
}
