#include "modes/custom/snake.h"

// Game structures

typedef u8 pos_t;

#define SNAKE_KEYPAD_OVERLAP

#define SNAKE_DIR_UP 10
#define SNAKE_DIR_RIGHT 1
#define SNAKE_DIR_DOWN -10
#define SNAKE_DIR_LEFT -1
typedef s8 dir_t;

#define SNAKE_MAX_LEN (8*8)

// Graphic and key bindings

#define snake_tick_time 300

#define snake_key_force 0

#define snake_start_pos 81
#define snake_start_dir SNAKE_DIR_RIGHT

#define snake_key_r 0
#define snake_key_g 0
#define snake_key_b 63

#define snake_head_r 0
#define snake_head_g 63
#define snake_head_b 2

#define snake_body_r 0
#define snake_body_g 63
#define snake_body_b 30

#define snake_food_r 63
#define snake_food_g 0
#define snake_food_b 0

#ifdef SNAKE_KEYPAD_OVERLAP
  #define snake_key_up 27
  #define snake_key_down 17
  #define snake_key_left 16
  #define snake_key_right 18
#else
  #define snake_key_up 6
  #define snake_key_down 7
  #define snake_key_left 5
  #define snake_key_right 8
#endif

// RNG routines

u16 snake_rng_state;

void snake_seed() {
  snake_rng_state = global_timer & 0xFFFF;
}

u16 snake_rng() {
    snake_rng_state ^= snake_rng_state << 5;
    snake_rng_state ^= snake_rng_state >> 7;
    snake_rng_state += 28383;

    return snake_rng_state;
}

pos_t snake_rng_pos() {
  u16 t = snake_rng();
  return 10 * ((t >> 8) % 8) + ((t & 0xF) % 8) + 11;
}

// State

u8 snake_multiple_input;

u16 snake_time;

pos_t snake_food;
pos_t snake[SNAKE_MAX_LEN];
u8 snake_tail, snake_head;
dir_t snake_dir;

u8 snake_valid_pos(pos_t pos) {
  u8 t = (pos % 10);
  if (t < 1 || t > 8)
    return 0;
  t = (pos / 10);
  if (t < 1 || t > 8)
    return 0;
  return 1;
}

u8 snake_issnake(pos_t pos) {
  for (u8 i = snake_tail; i != snake_head; i = (i + 1) % SNAKE_MAX_LEN) {
    if (pos == snake[i])
      return 1;
  }
  return pos == snake[snake_head];
}

void snake_update(pos_t next_pos, u8 grow) {
  #ifndef SNAKE_KEYPAD_OVERLAP
    // Render snake difference
    rgb_led(snake[snake_head], snake_body_r, snake_body_g, snake_body_b);
    rgb_led(snake[snake_tail], 0, 0, 0);
    rgb_led(next_pos, snake_head_r, snake_head_g, snake_head_b);
  #endif

  // Move head
  snake_head += 1;
  snake_head %= SNAKE_MAX_LEN;

  if (!grow) {
    // Shrink
    snake_tail += 1;
    snake_tail %= SNAKE_MAX_LEN;
  }

  snake[snake_head] = next_pos;
}

void snake_gen_food() {
  do {
    snake_food = snake_rng_pos();
  } while(snake_issnake(snake_food));
  #ifndef SNAKE_KEYPAD_OVERLAP
    // Incremental rendering
    rgb_led(snake_food, snake_food_r, snake_food_g, snake_food_b);
  #endif
}

void snake_render_key() {
  rgb_led(snake_key_up, snake_key_r, snake_key_g, snake_key_b);
  rgb_led(snake_key_right, snake_key_r, snake_key_g, snake_key_b);
  rgb_led(snake_key_down, snake_key_r, snake_key_g, snake_key_b);
  rgb_led(snake_key_left, snake_key_r, snake_key_g, snake_key_b);
}

void snake_tick() {
  pos_t next_pos = snake[snake_head] + snake_dir;
  if (!snake_valid_pos(next_pos) || snake_issnake(next_pos)) {
    // If out of bounds or on top of itself
    // Game over!
    text_port = 0;
    text_color = 127;
    text_loop = 1;
    const char gameover_str[] = "Game Over";
    const u8 len = sizeof(gameover_str);
    memcpy(&text_bytes[1], gameover_str, len);
    text_bytes[0] = len;
    text_palette = 0; // Allow exit on touch
    mode_update(mode_text);
    return;
  }

  // Check for food consumption and update status
  u8 grow = next_pos == snake_food;
  snake_update(next_pos, grow);
  if(grow) {
    // Regen food
    snake_gen_food();
  }

  #ifdef SNAKE_KEYPAD_OVERLAP
    // Should render all screen every time :(
    // You could avoid clearing, but makes adding features easier
    clear_led();
    // Render key colors first each time to cope with map overlap
    snake_render_key();
    // The food
    rgb_led(snake_food, snake_food_r, snake_food_g, snake_food_b);
    // The snake (circular buffer makes for with != and modulo...)
    for (u8 i = snake_tail; i != snake_head; i = (i + 1) % SNAKE_MAX_LEN) {
      rgb_led(snake[i], snake_body_r, snake_body_g, snake_body_b);
    }
    // Fill also head
    rgb_led(snake[snake_head], snake_head_r, snake_head_g, snake_head_b);
  #endif

  snake_multiple_input = 0;
}

void snake_init() {
  snake_seed();

  snake_multiple_input = 0;

  #ifndef SNAKE_KEYPAD_OVERLAP
    // Needs only one draw if no overlap
    snake_render_key();
  #endif

  snake_tail = 0;
  snake_head = 0;
  snake[snake_head] = snake_start_pos;
  rgb_led(snake[snake_head], snake_head_r, snake_head_g, snake_head_b);

  snake_dir = snake_start_dir;

  snake_gen_food();
}

void snake_timer_event() {
  if (++snake_time > snake_tick_time) {
    snake_time = 0;
    snake_tick();
  }
}

void snake_surface_event(u8 p, u8 v, u8 x, u8 y) {
  if (p == 0) { // Enter Setup mode
    if (v != 0) mode_update(mode_setup);

  } else if (v > snake_key_force && !snake_multiple_input) {
    snake_multiple_input = 1; // Avoid multiple input in the same frame
    if (p == snake_key_up) {
      snake_dir = SNAKE_DIR_UP;
    } else if (p == snake_key_right) {
      snake_dir = SNAKE_DIR_RIGHT;
    } else if (p == snake_key_down) {
      snake_dir = SNAKE_DIR_DOWN;
    } else if (p == snake_key_left) {
      snake_dir = SNAKE_DIR_LEFT;
    }
  }
}

void snake_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}
void snake_aftertouch_event(u8 v) {}
void snake_poly_event(u8 p, u8 v) {}
