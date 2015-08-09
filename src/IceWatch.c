#include <pebble.h>
// bluetooth code taken directly from classio-battery-connection example code
  
#include "Constants.h"
#include "Common.h"
#include "SetupDisplay.h"
#include "Actions.h"

Window *mainWindow;
TextLayer *ICELabelLayer;
TextLayer *ICENameLayer;
TextLayer *ICEPhoneLayer;
TextLayer *myNameLayer;
TextLayer *timeLayer;
TextLayer *dateLayer;
GBitmap *bluetoothImageOn,*bluetoothImageOff;
BitmapLayer *btBitMap;
int ConnectionLost;
AppTimer * btBuzzerTimer;

static void processMyName(DictionaryIterator *iter, void *context) 
{
   char * myName = "Name";
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing MyName");
   Tuple *tuple = dict_find(iter, KEY_MY_NAME);
	if(!tuple) return;

   if(tuple->value->cstring) myName = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch myName 1=:%s:",myName);

   // save new value if changed
   if((myName != NULL) && (strcmp(myName,"Name") != 0)) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch myName=:%s:",myName);
     // Persist value
     persist_write_string(KEY_MY_NAME, myName);
  	  text_layer_set_text(myNameLayer, myName);
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch myName missing");
   }
} // processMyName

static void inbox_received_handler(DictionaryIterator *iter, void *context) 
{
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch received message");
	processMyName(iter, context);
} // inbox_received_handler

static void loadSettings() 
{
	char * stringBuffer;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading settings");
	if(persist_exists(KEY_MY_NAME)){
      APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading myName");
		int strSize = persist_get_size(KEY_MY_NAME);
      APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch my name size=%d",strSize);
		if((stringBuffer = malloc(strSize)) != NULL){
			int actualSize = persist_read_string(KEY_MY_NAME, stringBuffer, strSize);
  	  		text_layer_set_text(myNameLayer, stringBuffer);
      	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch my name set actualSize=%d",actualSize);
      	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch my name =:%s:",stringBuffer);
			//free(stringBuffer);
		}
		else {
  	  		text_layer_set_text(myNameLayer, "No Name");
		}
	}
} // loadSettings

static void mainWindowLoad(Window *window)
{
  ConnectionLost=FALSE;
  btBuzzerTimer = NULL;
  bluetoothImageOn  = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn);
  bluetoothImageOff = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOff);

  ICELabelLayer = ICELabelSetup();
  ICENameLayer = ICENameSetup();
  ICEPhoneLayer = ICEPhoneSetup();
  myNameLayer = meSetup();
  timeLayer = timeSetup();
  dateLayer = dateSetup();
  connectionSetup();

  loadSettings();
   
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

  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

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
