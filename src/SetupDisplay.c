#include <pebble.h>
#include "Constants.h"
#include "Global.h"

TextLayer * makeTextLayer( Window * win
											 ,int x, int y
                                  ,int width, int height 
				  							 ,GColor backgroundColor
											 ,GColor textColor 
				  							 ,const char * font
                                  ,GTextAlignment alignment
				  							 ,char * initialText)
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

BitmapLayer* connectionSetup()
{
   BitmapLayer* btLayer = bitmap_layer_create(GRect(0, 0, 32, 32));

   bitmap_layer_set_bitmap(btLayer, bluetoothImageOff); // default off
   layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(btLayer));
	return(btLayer);
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
