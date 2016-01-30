#include <pebble.h>
#include "Constants.h"
#include "Global.h"
#include "Utilities.h"
#include "Layers.h"

extern int HourFormat;
extern Layer Layers[];

void updateTime() 
{
  time_t temp = time(NULL); 
  struct tm *tickTime = localtime(&temp);
  static char timeBuffer[] = "00:00";

  if (HourFormat == 24) {
    strftime(timeBuffer, sizeof("00:00"), "%H:%M", tickTime);
  } else {
    strftime(timeBuffer, sizeof("00:00"), "%l:%M", tickTime);
  }

  // Write the current hours and minutes into the buffer

  // Display this time on the TextLayer
  //APP_LOG(DebugLevel, "updateTime: setting text");
  text_layer_set_text(GET_LAYER(TIME_LAYER), timeBuffer);
  //APP_LOG(DebugLevel, "updateTime: text set");
} // updateTime

void updateDate() 
{
  time_t temp = time(NULL); 
  struct tm *tickTime = localtime(&temp);
  static char dateBuffer[] = "Wednesday 31 September 2015";

  strftime(dateBuffer, sizeof(dateBuffer), "%a %e %B %n %Y", tickTime);

  // Display this time on the TextLayer
  text_layer_set_text(GET_LAYER(DATE_LAYER), dateBuffer);
} // updateDate

void buzzer2() 
{
  app_timer_cancel( btBuzzerTimer);
  vibes_short_pulse();
} // buzzer2 

void bluetoothHandler(bool connected) 
{
  APP_LOG(DebugLevel, "bluetoothHandler: start connected :%s:",connected ? "true" : "false");
  bool prevConnected=false;
  if(persist_exists(BT_STATUS)){
    prevConnected = persist_read_bool(BT_STATUS);
	APP_LOG(DebugLevel, "bluetoothHandler: initial key");
  }
	APP_LOG(DebugLevel, "bluetoothHandler: prevConnected :%s:",prevConnected ? "true" : "false");

  if(connected && prevConnected) {
     bitmap_layer_set_bitmap(GET_LAYER(BLUETOOTH_LAYER), bluetoothImageOn);
	  APP_LOG(DebugLevel, "bluetoothHandler: both true turned on connection");
  }
  if(!connected && !prevConnected) {
     bitmap_layer_set_bitmap(GET_LAYER(BLUETOOTH_LAYER), bluetoothImageOff);
	  APP_LOG(DebugLevel, "bluetoothHandler: both false turned off connection");
  }

  if(connected && !prevConnected) {
     bitmap_layer_set_bitmap(GET_LAYER(BLUETOOTH_LAYER), bluetoothImageOn);
	  APP_LOG(DebugLevel, "bluetoothHandler: turned on connection");
     vibes_short_pulse();
  }

  if(!connected && prevConnected) {
  	  bitmap_layer_set_bitmap(GET_LAYER(BLUETOOTH_LAYER), bluetoothImageOff);
	  APP_LOG(DebugLevel, "bluetoothHandler: turned off connection");
     vibes_long_pulse();
     btBuzzerTimer = app_timer_register(BUZZER_INTERVAL, buzzer2,NULL);
  }
  persist_write_bool(BT_STATUS, connected);
  APP_LOG(DebugLevel, "bluetoothHandler: done saved :%s:",connected ? "true" : "false");
} // bluetoothHandler

void BatteryStatusOn() 
{
	APP_LOG(DebugLevel, "BatteryStatusOn");
	layer_set_hidden(GET_LAYER(BATTERY_LAYER), false);
} // BatteryStatusOn 

void BatteryStatusOff() 
{
	APP_LOG(DebugLevel, "BatteryStatusOff");
	layer_set_hidden(GET_LAYER(BATTERY_LAYER), true);
} // BatteryStatusOff 

void handleBattery(BatteryChargeState charge_state)
{
	static char battery_text[] = "100%";
	APP_LOG(DebugLevel, "handleBattery start");
	if(persist_exists(KEY_SHOW_BATTERY)){
  		bool value = persist_read_bool(KEY_SHOW_BATTERY);
  		APP_LOG(DebugLevel, "handleBattery: bool value :%d:",value);
		if (!value) {
			return;
		}
	}

  if (charge_state.is_charging) {
    APP_LOG(DebugLevel, "handleBattery is_charging");
    snprintf(battery_text, sizeof(battery_text), "chg");
  } else {
    APP_LOG(DebugLevel, "handleBattery not charging");
    snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);
    APP_LOG(DebugLevel, "handleBattery charge percent=%d",charge_state.charge_percent);
  }
  text_layer_set_text(GET_LAYER(BATTERY_LAYER), battery_text);
  APP_LOG(DebugLevel, "batteryCheck");
} //handleBattery
