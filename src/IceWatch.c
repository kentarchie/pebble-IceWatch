#include <pebble.h>
#include <string.h>
#include "generated/appinfo.h"
#include "Constants.h"
#include "SetupDisplay.h"
#include "Actions.h"
#include "ConfigData.h"
#include "Utilities.h"
#include "Layers.h"

// bluetooth and battery status code taken from classio-battery-connection example code

Window *mainWindow;
TextLayer *ICELabelLayer;
TextLayer *ICENameLayer;
TextLayer *ICEPhoneLayer;
TextLayer *myNameLayer;
TextLayer *timeLayer;
TextLayer *dateLayer;
TextLayer *batteryLayer;
bool DebugLevel=APP_LOG_LEVEL_DEBUG;
Layer Layers[LAYERCOUNT];

GBitmap *bluetoothImageOn,*bluetoothImageOff;
BitmapLayer *bluetoothLayer;

ConfigData CONFIG_DATA;

AppTimer * btBuzzerTimer;
int HourFormat = 24;

static char * setConfigString(DictionaryIterator * iter, int key, char * configField)
{
   Tuple *tuple = dict_find(iter, key);
   char * newStr = NULL;
	APP_LOG(DebugLevel, "ICEWatch setConfigString: configField=:%s:",configField);
	APP_LOG(DebugLevel, "ICEWatch setConfigString: key=%d",key);
   if(tuple && tuple->value->cstring) {
	   APP_LOG(DebugLevel, "ICEWatch setConfigString: string exists and =:%s:",tuple->value->cstring);
      if(configField != NULL)  {
         free(configField);
	      APP_LOG(DebugLevel, "ICEWatch setConfigString: freed space");
      }
      newStr = malloc(strlen(tuple->value->cstring)+1);
      strcpy(newStr,tuple->value->cstring);
	   APP_LOG(DebugLevel, "ICEWatch setConfigString: string copied =:%s:",newStr);
      return newStr;
   }
   else 
	   APP_LOG(DebugLevel, "ICEWatch setConfigString: key not found");
   return(NULL);
} // setConfigString

static void setConfigColor(DictionaryIterator * iter, int key, int * configField)
{
   Tuple *tuple = dict_find(iter, key);
   if(tuple && tuple->value->int32) {
      int colorValue = tuple->value->int32;
      if(colorValue > 0xffffff) colorValue = 0;
      *configField = colorValue;
   }
} // setConfigColor

static void setConfigHourFormat(DictionaryIterator * iter, int key, int * configField)
{
   Tuple *tuple = dict_find(iter, key);
   if(tuple && tuple->value->int32)
      *configField = tuple->value->int32;
} // setConfigHourFormat

static void setConfigSwitch(DictionaryIterator * iter, int key, bool * configField)
{
   Tuple *tuple = dict_find(iter, key);
   if(tuple && tuple->value->int32) {
      *configField = tuple->value->int32;
   }
} // setConfigSwitch

static void updateConfig(DictionaryIterator *iter, void *context) 
{
	APP_LOG(DebugLevel, "ICEWatch updateConfig: START");
   CONFIG_DATA.iceName = setConfigString(iter, KEY_CONTACT_NAME,CONFIG_DATA.iceName);
	APP_LOG(DebugLevel, "ICEWatch updateConfig: iceName=:%s:",CONFIG_DATA.iceName);
   CONFIG_DATA.icePhone = setConfigString(iter, KEY_CONTACT_PHONE,CONFIG_DATA.icePhone);
   CONFIG_DATA.myName = setConfigString(iter, KEY_MY_NAME, CONFIG_DATA.myName);
	APP_LOG(DebugLevel, "ICEWatch updateConfig: text info set");

   setConfigColor(iter, KEY_ICE_BACKGROUND, &CONFIG_DATA.iceBackgroundColor);
   setConfigColor(iter, KEY_ICE_TEXTCOLOR,  &CONFIG_DATA.iceTextColor);
   setConfigColor(iter, KEY_ME_BACKGROUND,  &CONFIG_DATA.meBackgroundColor);
   setConfigColor(iter, KEY_ME_TEXTCOLOR,   &CONFIG_DATA.meTextColor);
	APP_LOG(DebugLevel, "ICEWatch updateConfig: colors set");

   setConfigHourFormat(iter, KEY_HOUR_FORMAT, &CONFIG_DATA.hourFormat);
	APP_LOG(DebugLevel, "ICEWatch updateConfig: hourFormat set");

   setConfigSwitch(iter, KEY_SHOW_BT, &CONFIG_DATA.showBT);
   setConfigSwitch(iter, KEY_SHOW_BATTERY, &CONFIG_DATA.showBattery);
	APP_LOG(DebugLevel, "ICEWatch updateConfig: field set");

   logConfiguration();
   saveConfiguration();
   setDisplayData();
	APP_LOG(DebugLevel, "ICEWatch updateConfig: DONE");
} // updateConfig

static void sendConfig() 
{
	APP_LOG(DebugLevel, "ICEWatch sendConfig: making config message");
	DictionaryIterator *iter;
  	app_message_outbox_begin(&iter);
	
  	if (!iter) {
    	// Error creating outbound message
    	return;
  	}
  	dict_write_int(iter, KEY_DATA_VERSION, &CONFIG_DATA.dataVersion, sizeof(int), 1);
  	dict_write_cstring(iter, KEY_CONTACT_NAME,  CONFIG_DATA.iceName);
  	dict_write_cstring(iter, KEY_CONTACT_PHONE, CONFIG_DATA.icePhone);
  	dict_write_cstring(iter, KEY_MY_NAME,       CONFIG_DATA.myName);

  	dict_write_int(iter, KEY_ICE_BACKGROUND, &CONFIG_DATA.iceBackgroundColor, sizeof(int), true);
  	dict_write_int(iter, KEY_ICE_TEXTCOLOR,  &CONFIG_DATA.iceTextColor, sizeof(int), true);
  	dict_write_int(iter, KEY_ME_BACKGROUND,  &CONFIG_DATA.meBackgroundColor, sizeof(int), true);
  	dict_write_int(iter, KEY_ME_TEXTCOLOR,   &CONFIG_DATA.meTextColor, sizeof(int), true);

  	dict_write_uint8(iter, KEY_HOUR_FORMAT,  CONFIG_DATA.hourFormat);
  	dict_write_uint8(iter, KEY_SHOW_BATTERY, (CONFIG_DATA.showBattery) ? 1: 0);
  	dict_write_uint8(iter, KEY_SHOW_BT,      (CONFIG_DATA.showBT) ? 1: 0);
  	dict_write_end(iter);
	
  	app_message_outbox_send();
	APP_LOG(DebugLevel, "ICEWatch sendConfig: config message sent");
} // sendConfig

static void inbox_received_handler(DictionaryIterator *iter, void *context) 
{
	APP_LOG(DebugLevel, "ICEWatch inbox_handler: received message");
   Tuple *tuple = dict_find(iter, KEY_MESSAGE_TYPE);
   if(!tuple) {
      APP_LOG(DebugLevel, "ICEWatch: inbox_received_handler: no message type");
      return;
   }

   char * messageType = (tuple->value->cstring) ? tuple->value->cstring : "";
	APP_LOG(DebugLevel, "ICEWatch: messageType =:%s:",messageType);

   if((messageType != NULL) && (strcmp(messageType,"config") == 0))
		updateConfig(iter, context);
	else
		sendConfig();
	
	APP_LOG(DebugLevel, "ICEWatch inbox_handler: DONE");
} // inbox_received_handler

static void inbox_dropped_handler(AppMessageResult reason, void *context) 
{
	APP_LOG(DebugLevel, "ICEWatch inbox_handler: dropped message");
} // inbox_dropped_handler

static void mainWindowLoad(Window *window)
{
  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: START");
  btBuzzerTimer = NULL;
  bluetoothImageOn  = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn);
  bluetoothImageOff = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOff);
  
  loadLayers();    // make array of layer data structs
  fetchConfiguration();
  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: after fetchConfiguration");
  processLayers(); // make the layers indicated in the list
  setDisplayData();

  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: display setup");

  // Make sure the time is displayed from the start
  updateTime();
  handleBattery(battery_state_service_peek());
  updateDate();
  bluetoothHandler(bluetooth_connection_service_peek());
  APP_LOG(DebugLevel, "mainWindowLoad DONE");
} // mainWindowLoad

static void mainWindowUnload(Window *window)
{
   // Destroy TextLayer
   text_layer_destroy(GET_LAYER(ICE_LABEL_LAYER));
   text_layer_destroy(GET_LAYER(ICE_NAME_LAYER));
   text_layer_destroy(GET_LAYER(ICE_PHONE_LAYER));
   text_layer_destroy(GET_LAYER(ME_NAME_LAYER));
   text_layer_destroy(GET_LAYER(TIME_LAYER));
   text_layer_destroy(GET_LAYER(DATE_LAYER));
   text_layer_destroy(GET_LAYER(BATTERY_LAYER));
   bitmap_layer_destroy(GET_LAYER(BLUETOOTH_LAYER));

   tick_timer_service_unsubscribe();
   bluetooth_connection_service_unsubscribe();
   battery_state_service_unsubscribe();
   APP_LOG(DebugLevel, "mainWindow UnLoaded");
} // mainWindowUnload

static void tickHandler(struct tm *tickTime, TimeUnits units_changed)
{
  updateTime();
} // tickHandler
  
static void init()
{
  // Create main Window element and assign to pointer
  mainWindow = window_create();
  window_set_background_color(mainWindow, GColorCeleste);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load   = mainWindowLoad,
    .unload = mainWindowUnload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(mainWindow, true);
  
  // Register service handlers
  tick_timer_service_subscribe(MINUTE_UNIT, tickHandler);
  battery_state_service_subscribe(handleBattery);
  bluetooth_connection_service_subscribe(bluetoothHandler);

  app_message_register_inbox_received(inbox_received_handler);
  app_message_register_inbox_dropped(inbox_dropped_handler);
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
