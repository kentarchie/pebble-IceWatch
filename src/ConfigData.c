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

    //if(CONFIG_DATA.iceTextColor > 0xffffff) CONFIG_DATA.iceTextColor = 0x000000;
    CONFIG_DATA.iceTextColor = 0x000000;
    persist_write_int(    KEY_ICE_TEXTCOLOR,  CONFIG_DATA.iceTextColor);

    persist_write_int(    KEY_ME_BACKGROUND,  CONFIG_DATA.meBackgroundColor);

    //if(CONFIG_DATA.meTextColor > 0xffffff) CONFIG_DATA.meTextColor = 0x000000;
    CONFIG_DATA.meTextColor = 0x000000;
    persist_write_int(    KEY_ME_TEXTCOLOR,   CONFIG_DATA.meTextColor);

    persist_write_int(    KEY_HOUR_FORMAT,    CONFIG_DATA.hourFormat);
    APP_LOG(DebugLevel, "ICEWatch: saveConfiguration: hourFormat :%d:",CONFIG_DATA.hourFormat);
    persist_write_bool(   KEY_SHOW_BT,        CONFIG_DATA.showBT);
    persist_write_bool(   KEY_SHOW_BATTERY,   CONFIG_DATA.showBattery);

    APP_LOG(DebugLevel, "ICEWatch: saveConfiguration: DONE");
} // saveConfiguration

void loadConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: START");
    int strSize;
    CONFIG_DATA.dataVersion = persist_read_int(KEY_DATA_VERSION);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after dataVersion");

    strSize = persist_get_size(KEY_CONTACT_NAME)+1;
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: iceName: strSize =:%d:",strSize);
    if(strSize < 0) {
    	APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: FAILED iceName: strSize =:%d:",strSize);
	return;
    }
    CONFIG_DATA.iceName = malloc(strSize);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: iceName: after malloc");
    persist_read_string(KEY_CONTACT_NAME, CONFIG_DATA.iceName, strSize);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after iceName");

    strSize = persist_get_size(KEY_CONTACT_PHONE)+1;
    CONFIG_DATA.icePhone = malloc(strSize);
    persist_read_string(KEY_CONTACT_PHONE, CONFIG_DATA.icePhone, strSize);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after icePhone");

    strSize = persist_get_size(KEY_MY_NAME)+1;
    CONFIG_DATA.myName = malloc(strSize);
    persist_read_string(KEY_MY_NAME, CONFIG_DATA.myName, strSize);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after myName");

    CONFIG_DATA.iceBackgroundColor = persist_read_int(KEY_ICE_BACKGROUND);
    CONFIG_DATA.iceTextColor = persist_read_int(KEY_ICE_TEXTCOLOR);
    CONFIG_DATA.iceBackgroundColor = 0xffffff;
    CONFIG_DATA.iceTextColor = 0x000000;
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after iceColors");

    CONFIG_DATA.meBackgroundColor = persist_read_int(KEY_ME_BACKGROUND);
    CONFIG_DATA.meTextColor = persist_read_int(KEY_ME_TEXTCOLOR);
    CONFIG_DATA.meBackgroundColor = 0xffffff;
    CONFIG_DATA.meTextColor = 0x000000;
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after meColors");

    CONFIG_DATA.hourFormat = persist_read_int(KEY_HOUR_FORMAT);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: hourFormat :%d:",CONFIG_DATA.hourFormat);
    CONFIG_DATA.showBT = persist_read_bool(KEY_SHOW_BT);
    CONFIG_DATA.showBattery = persist_read_bool(KEY_SHOW_BATTERY);
    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: after hourFormat");

    APP_LOG(DebugLevel, "ICEWatch: loadConfiguration: DONE");
} // loadConfiguration

void fetchConfiguration()
{
    APP_LOG(DebugLevel, "ICEWatch: fetchConfiguration: START");
    initializeConfiguration();
    loadConfiguration();
    APP_LOG(DebugLevel, "ICEWatch: fetchConfiguration: calling logConfiguration");
    logConfiguration();
    APP_LOG(DebugLevel, "ICEWatch: fetchConfiguration: after logConfiguration");
} // fetchConfiguration

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
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: start");
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: icename =%s",Layers[ICE_NAME_LAYER].defaultText);
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: icename length=%d",strlen(Layers[ICE_NAME_LAYER].defaultText));
   CONFIG_DATA.iceName = malloc(strlen(Layers[ICE_NAME_LAYER].defaultText)+1);
   strcpy(CONFIG_DATA.iceName,Layers[ICE_NAME_LAYER].defaultText);

   CONFIG_DATA.icePhone = malloc(strlen(Layers[ICE_PHONE_LAYER].defaultText)+1);
   strcpy(CONFIG_DATA.icePhone,Layers[ICE_PHONE_LAYER].defaultText);

   CONFIG_DATA.myName = malloc(strlen(Layers[ME_NAME_LAYER].defaultText)+1);
   strcpy(CONFIG_DATA.myName,Layers[ME_NAME_LAYER].defaultText);

   CONFIG_DATA.iceBackgroundColor = 0xffffff;
   CONFIG_DATA.iceTextColor = 0x000000;
   CONFIG_DATA.meBackgroundColor = 0xffffff;
   CONFIG_DATA.meTextColor = 0x000000;
   
   CONFIG_DATA.hourFormat = (clock_is_24h_style()) ? 24 : 12;
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: default hourFormat :%d:",CONFIG_DATA.hourFormat);
   CONFIG_DATA.showBT = true;
   CONFIG_DATA.showBattery = true;
   APP_LOG(DebugLevel, "ICEWatch: initializeConfiguration: DONE");
} // initializeConfiguration
