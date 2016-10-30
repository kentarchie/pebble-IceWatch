#include <pebble.h>
#include "generated/appinfo.h"
#include "ConfigData.h"
#include "Actions.h"
#include "Constants.h"
#include "Global.h"
#include "Utilities.h"
#include "Layers.h"
extern Layer Layers[];

const int WHITE=0xffffff;
const int BLACK=0x000000;

void loadLayers()
{
	Layers[ICE_LABEL_LAYER] = (Layer) { 
	.name = "ICELayer",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 0,
	.width = PBL_DISPLAY_WIDTH,
	.height = 40,
	.currentText = "ICE",
	.defaultText = "ICE",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_GOTHIC_28_BOLD,
	.align = GTextAlignmentCenter
	};

	Layers[ICE_NAME_LAYER] = (Layer) { 
	.name = "ICEName",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 30,
	.width = PBL_DISPLAY_WIDTH,
	.height = 30,
	.currentText = "ICE",
	.defaultText = "Contact Name",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_ROBOTO_CONDENSED_21,
	.align = GTextAlignmentCenter
	};

	Layers[ICE_PHONE_LAYER] = (Layer) { 
	.name = "ICEPhone",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 50,
	.width = PBL_DISPLAY_WIDTH,
	.height = 32,
	.currentText = "",
	.defaultText = "000-555-1234",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_ROBOTO_CONDENSED_21,
	.align = GTextAlignmentCenter
	};

	Layers[ME_NAME_LAYER] = (Layer) { 
	.name = "MeName",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 72,
	.width = PBL_DISPLAY_WIDTH,
	.height = 25,
	.currentText = "",
	.defaultText = "My Name",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_ROBOTO_CONDENSED_21,
	.align = GTextAlignmentCenter
	};

	Layers[TIME_LAYER] = (Layer) { 
	.name = "timeLayer",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 85,
	.width = PBL_DISPLAY_WIDTH,
	.height = 45,
	.currentText = "",
	.defaultText = "00:00",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_BITHAM_42_BOLD,
	.align = GTextAlignmentCenter
	};

	Layers[DATE_LAYER] = (Layer) { 
	.name = "dateLayer",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 125,
	.width = PBL_DISPLAY_WIDTH,
	.height = 50,
	.currentText = "",
	.defaultText = "Tues. 31 September\n 2015",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_GOTHIC_18_BOLD,
	.align = GTextAlignmentCenter
	};

	Layers[BATTERY_LAYER] = (Layer) { 
	.name = "batteryLayer",
	.type = "text",
	.layer = NULL,
	.xpos = 100,
	.ypos = 0,
	.width = 50,
	.height = 25,
	.currentText = "",
	.defaultText = "100%",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = NULL,
	.defaultImage = NULL,
	.font = FONT_KEY_GOTHIC_24,
	.align = GTextAlignmentCenter
	};

	Layers[BLUETOOTH_LAYER] = (Layer) { 
	.name = "btLayer",
	.type = "bitmap",
	.layer = NULL,
	.xpos = 0,
	.ypos = 0,
	.width = 32,
	.height = 32,
	.currentText = "",
	.defaultText = "",
	.backgroundColor = WHITE,
	.textColor = BLACK,
	.currentImage = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn),
	.defaultImage = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn),
	.font = FONT_KEY_GOTHIC_24,
	.align = GTextAlignmentCenter
	};
} //loadLayers

void setBackgroundColor(int color,TextLayer * layer)
{
  GColor background_color = GColorFromHEX(color);
  text_layer_set_background_color(layer, background_color);
  APP_LOG(DebugLevel, "ICEWatch: setBackgroundColor: value=:%#06x:%d:",color,color);
} // setBackgroundColor

void setTextColor(int color,TextLayer * layer)
{
  GColor textColor = GColorFromHEX(color);
  text_layer_set_text_color(layer, textColor);
  APP_LOG(DebugLevel, "ICEWatch: setTextColor: value=:%#06x:%d:",color,color);
} // setTextColor

TextLayer * makeTextLayer( Window * win
			   ,int x, int y
                           ,int width, int height 
			   ,GColor backgroundColor
			   ,GColor textColor 
			   ,const char * font
                           ,GTextAlignment alignment
			   ,char * initialText)
{
  //APP_LOG(DebugLevel, "ICEWatch makeTextLayer: START");
  APP_LOG(DebugLevel, "ICEWatch makeTextLayer: backgroundColor=:%#06x: textColor=:%#06x:",
  	(int) backgroundColor.argb,
	(int) textColor.argb);
  TextLayer *newLayer = text_layer_create(GRect(x, y, width, height));
  text_layer_set_background_color(newLayer, backgroundColor);
  text_layer_set_font(newLayer, fonts_get_system_font(font));
  text_layer_set_text_color(newLayer, textColor);
  text_layer_set_text_alignment(newLayer, alignment);
  text_layer_set_text(newLayer, initialText);
  layer_add_child(window_get_root_layer(win), text_layer_get_layer(newLayer));
  return(newLayer);
} // makeTextLayer

void processLayers()
{
  GColor bColor;
  GColor tColor;
  APP_LOG(DebugLevel, "ICEWatch processLayers: START");
   for (int layer = 0; layer< LAYERCOUNT; ++layer) {
      APP_LOG(DebugLevel, "ICEWatch working on layer (%d) type=%s",layer,Layers[layer].type);
      if(strcmp(Layers[layer].type , "text") == 0) {
         APP_LOG(DebugLevel, "ICEWatch making textLayer (%d)",layer);
         APP_LOG(DebugLevel, "ICEWatch processLayers: layer (%d) backgroundColor=:%#06x: textColor=:%#06x:",layer, (int) Layers[layer].backgroundColor,(int) Layers[layer].textColor);
  	 bColor = GColorFromHEX( Layers[layer].backgroundColor);
  	 tColor = GColorFromHEX( Layers[layer].textColor);

         Layers[layer].layer =  makeTextLayer(mainWindow
                ,Layers[layer].xpos, Layers[layer].ypos, Layers[layer].width, Layers[layer].height,
  		bColor,tColor,
		Layers[layer].font, Layers[layer].align, Layers[layer].defaultText
         );
      }

      if(strcmp(Layers[layer].type , "bitmap") == 0) {
         APP_LOG(DebugLevel, "ICEWatch making bitmapLayer (%d)",layer);
         Layers[layer].layer =  bitmap_layer_create(GRect(Layers[layer].xpos, Layers[layer].ypos
						    ,Layers[layer].width, Layers[layer].height));
         layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(Layers[layer].layer));
      }
   } // for
  APP_LOG(DebugLevel, "ICEWatch processLayers: DONE");
} // processLayers

void setDisplayData()
{
   APP_LOG(DebugLevel, "ICEWatch setDisplay: START");
   setTextColor(CONFIG_DATA.iceTextColor,GET_LAYER(ICE_NAME_LAYER));
   setTextColor(CONFIG_DATA.iceTextColor,GET_LAYER(ICE_PHONE_LAYER));
   setTextColor(CONFIG_DATA.meTextColor,GET_LAYER(ME_NAME_LAYER));

   setBackgroundColor(CONFIG_DATA.iceBackgroundColor,GET_LAYER(ICE_NAME_LAYER));
   setBackgroundColor(CONFIG_DATA.iceBackgroundColor,GET_LAYER(ICE_PHONE_LAYER));
   setBackgroundColor(CONFIG_DATA.meBackgroundColor,GET_LAYER(ME_NAME_LAYER));

   text_layer_set_text(GET_LAYER(ME_NAME_LAYER), CONFIG_DATA.myName);
   text_layer_set_text(GET_LAYER(ICE_NAME_LAYER), CONFIG_DATA.iceName);
   text_layer_set_text(GET_LAYER(ICE_PHONE_LAYER), CONFIG_DATA.icePhone);

   APP_LOG(DebugLevel, "ICEWatch setDisplayData: showBattery=:%d:",CONFIG_DATA.showBattery);
   if(CONFIG_DATA.showBattery)
	   BatteryStatusOn();
   else
	   BatteryStatusOff();

   APP_LOG(DebugLevel, "ICEWatch setDisplayData: showBT=:%d:",CONFIG_DATA.showBT);
   if(CONFIG_DATA.showBT)
      bluetoothHandler(bluetooth_connection_service_peek());
   else
     bitmap_layer_set_bitmap(GET_LAYER(BLUETOOTH_LAYER), bluetoothImageOff);
   updateTime();
   APP_LOG(DebugLevel, "ICEWatch setDisplay: DONE");
} // setDisplayData
