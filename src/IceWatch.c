#include <pebble.h>
#include <string.h>
// bluetooth code taken from classio-battery-connection example code
// battery status code taken from classio-battery-connection example code
  
#include "Constants.h"
#include "SetupDisplay.h"
#include "Actions.h"
#include "ConfigHandlers.h"
#include "Utilities.h"
#include "Layers.h"

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

AppTimer * btBuzzerTimer;
int HourFormat = 24;

static void inbox_received_handler(DictionaryIterator *iter, void *context) 
{
	APP_LOG(DebugLevel, "ICEWatch inbox_handler: received message");
	processContactName(iter, context);
	processContactPhone(iter, context);
	processMyName(iter, context);
	processRadioHour(iter, context);
	processBatteryStatus(iter, context);

	processICEBackground(iter, context); 
	processICETextColor(iter, context); 
	processMeBackground(iter, context);
	processMeTextColor(iter, context);
	APP_LOG(DebugLevel, "ICEWatch inbox_handler: DONE");
} // inbox_received_handler

static void loadSettings() 
{
	APP_LOG(DebugLevel, "ICEWatch loadSettings: START");
	loadSettingsText(KEY_CONTACT_NAME,GET_LAYER(ICE_NAME_LAYER),"ICE Name");
	loadSettingsText(KEY_CONTACT_PHONE,GET_LAYER(ICE_PHONE_LAYER),"ICE Phone");
	loadSettingsText(KEY_MY_NAME,GET_LAYER(ME_NAME_LAYER),"My Name");
	APP_LOG(DebugLevel, "ICEWatch loadSettings: TEXT DONE");

	loadSettingsBackground(KEY_ICE_BACKGROUND,GET_LAYER(ICE_NAME_LAYER),0xA8A8A8);
	loadSettingsBackground(KEY_ICE_BACKGROUND,GET_LAYER(ICE_PHONE_LAYER),0xA8A8A8);
	loadSettingsBackground(KEY_ME_BACKGROUND,GET_LAYER(ME_NAME_LAYER),0xA8A8A8);
	APP_LOG(DebugLevel, "ICEWatch loadSettings: Background DONE");

	loadSettingsTextColor(KEY_ME_TEXTCOLOR,GET_LAYER(ME_NAME_LAYER),GColorBlackARGB8);
	loadSettingsTextColor(KEY_ICE_TEXTCOLOR,GET_LAYER(ICE_NAME_LAYER),GColorBlackARGB8);
	loadSettingsTextColor(KEY_ICE_TEXTCOLOR,GET_LAYER(ICE_PHONE_LAYER),GColorBlackARGB8);
	APP_LOG(DebugLevel, "ICEWatch loadSettings: Text Color DONE");

	HourFormat = loadSettingsInt(KEY_HOUR_FORMAT,12);
	APP_LOG(DebugLevel, "ICEWatch loadSettings: Hour Format DONE");
	updateTime();
	APP_LOG(DebugLevel,"ICEWatch loadSettings: HourFormat=%d",HourFormat);

	bool batteryOn = loadSettingsBoolean(KEY_SHOW_BATTERY,false);
	APP_LOG(DebugLevel, "ICEWatch loadSettings: batteryOn=%s",batteryOn ? "true" : "false");
	printMemory("loadSettings done");
	APP_LOG(DebugLevel, "ICEWatch loadSettings: DONE");
} // loadSettings

static void mainWindowLoad(Window *window)
{
  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: START");
  btBuzzerTimer = NULL;
  bluetoothImageOn  = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn);
  bluetoothImageOff = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOff);
  
  loadLayers();
  processLayers();
  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: after processLayers");

  if(persist_exists(KEY_SHOW_BATTERY)){
  		bool value = persist_read_bool(KEY_SHOW_BATTERY);
		if (!value) {
			layer_set_hidden((Layer *) GET_LAYER(BATTERY_LAYER), true);
		}
			layer_set_hidden((Layer *) GET_LAYER(BATTERY_LAYER), false);
  }
  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: after battery setup");
  loadSettings();
  APP_LOG(DebugLevel, "ICEWatch mainWindowLoad: after loadSettings");
   
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
	APP_LOG(DebugLevel, "mainWindowUnLoad");
  bluetooth_connection_service_unsubscribe();
} // mainWindowUnload

static void tickHandler(struct tm *tickTime, TimeUnits units_changed)
{
  updateTime();
  handleBattery(battery_state_service_peek());
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
