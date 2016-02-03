#include <pebble.h>
#include "generated/appinfo.h"
#include "Constants.h"
#include "ConfigData.h"
#include "Global.h"


bool fetchConfiguration()
{
	 if(persist_exists(KEY_CONTACT_NAME)) { // fetch old data, save in new format
      return convertConfiguration();
    }
    else {
      persist_read_data(OBJECT_KEY, &CONFIG_DATA, sizeof(ConfigData));
    }
    return(true);
} // fetchConfiguration

bool saveConfiguration()
{
    persist_write_data(OBJECT_KEY, &CONFIG_DATA, sizeof(ConfigData));
    return(true);
} // saveConfiguration

bool convertConfiguration()
{
      int strSize=0;
		if((CONFIG_DATA.iceName = malloc(persist_get_size(KEY_CONTACT_NAME))) != NULL){
			persist_read_string(KEY_CONTACT_NAME, CONFIG_DATA.iceName, strSize);
         persist_delete(KEY_CONTACT_NAME);
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
      return(true);
} // convertConfiguration
