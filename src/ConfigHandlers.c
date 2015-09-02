#include <pebble.h>
#include "Constants.h"
#include "Global.h"
#include "Actions.h"
extern int hourFormat;


void setBackgroundColor(int color,TextLayer * layer)
{
  GColor background_color = GColorFromHEX(color);
  text_layer_set_background_color(layer, background_color);
} // setBackgroundColor

void setTextColor(int color,TextLayer * layer)
{
  GColor textColor = GColorFromHEX(color);
  text_layer_set_text_color(layer, textColor);
} // setTextColor

void processContactName(DictionaryIterator *iter, void *context) 
{
   char * contactName = "Name";
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing contactName key=:%d:",KEY_CONTACT_NAME);
   Tuple *tuple = dict_find(iter, KEY_CONTACT_NAME);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch no contact name");
		return;
	}

   if(tuple->value->cstring) contactName = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch contactName 1=:%s:",contactName);

   // save new value if changed
   if((contactName != NULL) && (strcmp(contactName,"Name") != 0)) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch contactName=:%s:",contactName);
     persist_write_string(KEY_CONTACT_NAME, contactName); // Persist value
  	  text_layer_set_text(myNameLayer, contactName);  // set display
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch contactName missing");
   }
} // processContactName

void processContactPhone(DictionaryIterator *iter, void *context) 
{
   char * contactPhone = "Phone";
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing contactPhone");
   Tuple *tuple = dict_find(iter, KEY_CONTACT_PHONE);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch no contact phone");
		return;
	}

   if(tuple->value->cstring) contactPhone = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch contactPhone 1=:%s:",contactPhone);

   // save new value if changed
   if((contactPhone != NULL) && (strcmp(contactPhone,"Phone") != 0)) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch contactPhone=:%s:",contactPhone);
     persist_write_string(KEY_CONTACT_PHONE, contactPhone); // Persist value
  	  text_layer_set_text(myNameLayer, contactPhone);  // set display
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch contactPhone missing");
   }
} // processContactName

void processMyName(DictionaryIterator *iter, void *context) 
{
   char * myName = "Name";
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing MyName");
   Tuple *tuple = dict_find(iter, KEY_MY_NAME);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch no my name");
		return;
	}

   if(tuple->value->cstring) myName = tuple->value->cstring;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch myName 1=:%s:",myName);

   // save new value if changed
   if((myName != NULL) && (strcmp(myName,"Name") != 0)) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch myName=:%s:",myName);
     persist_write_string(KEY_MY_NAME, myName); // Persist value
  	  text_layer_set_text(myNameLayer, myName);  // set display
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch myName missing");
   }
} // processMyName

void processRadioHour(DictionaryIterator *iter, void *context) 
{
   int radioHour = -1;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing radioHour");
   Tuple *tuple = dict_find(iter, KEY_12OR24);
	if(!tuple) {
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch no radio hour:");
		return;
	}

   if(tuple->value->int8) {
		radioHour = tuple->value->int8;
	}
	else
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch radioHour no tuple->value:");

   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch radioHour 1=:%d:",radioHour);

   // save new value if changed
   if(radioHour != -1) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch radioHour=:%d:",radioHour);
     persist_write_int(KEY_12OR24, radioHour); // Persist value
	  hourFormat=radioHour;
	  updateTime();
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch radioHour missing");
   }
} // processRadioHour

void processBatteryStatus(DictionaryIterator *iter, void *context) 
{
   int batteryStatus = -1;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing batteryStatus");
   Tuple *tuple = dict_find(iter, KEY_BATTERY_ON);
	if(!tuple) return;

   if(tuple->value->int8) batteryStatus = tuple->value->int8;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch batteryStatus 1=:%d:",batteryStatus);

   // save new value if changed
   if(batteryStatus != -1) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch batteryStatus=:%d:",batteryStatus);
     persist_write_int(KEY_BATTERY_ON, batteryStatus); // Persist value
	  if(batteryStatus)
	  	 BatteryStatusOn();
	  else
	  	 BatteryStatusOff();
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch batteryStatus missing");
   }
} // processBatteryStatus

void processICEBackground(DictionaryIterator *iter, void *context) 
{
   int iceBackground = 0;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing iceBackground");
   Tuple *tuple = dict_find(iter, KEY_ICE_BACKGROUND);
	if(!tuple) return;

   if(tuple->value->int32) iceBackground = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch iceBackground 1=:%d:",iceBackground);

   // save new value if changed
   if(iceBackground != 0) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch iceBackground=:%d:",iceBackground);
     persist_write_int(KEY_ICE_BACKGROUND, iceBackground); // Persist value
     //setBackgroundColor(iceBackground,ICELabelLayer);
     setBackgroundColor(iceBackground,ICENameLayer);
     setBackgroundColor(iceBackground,ICEPhoneLayer);
   } 
	else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch iceBackground missing");
   }
} // processICEBackground

void processICETextColor(DictionaryIterator *iter, void *context) 
{
   int iceTextColor = 1;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing iceTextColor");
   Tuple *tuple = dict_find(iter, KEY_ICE_TEXTCOLOR);
	if(!tuple) return;

   if(tuple->value->int32) iceTextColor = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch iceTextColor 1=:%d:",iceTextColor);

   // save new value if changed
   if(iceTextColor != 0) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch iceTextColor=:%d:",iceTextColor);
     persist_write_int(KEY_ICE_TEXTCOLOR, iceTextColor); // Persist value
     //setTextColor(iceTextColor,ICELabelLayer);
     setTextColor(iceTextColor,ICENameLayer);
     setTextColor(iceTextColor,ICEPhoneLayer);
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch iceTextColor missing");
   }
} // processICETextColor

void processMeBackground(DictionaryIterator *iter, void *context) 
{
   int meBackground = 0;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing meBackground");
   Tuple *tuple = dict_find(iter, KEY_ME_BACKGROUND);
	if(!tuple) return;

   if(tuple->value->int32) meBackground = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch meBackground 1=:%d:",meBackground);

   // save new value if changed
   if(meBackground != 0) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch meBackground=:%d:",meBackground);
     persist_write_int(KEY_ME_BACKGROUND, meBackground); // Persist value
     setBackgroundColor(meBackground,myNameLayer);
	}
   else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch meBackground missing");
   }
} // processMeBackground

void processMeTextColor(DictionaryIterator *iter, void *context) 
{
   int meTextColor = 1;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch processing meTextColor");
   Tuple *tuple = dict_find(iter, KEY_ME_TEXTCOLOR);
	if(!tuple) return;

   if(tuple->value->int32) meTextColor = tuple->value->int32;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch meTextColor 1=:%d:",meTextColor);

   // save new value if changed
   if(meTextColor != 0) {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch meTextColor=:%d:",meTextColor);
     persist_write_int(KEY_ME_TEXTCOLOR, meTextColor); // Persist value
     setTextColor(meTextColor,myNameLayer);
   } else {
     APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch meTextColor missing");
   }
} // processMeTextColor

void loadSettingsText(int key,TextLayer * layer,char * defaultValue) 
{
	char * stringBuffer;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading text settings");
	if(persist_exists(key)){
      APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading key");
		int strSize = persist_get_size(key);
      APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch text size=%d",strSize);
		if((stringBuffer = malloc(strSize)) != NULL){
			int actualSize = persist_read_string(key, stringBuffer, strSize);
  	  		text_layer_set_text(layer, stringBuffer);
      	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch my name set actualSize=%d",actualSize);
      	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch my name =:%s:",stringBuffer);
			//free(stringBuffer);
		}
		else {
  	  		text_layer_set_text(layer, defaultValue);
		}
	}
} // loadSettingsText

void loadSettingsBackground(int key,TextLayer * layer,int defaultValue) 
{
	int backgroundColor;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading backgroundColor settings");
	if(persist_exists(key)){
      backgroundColor = persist_read_int(key);
      APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch text backgroundColor=%d",backgroundColor);
      setBackgroundColor(backgroundColor,layer);
	}
	else {
     	setBackgroundColor(defaultValue,layer);
	}
} // loadSettingsBackground

void loadSettingsTextColor(int key,TextLayer * layer,int defaultValue) 
{
	int textColor;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading textColor settings");
	if(persist_exists(key)){
      textColor = persist_read_int(key);
      APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch text textColor=%d",textColor);
      setTextColor(textColor,layer);
	}
	else {
      setTextColor(defaultValue,layer);
	}
} // loadSettingsTextColor

int loadSettingsInt(int key,int defaultValue) 
{
	int value = defaultValue;
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading int settings");
	if(persist_exists(key)){
   	APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch persists key=%d",key);
      value = persist_read_int(key);
	}
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch text value=%d",value);
	return(value);
} // loadSettingsInt

int loadSettingsBoolean(int key,int defaultValue) 
{
   APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch loading Boolean settings");
	if(persist_exists(key)){
  		return(persist_read_bool(key));
	}
	else
	   return(defaultValue);
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
		case KEY_12OR24:
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"WatchSide: Dictionary: 12OR24 value=:%d:",(int)tuple->value->int8);
      	break;
		case KEY_BATTERY_ON:
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
   		APP_LOG(APP_LOG_LEVEL_DEBUG,"ICEWatch logDictionary: undefined key=%d",(int)tuple->key);
      	break;
  	} // esac
  	tuple = dict_read_next(iter);
	}
} // logDictionary
