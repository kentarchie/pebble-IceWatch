#include <pebble.h>
#include "Constants.h"
#include "Common.h"
#include "Global.h"

void updateTime() 
{
  time_t temp = time(NULL); 
  struct tm *tickTime = localtime(&temp);
  static char timeBuffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  strftime(timeBuffer, sizeof("00:00"), "%H:%M", tickTime);

  // Display this time on the TextLayer
  text_layer_set_text(timeLayer, timeBuffer);
} // updateTime

void updateDate() 
{
  time_t temp = time(NULL); 
  struct tm *tickTime = localtime(&temp);
  static char dateBuffer[] = "31 September 2015";

  strftime(dateBuffer, sizeof(dateBuffer), "%e %B %Y", tickTime);

  // Display this time on the TextLayer
  text_layer_set_text(dateLayer, dateBuffer);
} // updateDate

void buzzer2() 
{
  app_timer_cancel( btBuzzerTimer);
  vibes_short_pulse();
  //bitmap_layer_set_bitmap(btBitMap, bluetoothImageOff);
  bitmap_layer_set_bitmap(bluetoothLayer, bluetoothImageOff);
  ConnectionLost = TRUE;
} // buzzer2 

void bluetoothHandler(bool connected) 
{
  if(connected) {
     //APP_LOG(APP_LOG_LEVEL_DEBUG, "connected true");
     //bitmap_layer_set_bitmap(btBitMap, bluetoothImageOn);
     bitmap_layer_set_bitmap(bluetoothLayer, bluetoothImageOn);
     if(ConnectionLost == TRUE) {
         vibes_short_pulse();
         ConnectionLost = FALSE;
     }    
  }
  else {
     //APP_LOG(APP_LOG_LEVEL_DEBUG, "connected false");
    if(ConnectionLost == FALSE) {
       vibes_long_pulse();
       btBuzzerTimer = app_timer_register(BUZZER_INTERVAL, buzzer2,NULL);
    }
  }
} // bluetoothHandler