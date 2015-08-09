#include <pebble.h>
#include "Constants.h"
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
