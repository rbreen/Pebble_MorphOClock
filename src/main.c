#include <pebble.h>
#include "animate.h"

/***** TYPE DEFS ****/
typedef struct {
  int hours;
  int minutes;
} Time;

/***** GLOBALS ****/
static Window *s_main_window;
static Layer *s_canvas_layer;

static GPoint s_center;
static Time s_last_time, s_anim_time;


/**** The real time update handler ****/
static void update_time() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Update time called.");

  // Get a tm structure
  time_t temp = time(NULL); 
  // Convert to current timezone
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);

  // Display this time on the TextLayer
}

/**** main constructor for the app ****/
static void main_window_load(Window *window){
  // Create layer and set settings
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Main window loaded.");
}

static void main_window_unload(Window *window){
  // Destroy everything created in the main_window_load
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Main window destroyed.");
}

/**** Handler that is registered for time update callbacks with the OS ****/
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  //Find out which numbers have changed and register animations for all of them.
  update_time();
}

/**** Initialize the application/Watchface ****/
static void init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Init called.");

  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Init with correct time
  update_time();
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "De-init called.");
  // Destroy the window
  window_destroy(s_main_window);
}

/**** Main application entry ****/
int main(void){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Main called.");
  init();
  app_event_loop();
  deinit();
}
