#include <pebble.h>
#include "Constants.h"
#include "Global.h"
#include "Common.h"

BitmapLayer* connectionSetup()
{
   BitmapLayer* bluetoothLayer = bitmap_layer_create(GRect(0, 0, 32, 32));

   bitmap_layer_set_bitmap(bluetoothLayer, bluetoothImageOff); // default off
   layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(bluetoothLayer));
	return(bluetoothLayer);
} // connectionSetup

TextLayer* ICELabelSetup()
{
   TextLayer* labelLayer = makeTextLayer(mainWindow,0, 0, 144, 40,
  		GColorWhite,GColorRed,
  		FONT_KEY_GOTHIC_28_BOLD,
  		GTextAlignmentCenter,
  		"ICE"
   );
  return(labelLayer);
} // ICELabelSetup

TextLayer* ICENameSetup()
{
  TextLayer* nameLayer = makeTextLayer(mainWindow,0, 30, 144, 30,
  		GColorWhite,GColorBlack,
  		FONT_KEY_ROBOTO_CONDENSED_21,
  		GTextAlignmentCenter,
  		"Kate Perkins"
  );
  return(nameLayer);
} // ICENameSetup

TextLayer* ICEPhoneSetup()
{
  TextLayer* phoneLayer = makeTextLayer(mainWindow,0, 50, 144, 30,
  		GColorWhite,GColorBlack,
  		FONT_KEY_ROBOTO_CONDENSED_21,
  		GTextAlignmentCenter,
  		"630-253-1359"
  );
  return(phoneLayer);
} // ICEPhoneSetup

TextLayer* meSetup()
{
  TextLayer* meLayer = makeTextLayer(mainWindow,0, 80, 140, 60,
  		GColorClear,GColorBlack,
  		FONT_KEY_GOTHIC_24_BOLD,
  		GTextAlignmentCenter,
  		"Kent Archie"
  );
  return(meLayer);
} // meSetup

TextLayer* timeSetup()
{
  TextLayer* timeLayer = makeTextLayer(mainWindow,0, 100, 144, 50,
  		GColorClear,GColorBlack,
  		FONT_KEY_BITHAM_42_BOLD,
  		GTextAlignmentCenter,
  		"00:00"
  );
  return(timeLayer);
} // timeSetup

TextLayer* dateSetup()
{
  TextLayer* dateLayer = makeTextLayer(mainWindow,0, 140, 144, 50,
  		GColorClear,GColorBlack,
  		FONT_KEY_GOTHIC_24_BOLD,
  		GTextAlignmentCenter,
  		"31 September 2015"
  );
  return(dateLayer);
} // dateSetup
