#include <pebble.h>
// bluetooth code taken from classio-battery-connection example code
// battery status code taken from classio-battery-connection example code
  
#include "Constants.h"
#include "SetupDisplay.h"
#include "Actions.h"
#include "ConfigHandlers.h"

Window *mainWindow;
TextLayer *ICELabelLayer;
TextLayer *ICENameLayer;
TextLayer *ICEPhoneLayer;
TextLayer *myNameLayer;
TextLayer *timeLayer;
TextLayer *dateLayer;
TextLayer *batteryLayer;

GBitmap *bluetoothImageOn,*bluetoothImageOff;
BitmapLayer *bluetoothLayer;

int ConnectionLost;
AppTimer * btBuzzerTimer;
int hourFormat = 24;

static void inbox_received_handler(DictionaryIterator *iter, void *context) 
{
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch inbox_handler: received message");
	//logDictionary(iter);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch inbox_handler: after dict print");
	processContactName(iter, context);
	processContactPhone(iter, context);
	processMyName(iter, context);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch inbox_handler: processed Name");
	processRadioHour(iter, context);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch inbox_handler: processed radioHour");
	processBatteryStatus(iter, context);

   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch inbox_handler: starting colors");
	processICEBackground(iter, context); 
	processICETextColor(iter, context); 
	processMeBackground(iter, context);
	processMeTextColor(iter, context);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch inbox_handler: DONE");
} // inbox_received_handler

static void loadSettings() 
{
	loadSettingsText(KEY_CONTACT_NAME,ICENameLayer,"ICE Name");
	loadSettingsText(KEY_CONTACT_PHONE,ICEPhoneLayer,"ICE Phone");
	loadSettingsText(KEY_MY_NAME,myNameLayer,"My Name");

	loadSettingsBackground(KEY_ICE_BACKGROUND,ICENameLayer,0xA8A8A8);
	loadSettingsBackground(KEY_ICE_BACKGROUND,ICEPhoneLayer,0xA8A8A8);
	loadSettingsBackground(KEY_ME_BACKGROUND,myNameLayer,0xA8A8A8);

	loadSettingsTextColor(KEY_ME_TEXTCOLOR,myNameLayer,GColorBlackARGB8);
	loadSettingsTextColor(KEY_ICE_TEXTCOLOR,ICENameLayer,GColorBlackARGB8);
	loadSettingsTextColor(KEY_ICE_TEXTCOLOR,ICEPhoneLayer,GColorBlackARGB8);

	hourFormat = loadSettingsInt(KEY_12OR24,12);
	updateTime();
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loadSettings: hourFormat=%d",hourFormat);
	int batteryOn = loadSettingsBoolean(KEY_BATTERY_ON,FALSE);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loadSettings: batteryOn=%d",batteryOn);
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
  bluetoothLayer = connectionSetup();
  batteryLayer = batterySetup();

  loadSettings();
   
  // Make sure the time is displayed from the start
  updateTime();
  handleBattery(battery_state_service_peek());
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
