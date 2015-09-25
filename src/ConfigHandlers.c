#include <pebble.h>
#include "Constants.h"
#include "Global.h"
#include "Actions.h"
extern int HourFormat;


void setBackgroundColor(int color,TextLayer * layer)
{
  GColor background_color = GColorFromHEX(color);
  text_layer_set_background_color(layer, background_color);
  APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: setBackgroundColor: value=:%#06x:",color);
} // setBackgroundColor

void setTextColor(int color,TextLayer * layer)
{
  GColor textColor = GColorFromHEX(color);
  text_layer_set_text_color(layer, textColor);
} // setTextColor

void processContactName(DictionaryIterator *iter, void *context) 
{
   char * contactName = "Name";
   Tuple *tuple = dict_find(iter, KEY_CONTACT_NAME);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: ProcessContactName: no contact name");
		return;
	}

   if(tuple->value->cstring) contactName = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: contactName =:%s:",contactName);

   // save new value if changed
   if((contactName != NULL) && (strcmp(contactName,"Name") != 0)) {
     persist_write_string(KEY_CONTACT_NAME, contactName); // Persist value
  	  text_layer_set_text(myNameLayer, contactName);  // set display
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: contactName missing");
   }
} // processContactName

void processContactPhone(DictionaryIterator *iter, void *context) 
{
   char * contactPhone = "Phone";
   Tuple *tuple = dict_find(iter, KEY_CONTACT_PHONE);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: no contact phone");
		return;
	}

   if(tuple->value->cstring) contactPhone = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: contactPhone =:%s:",contactPhone);

   // save new value if changed
   if((contactPhone != NULL) && (strcmp(contactPhone,"Phone") != 0)) {
     persist_write_string(KEY_CONTACT_PHONE, contactPhone); // Persist value
  	  text_layer_set_text(myNameLayer, contactPhone);  // set display
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: contactPhone missing");
   }
} // processContactName

void processMyName(DictionaryIterator *iter, void *context) 
{
   char * myName = "Name";
   Tuple *tuple = dict_find(iter, KEY_MY_NAME);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: no my name");
		return;
	}

   if(tuple->value->cstring) myName = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: myName =:%s:",myName);

   // save new value if changed
   if((myName != NULL) && (strcmp(myName,"Name") != 0)) {
     persist_write_string(KEY_MY_NAME, myName); // Persist value
  	  text_layer_set_text(myNameLayer, myName);  // set display
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: myName missing");
   }
} // processMyName

void processRadioHour(DictionaryIterator *iter, void *context) 
{
   int hourFormat = -1;
   Tuple *tuple = dict_find(iter, KEY_HOUR_FORMAT);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: no radio hour:");
		return;
	}

   if(tuple->value->int8) {
		hourFormat = tuple->value->int8;
	}
	else
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: hourFormat no tuple->value:");

   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: hourFormat =:%d:",hourFormat);

   // save new value if changed
   if(hourFormat != -1) {
     persist_write_int(KEY_HOUR_FORMAT, hourFormat); // Persist value
	  HourFormat=hourFormat;
	  updateTime();
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: hourFormat missing");
   }
} // processRadioHour

void processBatteryStatus(DictionaryIterator *iter, void *context) 
{
   char * batteryStatus = NULL;
   Tuple *tuple = dict_find(iter, KEY_SHOW_BATTERY);
	if(!tuple) return;

   if(tuple->value->cstring) batteryStatus = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: batteryStatus =:%s:",batteryStatus);

   // save new value if changed
   if(batteryStatus != NULL) {
     persist_write_bool(KEY_SHOW_BATTERY, strcmp(batteryStatus,"on") == 0); // Persist value
	  if(strcmp(batteryStatus,"on") == 0)
	  	 BatteryStatusOn();
	  else
	  	 BatteryStatusOff();
   } 
	else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: batteryStatus missing");
   }
} // processBatteryStatus

void processICEBackground(DictionaryIterator *iter, void *context) 
{
   int iceBackground = 0;
   Tuple *tuple = dict_find(iter, KEY_ICE_BACKGROUND);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: processICEBackground: no tuple iceBackground");
		return;
	}

   if(tuple->value->int32) iceBackground = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: processICEBackground: iceBackground =:%#06x:",iceBackground);

   // save new value if changed
   if(iceBackground != 0) {
     persist_write_int(KEY_ICE_BACKGROUND, iceBackground); // Persist value
     setBackgroundColor(iceBackground,ICENameLayer);
     setBackgroundColor(iceBackground,ICEPhoneLayer);
   } 
	else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: processICEBackground: iceBackground missing");
   }
} // processICEBackground

void processICETextColor(DictionaryIterator *iter, void *context) 
{
   int iceTextColor = 1;
   Tuple *tuple = dict_find(iter, KEY_ICE_TEXTCOLOR);
	if(!tuple) return;

   if(tuple->value->int32) iceTextColor = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: iceTextColor =:%#06x:",iceTextColor);

   // save new value if changed
   persist_write_int(KEY_ICE_TEXTCOLOR, iceTextColor); // Persist value
   setTextColor(iceTextColor,ICENameLayer);
   setTextColor(iceTextColor,ICEPhoneLayer);
} // processICETextColor

void processMeBackground(DictionaryIterator *iter, void *context) 
{
   int meBackground = 0;
   Tuple *tuple = dict_find(iter, KEY_ME_BACKGROUND);
	if(!tuple) return;

   if(tuple->value->int32) meBackground = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: meBackground =:%#06x:",meBackground);

   persist_write_int(KEY_ME_BACKGROUND, meBackground); // Persist value
   setBackgroundColor(meBackground,myNameLayer);
} // processMeBackground

void processMeTextColor(DictionaryIterator *iter, void *context) 
{
   int meTextColor = 1;
   Tuple *tuple = dict_find(iter, KEY_ME_TEXTCOLOR);
	if(!tuple) return;

   if(tuple->value->int32) meTextColor = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: meTextColor =:%#06x:",meTextColor);

   persist_write_int(KEY_ME_TEXTCOLOR, meTextColor); // Persist value
   setTextColor(meTextColor,myNameLayer);
} // processMeTextColor

void loadSettingsText(int key,TextLayer * layer,char * defaultValue) 
{
	char * stringBuffer;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: loading text settings");
	if(persist_exists(key)){
		int strSize = persist_get_size(key);
		if((stringBuffer = malloc(strSize)) != NULL){
			int actualSize = persist_read_string(key, stringBuffer, strSize);
  	  		text_layer_set_text(layer, stringBuffer);
      	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: loadText: key=:%d:, value =:%s:",key,stringBuffer);
		}
		else {
  	  		text_layer_set_text(layer, defaultValue);
		}
	}
} // loadSettingsText

void loadSettingsBackground(int key,TextLayer * layer,int defaultValue) 
{
	int backgroundColor = defaultValue;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: loading backgroundColor settings");
	if(persist_exists(key)){
      backgroundColor = persist_read_int(key);
      setBackgroundColor(backgroundColor,layer);
	}
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: text key=:%d: backgroundColor=%#06x",key,backgroundColor);
} // loadSettingsBackground

void loadSettingsTextColor(int key,TextLayer * layer,int defaultValue) 
{
	int textColor = defaultValue;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: loading textColor settings");
	if(persist_exists(key)){
      textColor = persist_read_int(key);
      setTextColor(textColor,layer);
	}
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: key=:%d: textColor=%#06x",key,textColor);
} // loadSettingsTextColor

int loadSettingsInt(int key,int defaultValue) 
{
	int value = defaultValue;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: loading int settings");
	if(persist_exists(key)){
      value = persist_read_int(key);
	}
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: key=:%d: int value=%d",key,value);
	return(value);
} // loadSettingsInt

bool loadSettingsBoolean(int key,bool defaultValue) 
{
	bool value = defaultValue;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: loading Boolean settings");
	if(persist_exists(key)){
  		value = persist_read_bool(key);
	}
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: key=:%d: bool value=%s",key,value ? "true" : "false");
	return(value);
} // loadSettingsBoolean

void logDictionary( DictionaryIterator *iter)
{
   APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: START");
	uint8_t buffer[2048];
	uint32_t currentSize =  dict_size(iter);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: size=:%d:",(int) currentSize);
	Tuple *tuple = dict_read_begin_from_buffer(iter, buffer, currentSize);
   APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: after tuple start");
	while (tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: in loop key=:%d:",(int)tuple->key);
  	switch (tuple->key) {
    	case KEY_CONTACT_NAME :
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: NAME value=:%s:",tuple->value->cstring);
      	break;
		case KEY_CONTACT_PHONE:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: PHONE value=:%s:",tuple->value->cstring);
      	break;
		case KEY_MY_NAME:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: MYNAME value=:%s:",tuple->value->cstring);
      	break;
		case KEY_HOUR_FORMAT:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: 12OR24 value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_SHOW_BATTERY:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: BATTERY value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ICE_BACKGROUND:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: ICEBACK value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ICE_TEXTCOLOR:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: ICETEXT value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ME_BACKGROUND:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: MEBACK value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_ME_TEXTCOLOR:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: METEXT value=:%d:",(int)tuple->value->int8);
      	break;
		default:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch: logDictionary: undefined key=%d",(int)tuple->key);
      	break;
  	} // esac
  	tuple = dict_read_next(iter);
	}
} // logDictionary
