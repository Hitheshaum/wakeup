#include <pebble.h>

static Window *main_window;
static TextLayer *time_layer;

static void main_window_load(Window *window) {
  // Create time TextLayer
  time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_text(time_layer, "00:00");

  // Improve the layout to be more like a watchface
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(time_layer);
}

static void tick_handler(struct tm tick_time, TimeUnits units_changed) {
  update_time();
}

static void update_time() {

  //Get a tm structure
  time t temp = time(NULL)
  struct tm *tick_time = localtme(&temp);
  
  static char buffer[] = "00:00";

  if(clock_is_24h_style() == true) {
    strftime(buffer, sizeof("00:00"), "%H:%M",tick_time);
  }
  else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);

}

static void init() {
  // Create main Window element and assign to pointer
  main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = main_window_load,
      .unload = main_window_unload
	});

  // Show the Window on the watch, with animated=true
  window_stack_push(main_window, true);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  window_destroy(main_window)
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
