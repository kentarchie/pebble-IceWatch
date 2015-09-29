#include <pebble.h>
#include <stdio.h>
#include <stdarg.h>
#include "Constants.h"
#include "Global.h"
#include "Utilities.h"

void printMemory(char * header)
{
	APP_LOG(DebugLevel,"ICEWatch memory: %s: used=%d free=%d",header,heap_bytes_used(),heap_bytes_free());
} // printMemory

void logDictionary( DictionaryIterator *iter)
{
   APP_LOG(DebugLevel,"WatchSide: Dictionary: START");
	uint8_t buffer[2048];
	uint32_t currentSize =  dict_size(iter);
   APP_LOG(DebugLevel,"WatchSide: Dictionary: size=:%d:",(int) currentSize);
	Tuple *tuple = dict_read_begin_from_buffer(iter, buffer, currentSize);
   APP_LOG(DebugLevel,"WatchSide: Dictionary: after tuple start");
	while (tuple) {
   	APP_LOG(DebugLevel,"WatchSide: Dictionary: in loop key=:%d:",(int)tuple->key);
  	switch (tuple->key) {
    	case KEY_CONTACT_NAME :
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: NAME value=:%s:",tuple->value->cstring);
      	break;
		case KEY_CONTACT_PHONE:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: PHONE value=:%s:",tuple->value->cstring);
      	break;
		case KEY_MY_NAME:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: MYNAME value=:%s:",tuple->value->cstring);
      	break;
		case KEY_HOUR_FORMAT:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: 12OR24 value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_SHOW_BATTERY:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: BATTERY value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ICE_BACKGROUND:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: ICEBACK value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ICE_TEXTCOLOR:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: ICETEXT value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ME_BACKGROUND:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: MEBACK value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ME_TEXTCOLOR:
   		APP_LOG(DebugLevel,"WatchSide: Dictionary: METEXT value=:%d:",(int)tuple->value->int8);
      	break;
		default:
   		APP_LOG(DebugLevel,"ICEWatch: logDictionary: undefined key=%d",(int)tuple->key);
      	break;
  	} // esac
  	tuple = dict_read_next(iter);
	}
} // logDictionary
