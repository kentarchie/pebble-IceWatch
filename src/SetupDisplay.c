#include <pebble.h>
#include "Constants.h"
#include "Global.h"
#include "Utilities.h"
#include "Layers.h"
extern Layer Layers[];

void loadLayers()
{
	Layers[ICE_LABEL_LAYER] = (Layer) { 
	.name = "ICELayer",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 0,
	.width = MAX_WIDTH,
	.height = 40,
	.currentText = "ICE",
	.defaultText = "ICE",
	.currentImage = NULL,
	.defaultImage = NULL,
	.backgroundColor = GColorWhite,
	.textColor = GColorRed,
	.font = FONT_KEY_GOTHIC_28_BOLD,
	.align = GTextAlignmentCenter
	};

	Layers[ICE_NAME_LAYER] = (Layer) { 
	.name = "ICEName",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 30,
	.width = MAX_WIDTH,
	.height = 30,
	.currentText = "ICE",
	.defaultText = "Contact Name",
	.currentImage = NULL,
	.defaultImage = NULL,
	.backgroundColor = GColorWhite,
	.textColor = GColorBlack,
	.font = FONT_KEY_ROBOTO_CONDENSED_21,
	.align = GTextAlignmentCenter
	};

	Layers[ICE_PHONE_LAYER] = (Layer) { 
	.name = "ICEPhone",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 50,
	.width = MAX_WIDTH,
	.height = 32,
	.currentText = "",
	.defaultText = "000-555-1234",
	.currentImage = NULL,
	.defaultImage = NULL,
	.backgroundColor = GColorWhite,
	.textColor = GColorBlack,
	.font = FONT_KEY_ROBOTO_CONDENSED_21,
	.align = GTextAlignmentCenter
	};

	Layers[ME_NAME_LAYER] = (Layer) { 
	.name = "MeName",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 72,
	.width = MAX_WIDTH,
	.height = 25,
	.currentText = "",
	.defaultText = "My Name",
	.currentImage = NULL,
	.defaultImage = NULL,
	.backgroundColor = GColorWhite,
	.textColor = GColorBlack,
	.font = FONT_KEY_ROBOTO_CONDENSED_21,
	.align = GTextAlignmentCenter
	};

	Layers[TIME_LAYER] = (Layer) { 
	.name = "timeLayer",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 85,
	.width = MAX_WIDTH,
	.height = 45,
	.currentText = "",
	.defaultText = "00:00",
	.currentImage = NULL,
	.defaultImage = NULL,
	.backgroundColor = GColorClear,
	.textColor = GColorBlack,
	.font = FONT_KEY_BITHAM_42_BOLD,
	.align = GTextAlignmentCenter
	};

	Layers[DATE_LAYER] = (Layer) { 
	.name = "dateLayer",
	.type = "text",
	.layer = NULL,
	.xpos = 0,
	.ypos = 125,
	.width = MAX_WIDTH,
	.height = 50,
	.currentText = "",
	.defaultText = "Tues. 31 September\n 2015",
	.currentImage = NULL,
	.defaultImage = NULL,
	.backgroundColor = GColorClear,
	.textColor = GColorBlack,
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
	.currentImage = NULL,
	.defaultImage = NULL,
	.textColor = GColorBlue,
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
	.currentImage = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn),
	.defaultImage = gbitmap_create_with_resource(RESOURCE_ID_bluetoothOn),
	.backgroundColor = GColorWhite,
	.textColor = GColorBlue,
	.font = FONT_KEY_GOTHIC_24,
	.align = GTextAlignmentCenter
	};
} //loadLayers

TextLayer * makeTextLayer( Window * win
											 ,int x, int y
                                  ,int width, int height 
				  							 ,GColor backgroundColor
											 ,GColor textColor 
				  							 ,const char * font
                                  ,GTextAlignment alignment
				  							 ,char * initialText)
{
  APP_LOG(DebugLevel, "ICEWatch makeTextLayer: START");
  TextLayer *newLayer = text_layer_create(GRect(x, y, width, height));
  text_layer_set_background_color(newLayer, backgroundColor);
  text_layer_set_text_color(newLayer, textColor);
  text_layer_set_font(newLayer, fonts_get_system_font(font));
  layer_add_child(window_get_root_layer(win), text_layer_get_layer(newLayer));
  text_layer_set_text_alignment(newLayer, alignment);
  text_layer_set_text(newLayer, initialText);
  return(newLayer);
} // makeTextLayer

void processLayers()
{
  APP_LOG(DebugLevel, "ICEWatch processLayers: START");
   for (int layer = 0; layer< LAYERCOUNT; ++layer) {
      APP_LOG(DebugLevel, "ICEWatch working on layer (%d) type=%s",layer,Layers[layer].type);
      if(strcmp(Layers[layer].type , "text") == 0) {
         APP_LOG(DebugLevel, "ICEWatch making textLayer (%d)",layer);
         Layers[layer].layer =  makeTextLayer(mainWindow
                ,Layers[layer].xpos, Layers[layer].ypos, Layers[layer].width, Layers[layer].height,
  		          Layers[layer].backgroundColor,Layers[layer].textColor,
		          Layers[layer].font, Layers[layer].align, Layers[layer].defaultText
         );
      }

      if(strcmp(Layers[layer].type , "bitmap") == 0) {
         APP_LOG(DebugLevel, "ICEWatch making bitmapLayer (%d)",layer);
         Layers[layer].layer =  bitmap_layer_create(GRect(Layers[layer].xpos, Layers[layer].ypos, Layers[layer].width, Layers[layer].height));
         layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(Layers[layer].layer));
      }
   } // for
  APP_LOG(DebugLevel, "ICEWatch processLayers: DONE");
} // processLayers

