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

static TextLayer * makeTextLayer( Window * win, int x, int y,
int width, int height, GColor backgroundColor, GColor textColor, const char * font,
GTextAlignment alignment,char * initialText
)
{
  TextLayer *newLayer = text_layer_create(GRect(x, y, width, height));
  text_layer_set_background_color(newLayer, backgroundColor);
  text_layer_set_text_color(newLayer, textColor);
  text_layer_set_font(newLayer, fonts_get_system_font(font));
  layer_add_child(window_get_root_layer(win), text_layer_get_layer(newLayer));
  text_layer_set_text_alignment(newLayer, alignment);
  text_layer_set_text(newLayer, initialText);
  return(newLayer);
} // makeTextLayer

static void connectionSetup()
{
  connectionLayer = makeTextLayer(mainWindow,0, 0, 30, 30,
  	GColorWhite,GColorGreen,
  	FONT_KEY_DROID_SERIF_28_BOLD,
	GTextAlignmentLeft,
	"U"
  );
} // connectionSetup

static void ICESetup()
{
  ICELabelLayer = makeTextLayer(mainWindow,0, 0, 144, 40,
  	GColorWhite,GColorRed,
  	FONT_KEY_GOTHIC_28_BOLD,
  	GTextAlignmentCenter,
  	"ICE"
  );

  ICENameLayer = makeTextLayer(mainWindow,0, 30, 144, 30,
  	GColorWhite,GColorBlack,
  	FONT_KEY_ROBOTO_CONDENSED_21,
  	GTextAlignmentCenter,
  	"Kate Perkins"
  );

  ICEPhoneLayer = makeTextLayer(mainWindow,0, 50, 144, 30,
  	GColorWhite,GColorBlack,
  	FONT_KEY_ROBOTO_CONDENSED_21,
  	GTextAlignmentCenter,
  	"630-253-1359"
  );
} // ICESetup

static void meSetup()
{
  myNameLayer = makeTextLayer(mainWindow,0, 80, 140, 60,
  	GColorClear,GColorBlack,
  	FONT_KEY_GOTHIC_24_BOLD,
  	GTextAlignmentCenter,
  	"Kent Archie"
  );
} // meSetup

static void timeSetup()
{
  timeLayer = makeTextLayer(mainWindow,0, 100, 144, 50,
  	GColorClear,GColorBlack,
  	FONT_KEY_BITHAM_42_BOLD,
  	GTextAlignmentCenter,
  	"00:00"
  );
} // timeSetup

static void dateSetup()
{
  // Create date TextLayer
  dateLayer = makeTextLayer(mainWindow,0, 140, 144, 50,
  	GColorClear,GColorBlack,
  	FONT_KEY_GOTHIC_24_BOLD,
  	GTextAlignmentCenter,
  	"31 September 2015"
  );
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
