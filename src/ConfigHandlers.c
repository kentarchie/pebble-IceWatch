#include <pebble.h>
#include "Constants.h"
#include "Global.h"
#include "Actions.h"
#include "Utilities.h"

extern int HourFormat;
char DebugStr[DEBUG_SIZE];

void setBackgroundColor(int color,TextLayer * layer)
{
  GColor background_color = GColorFromHEX(color);
  text_layer_set_background_color(layer, background_color);
  snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: setBackgroundColor: value=:%#06x:",color);
  printMemory( DebugStr, false);
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
	   printMemory( "ICEWatch: ProcessContactName: no contact name" , false);
		return;
	}

   if(tuple->value->cstring) contactName = tuple->value->cstring;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: contactName =:%s:",contactName);
	printMemory( DebugStr, false);

   // save new value if changed
   if((contactName != NULL) && (strcmp(contactName,"Name") != 0)) {
     persist_write_string(KEY_CONTACT_NAME, contactName); // Persist value
  	  text_layer_set_text(myNameLayer, contactName);  // set display
   } else {
	  printMemory( "ICEWatch: contactName missing" , false);
   }
} // processContactName

void processContactPhone(DictionaryIterator *iter, void *context) 
{
   char * contactPhone = "Phone";
   Tuple *tuple = dict_find(iter, KEY_CONTACT_PHONE);
	if(!tuple) {
		printMemory( "ICEWatch: no contact phone" , false);
		return;
	}

   if(tuple->value->cstring) contactPhone = tuple->value->cstring;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: contactPhone =:%s:",contactPhone);
	printMemory( DebugStr, false);

   // save new value if changed
   if((contactPhone != NULL) && (strcmp(contactPhone,"Phone") != 0)) {
     persist_write_string(KEY_CONTACT_PHONE, contactPhone); // Persist value
  	  text_layer_set_text(myNameLayer, contactPhone);  // set display
   } else {
	  printMemory( "ICEWatch: contactPhone missing" , false);
   }
} // processContactName

void processMyName(DictionaryIterator *iter, void *context) 
{
   char * myName = "Name";
   Tuple *tuple = dict_find(iter, KEY_MY_NAME);
	if(!tuple) {
	   printMemory( "ICEWatch: no my name" , false);
		return;
	}

   if(tuple->value->cstring) myName = tuple->value->cstring;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: myName =:%s:",myName);
	printMemory( DebugStr, false);

   // save new value if changed
   if((myName != NULL) && (strcmp(myName,"Name") != 0)) {
     persist_write_string(KEY_MY_NAME, myName); // Persist value
  	  text_layer_set_text(myNameLayer, myName);  // set display
   } else {
	  printMemory( "ICEWatch: myName missing" , false);
   }
} // processMyName

void processRadioHour(DictionaryIterator *iter, void *context) 
{
   int hourFormat = -1;
   Tuple *tuple = dict_find(iter, KEY_HOUR_FORMAT);
	if(!tuple) {
		printMemory( "ICEWatch: no radio hour:" , false);
		return;
	}

   if(tuple->value->int8) {
		hourFormat = tuple->value->int8;
	}
	else
		printMemory( "ICEWatch: hourFormat no tuple->value:" , false);

	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: hourFormat =:%d:",hourFormat);
	printMemory( DebugStr, false);

   // save new value if changed
   if(hourFormat != -1) {
     persist_write_int(KEY_HOUR_FORMAT, hourFormat); // Persist value
	  HourFormat=hourFormat;
	  updateTime();
   } else {
	  printMemory( "ICEWatch: hourFormat missing" , false);
   }
} // processRadioHour

void processBatteryStatus(DictionaryIterator *iter, void *context) 
{
   char * batteryStatus = NULL;
   Tuple *tuple = dict_find(iter, KEY_SHOW_BATTERY);
	if(!tuple) return;

   if(tuple->value->cstring) batteryStatus = tuple->value->cstring;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: batteryStatus =:%s:",batteryStatus);
	printMemory( DebugStr, false);

   // save new value if changed
   if(batteryStatus != NULL) {
     persist_write_bool(KEY_SHOW_BATTERY, strcmp(batteryStatus,"on") == 0); // Persist value
	  if(strcmp(batteryStatus,"on") == 0)
	  	 BatteryStatusOn();
	  else
	  	 BatteryStatusOff();
   } 
	else {
	  printMemory( "ICEWatch: batteryStatus missing" , false);
   }
} // processBatteryStatus

void processICEBackground(DictionaryIterator *iter, void *context) 
{
   int iceBackground = 0;
   Tuple *tuple = dict_find(iter, KEY_ICE_BACKGROUND);
	if(!tuple) {
	   printMemory( "ICEWatch: processICEBackground: no tuple iceBackground" , false);
		return;
	}

   if(tuple->value->int32) iceBackground = tuple->value->int32;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: processICEBackground: iceBackground =:%#06x:",iceBackground);
	printMemory( DebugStr, false);

   // save new value if changed
   if(iceBackground != 0) {
     persist_write_int(KEY_ICE_BACKGROUND, iceBackground); // Persist value
     setBackgroundColor(iceBackground,ICENameLayer);
     setBackgroundColor(iceBackground,ICEPhoneLayer);
   } 
	else {
	  printMemory( "ICEWatch: processICEBackground: iceBackground missing" , false);
   }
} // processICEBackground

void processICETextColor(DictionaryIterator *iter, void *context) 
{
   int iceTextColor = 1;
   Tuple *tuple = dict_find(iter, KEY_ICE_TEXTCOLOR);
	if(!tuple) return;

   if(tuple->value->int32) iceTextColor = tuple->value->int32;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: iceTextColor =:%#06x:",iceTextColor);
	printMemory( DebugStr, false);

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
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: meBackground =:%#06x:",meBackground);
	printMemory( DebugStr, false);

   persist_write_int(KEY_ME_BACKGROUND, meBackground); // Persist value
   setBackgroundColor(meBackground,myNameLayer);
} // processMeBackground

void processMeTextColor(DictionaryIterator *iter, void *context) 
{
   int meTextColor = 1;
   Tuple *tuple = dict_find(iter, KEY_ME_TEXTCOLOR);
	if(!tuple) return;

   if(tuple->value->int32) meTextColor = tuple->value->int32;
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: meTextColor =:%#06x:",meTextColor);
	printMemory( DebugStr, false);

   persist_write_int(KEY_ME_TEXTCOLOR, meTextColor); // Persist value
   setTextColor(meTextColor,myNameLayer);
} // processMeTextColor

void loadSettingsText(int key,TextLayer * layer,char * defaultValue) 
{
	char * stringBuffer;
	printMemory( "ICEWatch: loading text settings" , false);
	if(persist_exists(key)){
		int strSize = persist_get_size(key);
		if((stringBuffer = malloc(strSize)) != NULL){
			int actualSize = persist_read_string(key, stringBuffer, strSize);
  	  		text_layer_set_text(layer, stringBuffer);
			snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: loadText: key=:%d:, value =:%s:",key,stringBuffer);
			printMemory( DebugStr, false);
		}
		else {
  	  		text_layer_set_text(layer, defaultValue);
		}
	}
} // loadSettingsText

void loadSettingsBackground(int key,TextLayer * layer,int defaultValue) 
{
	int backgroundColor = defaultValue;
	printMemory( "ICEWatch: loading backgroundColor settings" , false);
	if(persist_exists(key)){
      backgroundColor = persist_read_int(key);
      setBackgroundColor(backgroundColor,layer);
	}
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: text key=:%d: backgroundColor=%#06x",key,backgroundColor);
	printMemory( DebugStr, false);
} // loadSettingsBackground

void loadSettingsTextColor(int key,TextLayer * layer,int defaultValue) 
{
	int textColor = defaultValue;
	printMemory( "ICEWatch: loading textColor settings" , false);
	if(persist_exists(key)){
      textColor = persist_read_int(key);
      setTextColor(textColor,layer);
	}
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: key=:%d: textColor=%#06x",key,textColor);
	printMemory( DebugStr, false);
} // loadSettingsTextColor

int loadSettingsInt(int key,int defaultValue) 
{
	int value = defaultValue;
	printMemory( "ICEWatch: loading int settings" , false);
	if(persist_exists(key)){
      value = persist_read_int(key);
	}
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: key=:%d: int value=%d",key,value);
	printMemory( DebugStr, false);
	return(value);
} // loadSettingsInt

bool loadSettingsBoolean(int key,bool defaultValue) 
{
	bool value = defaultValue;
	printMemory( "ICEWatch: loading Boolean settings" , false);
	if(persist_exists(key)){
  		value = persist_read_bool(key);
	}
	snprintf(DebugStr,DEBUG_SIZE, "ICEWatch: key=:%d: bool value=%s",key,value ? "true" : "false");
	printMemory( DebugStr, false);
	return(value);
} // loadSettingsBoolean
