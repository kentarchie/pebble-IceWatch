#include <pebble.h>
#include "generated/appinfo.h"
#include "Constants.h"
#include "ConfigData.h"
#include "Global.h"
#include "Layers.h"
extern Layer Layers[];

void saveConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: saveConfiguration: START");
    
    persist_write_int(    KEY_DATA_VERSION,   CONFIG_DATA.dataVersion);
    persist_write_string( KEY_CONTACT_NAME,   CONFIG_DATA.iceName);
    persist_write_string( KEY_CONTACT_PHONE,  CONFIG_DATA.icePhone);
    persist_write_string( KEY_MY_NAME,        CONFIG_DATA.myName);
    persist_write_int(    KEY_ICE_BACKGROUND, CONFIG_DATA.iceBackgroundColor);

    if(CONFIG_DATA.iceTextColor > 0xffffff) CONFIG_DATA.iceTextColor = 0;
    persist_write_int(    KEY_ICE_TEXTCOLOR,  CONFIG_DATA.iceTextColor);

    persist_write_int(    KEY_ME_BACKGROUND,  CONFIG_DATA.meBackgroundColor);

    if(CONFIG_DATA.meTextColor > 0xffffff) CONFIG_DATA.meTextColor = 0;
    persist_write_int(    KEY_ME_TEXTCOLOR,   CONFIG_DATA.meTextColor);

    persist_write_int(    KEY_HOUR_FORMAT,    CONFIG_DATA.hourFormat);
    persist_write_bool(   KEY_SHOW_BT,        CONFIG_DATA.showBT);
    persist_write_bool(   KEY_SHOW_BATTERY,   CONFIG_DATA.showBattery);

    APP_LOG(DebugLevel, "ICEWatch: saveConfiguration: DONE");
} // saveConfiguration

void loadConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: START");
    int strSize;
    CONFIG_DATA.dataVersion = persist_read_int(KEY_DATA_VERSION);

    strSize = persist_get_size(KEY_CONTACT_NAME)+1;
    CONFIG_DATA.iceName = malloc(strSize);
    persist_read_string(KEY_CONTACT_NAME, CONFIG_DATA.iceName, strSize);

    strSize = persist_get_size(KEY_CONTACT_PHONE)+1;
    CONFIG_DATA.icePhone = malloc(strSize);
    persist_read_string(KEY_CONTACT_PHONE, CONFIG_DATA.icePhone, strSize);

    strSize = persist_get_size(KEY_MY_NAME)+1;
    CONFIG_DATA.myName = malloc(strSize);
    persist_read_string(KEY_MY_NAME, CONFIG_DATA.myName, strSize);

    CONFIG_DATA.iceBackgroundColor = persist_read_int(KEY_ICE_BACKGROUND);
    CONFIG_DATA.iceTextColor = persist_read_int(KEY_ICE_TEXTCOLOR);
    CONFIG_DATA.meBackgroundColor = persist_read_int(KEY_ME_BACKGROUND);
    CONFIG_DATA.meTextColor = persist_read_int(KEY_ME_TEXTCOLOR);
    CONFIG_DATA.hourFormat = persist_read_int(KEY_HOUR_FORMAT);
    CONFIG_DATA.showBT = persist_read_bool(KEY_SHOW_BT);
    CONFIG_DATA.showBattery = persist_read_bool(KEY_SHOW_BATTERY);

    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: DONE");
} // loadConfiguration

void fetchConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: fetchConfiguration: START");
    initializeConfiguration();
	 if(persist_exists(KEY_CONTACT_NAME)) {
       loadConfiguration();
    }
    APP_LOG(DebugLevel, "ICEWatch: fetchConfiguration: calling logConfiguration");
    logConfiguration();
    APP_LOG(DebugLevel, "ICEWatch: fetchConfiguration: after logConfiguration");
} // fetchConfiguration

bool convertConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: ConvertConfiguration: START");
      int strSize=0;
		if((CONFIG_DATA.iceName = malloc(persist_get_size(KEY_CONTACT_NAME))) != NULL){
			persist_read_string(KEY_CONTACT_NAME, CONFIG_DATA.iceName, strSize);
         persist_delete(KEY_CONTACT_NAME);
      APP_LOG(DebugLevel, "ICEWatch: ConvertConfiguration: processed name :%s:",CONFIG_DATA.iceName);
      }
	   if(persist_exists(KEY_CONTACT_PHONE)) {
		   if((CONFIG_DATA.icePhone = malloc(persist_get_size(KEY_CONTACT_PHONE))) != NULL){
			   persist_read_string(KEY_CONTACT_PHONE, CONFIG_DATA.icePhone, strSize);
            persist_delete(KEY_CONTACT_PHONE);
         }
      }
	   if(persist_exists(KEY_MY_NAME)) {
		   if((CONFIG_DATA.myName = malloc(persist_get_size(KEY_MY_NAME))) != NULL){
			   persist_read_string(KEY_MY_NAME, CONFIG_DATA.myName, strSize);
            persist_delete(KEY_MY_NAME);
         }
      }
	   if(persist_exists(KEY_HOUR_FORMAT)) {
			   CONFIG_DATA.hourFormat = persist_read_int(KEY_HOUR_FORMAT);
            persist_delete(KEY_HOUR_FORMAT);
      }
	   if(persist_exists(KEY_ICE_BACKGROUND)) {
			   CONFIG_DATA.iceBackgroundColor = persist_read_int(KEY_ICE_BACKGROUND);
            persist_delete(KEY_ICE_BACKGROUND);
      }
	   if(persist_exists(KEY_ICE_TEXTCOLOR)) {
			   CONFIG_DATA.iceTextColor = persist_read_int(KEY_ICE_TEXTCOLOR);
            persist_delete(KEY_ICE_TEXTCOLOR);
      }
	   if(persist_exists(KEY_ME_BACKGROUND)) {
			   CONFIG_DATA.meBackgroundColor = persist_read_int(KEY_ME_BACKGROUND);
            persist_delete(KEY_ME_BACKGROUND);
      }
	   if(persist_exists(KEY_ME_TEXTCOLOR)) {
			   CONFIG_DATA.meTextColor = persist_read_int(KEY_ME_TEXTCOLOR);
            persist_delete(KEY_ME_TEXTCOLOR);
      }
	   if(persist_exists(KEY_SHOW_BT)) {
			   CONFIG_DATA.showBT = persist_read_bool(KEY_SHOW_BT);
            persist_delete(KEY_SHOW_BT);
      }
	   if(persist_exists(KEY_SHOW_BATTERY)) {
			   CONFIG_DATA.showBattery = persist_read_bool(KEY_SHOW_BATTERY);
            persist_delete(KEY_SHOW_BATTERY);
      }
    APP_LOG(DebugLevel, "ICEWatch: ConvertConfiguration: DONE");
      return(true);
} // convertConfiguration

void logConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: logConfiguration: start");
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.iceName=:%s:",CONFIG_DATA.iceName);
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.icePhone=:%s:",CONFIG_DATA.icePhone);
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.myName=:%s:",CONFIG_DATA.myName);
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.hourFormat=:%d:",CONFIG_DATA.hourFormat);

    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.iceBackgroundColor=:%#06x:%d:", CONFIG_DATA.iceBackgroundColor, CONFIG_DATA.iceBackgroundColor);
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.iceTextColor=:%#06x:%d:", CONFIG_DATA.iceTextColor, CONFIG_DATA.iceTextColor);
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.meBackgroundColor=:%#06x:%d:", CONFIG_DATA.meBackgroundColor, CONFIG_DATA.meBackgroundColor);
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.metextColor=:%#06x:%d:", CONFIG_DATA.meTextColor, CONFIG_DATA.meTextColor);

    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.showBT=:%s:",(CONFIG_DATA.showBT)?"true":"false");
    APP_LOG(DebugLevel, "ICEWatch: CONFIG_DATA.showBattery=:%s:",(CONFIG_DATA.showBattery)?"true":"false");
    APP_LOG(DebugLevel, "ICEWatch: logConfiguration: DONE");
} // logConfiguration

void initializeConfiguration()
{
   char * str = NULL;
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: start");
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: icename =%s",Layers[ICE_NAME_LAYER].defaultText);
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: icename length=%d",strlen(Layers[ICE_NAME_LAYER].defaultText));
   str = malloc(strlen(Layers[ICE_NAME_LAYER].defaultText)+1);
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: icename: after malloc");
   strcpy(str,Layers[ICE_NAME_LAYER].defaultText);
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: icename: after strcpy");
   CONFIG_DATA.iceName = str;

   str = malloc(strlen(Layers[ICE_PHONE_LAYER].defaultText)+1);
   strcpy(str,Layers[ICE_PHONE_LAYER].defaultText);
   CONFIG_DATA.icePhone = str;

   str = malloc(strlen(Layers[ME_NAME_LAYER].defaultText)+1);
   strcpy(str,Layers[ME_NAME_LAYER].defaultText);
   CONFIG_DATA.myName = str;

   CONFIG_DATA.iceBackgroundColor = (int)0xff;
   CONFIG_DATA.iceTextColor = (int)0x000;
   CONFIG_DATA.meBackgroundColor = (int)0xff;
   CONFIG_DATA.meTextColor = (int)0x000;
   
   CONFIG_DATA.hourFormat = 12;
   CONFIG_DATA.showBT = true;
   CONFIG_DATA.showBattery = true;
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: DONE");
} // initializeConfiguration
