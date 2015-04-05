#include <pebble_worker.h>
// #include <pebble.h>




// Called when a message is received from PebbleKitJS
static void in_received_handler(DictionaryIterator *received, void *context) {
  Tuple *tuple;
  
  tuple = dict_find(received, 0);
  if(tuple) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Status: %d", (int)tuple->value->uint8); 
  }
  
//   tuple = dict_find(received, MESSAGE_KEY);
//   if(tuple) {
//     APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Message: %s", tuple->value->cstring);
//   }
  //Renders display                                                                                          
  //Layer *window_layer = window_get_root_layer(window);
  //GRect window_bounds = layer_get_bounds(window_layer);

  //text_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  //text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  //text_layer_set_text(text_layer, "Get Back to Work!");

  //Vibrates device                                                                                          
  vibes_long_pulse();

}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
}

void init(void) {

  
  // Register AppMessage handlers
  app_message_register_inbox_received(in_received_handler); 
  app_message_register_inbox_dropped(in_dropped_handler); 
  app_message_register_outbox_failed(out_failed_handler);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
}

void deinit(void) {
  app_message_deregister_callbacks();

}

int main( void ) {
  init();
  app_event_loop();
  deinit();
}

