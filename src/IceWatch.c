#include <pebble.h>
// bluetooth code taken directly from classio-battery-connection example code
  
static Window *mainWindow;
static TextLayer *connectionLayer;
static TextLayer *ICELabelLayer;
static TextLayer *ICENameLayer;
static TextLayer *ICEPhoneLayer;
static TextLayer *myNameLayer;
static TextLayer *timeLayer;
static TextLayer *dateLayer;

static void connectionSetup()
{
  connectionLayer = text_layer_create(GRect(0, 0, 30, 30));
  text_layer_set_background_color(connectionLayer, GColorWhite);
  text_layer_set_text_color(connectionLayer, GColorGreen);
  text_layer_set_font(connectionLayer, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD ));
  text_layer_set_text(connectionLayer, "U");
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(connectionLayer));
} // connectionSetup

static void ICESetup()
{
	ICELabelLayer = text_layer_create(GRect(0, 0,  144, 40));
	ICENameLayer =  text_layer_create(GRect(0, 30, 144, 30));
	ICEPhoneLayer = text_layer_create(GRect(0, 50, 144, 30));

  	text_layer_set_background_color(ICELabelLayer, GColorWhite);
  	text_layer_set_background_color(ICENameLayer, GColorWhite);
  	text_layer_set_background_color(ICEPhoneLayer, GColorWhite);

  	text_layer_set_text_color(ICELabelLayer, GColorRed);
  	text_layer_set_text_color(ICENameLayer, GColorBlack);
  	text_layer_set_text_color(ICEPhoneLayer, GColorBlack);

  	text_layer_set_text(ICELabelLayer, "ICE");
  	text_layer_set_text(ICENameLayer,  "Kate Perkins");
  	text_layer_set_text(ICEPhoneLayer, "630-253-1359");

  	text_layer_set_font(ICELabelLayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  	text_layer_set_font(ICENameLayer,  fonts_get_system_font( FONT_KEY_ROBOTO_CONDENSED_21));
  	text_layer_set_font(ICEPhoneLayer, fonts_get_system_font( FONT_KEY_ROBOTO_CONDENSED_21));

  	text_layer_set_text_alignment(ICELabelLayer, GTextAlignmentCenter);
  	text_layer_set_text_alignment(ICENameLayer, GTextAlignmentCenter);
  	text_layer_set_text_alignment(ICEPhoneLayer, GTextAlignmentCenter);

  	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(ICELabelLayer));
  	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(ICENameLayer));
  	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(ICEPhoneLayer));
} // ICESetup

static void meSetup()
{
	myNameLayer = text_layer_create(GRect(0, 80, 140, 60));
  	text_layer_set_background_color(myNameLayer, GColorClear);
  	text_layer_set_text_color(myNameLayer, GColorBlack);
  	text_layer_set_text(myNameLayer, "Kent Archie");
  	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(myNameLayer));
  	text_layer_set_font(myNameLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  	text_layer_set_text_alignment(myNameLayer, GTextAlignmentCenter);
} // meSetup

static void timeSetup()
{
  // Create time TextLayer
  timeLayer = text_layer_create(GRect(0, 100, 144, 50));
  text_layer_set_background_color(timeLayer, GColorClear);
  text_layer_set_text_color(timeLayer, GColorBlack);
  text_layer_set_text(timeLayer, "00:00");

  // Improve the layout to be more like a watchface
  text_layer_set_font(timeLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(timeLayer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(timeLayer));
} // timeSetup

static void dateSetup()
{
  // Create date TextLayer
  dateLayer = text_layer_create(GRect(0, 140, 144, 50));
  text_layer_set_background_color(dateLayer, GColorClear);
  text_layer_set_text_color(dateLayer, GColorBlack);
  text_layer_set_text_alignment(dateLayer, GTextAlignmentCenter);

  text_layer_set_font(dateLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(dateLayer));
} // dateSetup

static void updateTime() 
{
  time_t temp = time(NULL); 
  struct tm *tickTime = localtime(&temp);

  // Create a long-lived buffer
  static char timeBuffer[] = "00:00";

  // Write the current hours and minutes into the buffer
    strftime(timeBuffer, sizeof("00:00"), "%H:%M", tickTime);

  // Display this time on the TextLayer
  text_layer_set_text(timeLayer, timeBuffer);
} // updateTime

static void updateDate() 
{
  time_t temp = time(NULL); 
  struct tm *tickTime = localtime(&temp);

  // Create a long-lived buffer
  static char dateBuffer[] = "31 September 2015";

  // Write the current hours and minutes into the buffer
    strftime(dateBuffer, sizeof(dateBuffer), "%e %B %Y", tickTime);

  // Display this time on the TextLayer
  text_layer_set_text(dateLayer, dateBuffer);
} // updateDate

static void handle_bluetooth(bool connected) {
  text_layer_set_text(connectionLayer, connected ? "C" : "U");
}

static void mainWindowLoad(Window *window)
{
   ICESetup();
   connectionSetup();
   meSetup();
   timeSetup();
   dateSetup();
  
  // Make sure the time is displayed from the start
  updateTime();
  updateDate();
  handle_bluetooth(bluetooth_connection_service_peek());
} // mainWindowLoad

static void mainWindowUnload(Window *window)
{
  // Destroy TextLayer
  text_layer_destroy(timeLayer);
  tick_timer_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
} // mainWindowUnload

static void tickHandler(struct tm *tickTime, TimeUnits units_changed)
{
  updateTime();
} // tickHandler
  
static void init()
{
  // Create main Window element and assign to pointer
  mainWindow = window_create();
  window_set_background_color(mainWindow, GColorTiffanyBlue);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load = mainWindowLoad,
    .unload = mainWindowUnload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(mainWindow, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tickHandler);
  bluetooth_connection_service_subscribe(handle_bluetooth);
} // init

static void deinit()
{
  // Destroy Window
  window_destroy(mainWindow);
} //deinit


int main(void)
{
  init();
  app_event_loop();
  deinit();
} // main
