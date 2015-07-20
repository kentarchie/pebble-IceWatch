#include <pebble.h>
// bluetooth code taken directly from classio-battery-connection example code
  
#define FALSE 1
#define TRUE 0
static Window *mainWindow;
static TextLayer *connectionLayer;
static TextLayer *ICELabelLayer;
static TextLayer *ICENameLayer;
static TextLayer *ICEPhoneLayer;
static TextLayer *myNameLayer;
static TextLayer *timeLayer;
static TextLayer *dateLayer;
static GBitmap *bluetoothImageOn,*bluetoothImageOff;
static BitmapLayer *btBitMap,*btOffBitMap;
static int ConnectionLost=FALSE;
static int BuzzerInterval=1500;
static AppTimer * btBuzzerTimer = NULL;


static TextLayer * makeTextLayer( Window * win, int x, int y,
                                  int width, int height, 
				  GColor backgroundColor, GColor textColor, 
				  const char * font,
                                  GTextAlignment alignment,
				  char * initialText
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
   bluetoothImageOn  = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn);
   bluetoothImageOff = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOff);

   btBitMap = bitmap_layer_create(GRect(0, 0, 32, 32));

   bitmap_layer_set_bitmap(btBitMap, bluetoothImageOff); // default off
   layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(btBitMap));
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
  static char dateBuffer[] = "31 September 2015";

  strftime(dateBuffer, sizeof(dateBuffer), "%e %B %Y", tickTime);

  // Display this time on the TextLayer
  text_layer_set_text(dateLayer, dateBuffer);
} // updateDate

static void buzzer2() 
{
  app_timer_cancel( btBuzzerTimer);
  vibes_short_pulse();
  bitmap_layer_set_bitmap(btBitMap, bluetoothImageOff);
  ConnectionLost = TRUE;
} // buzzer2 

static void bluetoothHandler(bool connected) 
{
  if(connected) {
     //APP_LOG(APP_LOG_LEVEL_DEBUG, "connected true");
     bitmap_layer_set_bitmap(btBitMap, bluetoothImageOn);
     if(ConnectionLost == TRUE) {
         vibes_short_pulse();
         ConnectionLost = FALSE;
     }    
  }
  else {
     //APP_LOG(APP_LOG_LEVEL_DEBUG, "connected false");
    if(ConnectionLost == FALSE) {
       vibes_long_pulse();
       btBuzzerTimer = app_timer_register(BuzzerInterval, buzzer2,NULL);
    }
  }
} // bluetoothHandler

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
  bluetoothHandler(bluetooth_connection_service_peek());
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
    .load   = mainWindowLoad,
    .unload = mainWindowUnload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(mainWindow, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tickHandler);
  bluetooth_connection_service_subscribe(bluetoothHandler);
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
