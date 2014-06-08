#include "pebble.h"

static Window *window;  /* Create a Window object */

static TextLayer *time_layer; /* Create a TextLayer object */
static TextLayer *title_layer; /* Create a TextLayer object */

static void init() {
  window = window_create(); /* Create Window */
  window_stack_push(window, true /* Animated */); /* Add the Window Layer to the Window stack */

  Layer *window_layer = window_get_root_layer(window);  /* Get the root layer of the Window */
  GRect bounds = layer_get_frame(window_layer); /* Get the boundaries for the Window */

  /* Grab the time */
  char time_str[100];
  clock_copy_time_string(time_str, 100);

  /* Make Title TextLayer */
  title_layer = text_layer_create((GRect){ .origin = { 0, 10 }, .size = bounds.size });  /* Allocate TextLayer and initialize origin and size */
  text_layer_set_text(title_layer, "Welcome to Fifteen!");  /* Set text in the TextLayer */
  text_layer_set_font(title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD)); /* Set TextLayer font */
  text_layer_set_text_alignment(title_layer, GTextAlignmentCenter);  /* Align TextLayer */
  layer_add_child(window_layer, text_layer_get_layer(title_layer)); /* Add TextLayer to window_layer as a child */

  /* Make Time TextLayer */
  time_layer = text_layer_create((GRect){ .origin = { 0, 50 }, .size = bounds.size });  /* Allocate TextLayer and initialize origin and size */
  text_layer_set_text(time_layer, strcat("The time is now ", time_str));  /* Set text in the TextLayer */
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14)); /* Set TextLayer font */
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);  /* Align TextLayer */
  layer_add_child(window_layer, text_layer_get_layer(time_layer)); /* Add TextLayer to window_layer as a child */
}

static void deinit() {
  text_layer_destroy(time_layer);
  text_layer_destroy(title_layer);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
