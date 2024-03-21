#include <SDL.h>
#include <map>

#include "arduino.h"
#include "renderer.h"
#include "spork_console/config.h"
#include "spork_console/controller.h"

class EmuController {
public:
  int data_pin;

  EmuController(int data_pin): data_pin(data_pin) {
    // TODO: Support different configs for different controllers.
    key_bindings[Controller::Button::b] = SDL_SCANCODE_A;
    key_bindings[Controller::Button::a] = SDL_SCANCODE_S;
    key_bindings[Controller::Button::select] = SDL_SCANCODE_RETURN;
    key_bindings[Controller::Button::start] = SDL_SCANCODE_TAB;
    key_bindings[Controller::Button::down] = SDL_SCANCODE_DOWN;
    key_bindings[Controller::Button::right] = SDL_SCANCODE_RIGHT;
    key_bindings[Controller::Button::up] = SDL_SCANCODE_UP;
    key_bindings[Controller::Button::left] = SDL_SCANCODE_LEFT;
  }

  void update_button_states() {
    SDL_PumpEvents();
    const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
    
    button_states.clear();
    for (int i = 0; i < Controller::Button::__count; i++) {
      button_states.push_back(keyboard_state[key_bindings[i]] != 0);
    }
  }

  bool read_value() {
    return button_states.back();
  }

  void shift_data() {
    button_states.pop_back();
  }

private:
  std::vector<bool> button_states;
  std::map<int, uint8_t> key_bindings;
};

static int arduino_pins[] = {
  DISPLAY_RCLK_PIN,
  DISPLAY_SRCLK_PIN,
  DISPLAY_SER_PIN,
  DISPLAY_OE_PIN,
  AUDIO_PIN,

  CONSOLE_LEFT_BUTTON_PIN,
  CONSOLE_RIGHT_BUTTON_PIN,

  CONTROLLER_SHLD_PIN,
  CONTROLLER_CLK_PIN,

  CONTROLLER_1_SER_PIN,
  CONTROLLER_1_CONN_PIN,
  CONTROLLER_2_SER_PIN,
  CONTROLLER_2_CONN_PIN,

  CONTROLLER_AUX_SHLD_PIN,
  CONTROLLER_AUX_CLK_PIN,
  CONTROLLER_AUX_SER_PIN,
  CONTROLLER_AUX_CONN_PIN,
};

static std::map<int, bool> pin_states;

static EmuController controller(CONTROLLER_1_SER_PIN);

unsigned long millis() {
  return SDL_GetTicks();
}

void delay(unsigned long millis) {
  SDL_Event e;

  // Get any pending event.
  SDL_PollEvent(&e);

  // User requests quit
  if (e.type == SDL_QUIT) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
  }

  SDL_Delay(millis);
}

void digitalWrite(uint8_t pin, bool val) {
  bool old_val = pin_states[pin];
  pin_states[pin] = val;

  if (pin == CONTROLLER_CLK_PIN && val == true && old_val == false) {
    if (pin_states[CONTROLLER_SHLD_PIN]) {
      controller.shift_data();
    } else {
      controller.update_button_states();
    }
  }
}

bool digitalRead(uint8_t pin) {
  if (pin == controller.data_pin) {
    return controller.read_value();
  }
  if (pin == CONTROLLER_1_CONN_PIN) {
    return true;
  }
  return false;
}

void pinMode(uint8_t pin, int mode) {

}
