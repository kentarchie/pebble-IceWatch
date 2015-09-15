var options = {};

Pebble.addEventListener("ready", init);
Pebble.addEventListener("showConfiguration", setupConfig);
Pebble.addEventListener("webviewclosed", processConfig);

function init()
{
  console.log("phoneSide: init called!");
} // init

function setupConfig()
{
  console.log("phoneSide: setupConfig start");
  //var optionsString = window.localStorage.getItem('IceWatch');
  //if(!optionString) optionString = "{}";
  //var IceWatchOptions = JSON.parse(optionString);
  //console.log("phoneSide: setupConfig: myName from storage=:"+IceWatchOptions.myName+":");
  //var url= 'http://archie-perkins.com/pebble/IceWatch/index.html?'+encodeURIComponent(optionString);
  var url= 'http://archie-perkins.com/pebble/IceWatch/index.html';
  Pebble.openURL(url);
} // setupConfig

function processConfig(e)
{
  console.log("phoneSide: procssConfig: start");
  console.log('phoneSide: processConfig: response = :'+ e.response + ':');

  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log("phoneSide: processConfig: configData = " + JSON.stringify(configData));
  var watchData = {};
  // defaults
  watchData['KEY_CONTACT_NAME'] = 'Emergency Contact Name';
  watchData['KEY_CONTACT_PHONE'] = '123-555-1234';
  watchData['KEY_MY_NAME'] = 'My Name';
  watchData['KEY_HOUR_FORMAT'] = 12;
  watchData['KEY_ICE_BACKGROUND'] = '0x000000';
  watchData['KEY_ICE_TEXTCOLOR'] = '0xffffff'
  watchData['KEY_ME_BACKGROUND'] = '0x000000'
  watchData['KEY_ME_TEXTCOLOR'] = '0xffffff'
  watchData['KEY_SHOW_BT'] = "on"
  watchData['KEY_SHOW_BATTERY'] = "on"
  watchData['KEY_BT_CONNECTION'] = true

  if ('iceName' in configData) 
  	 watchData['KEY_CONTACT_NAME']   =  configData.iceName;

  if ('icePhone' in configData) 
  	 watchData['KEY_CONTACT_PHONE']  =  configData.icePhone;

  if ('myName' in configData) 
  	 watchData['KEY_MY_NAME']    =  configData.myName;

  if ('hourFormat' in configData) 
  	 watchData['KEY_HOUR_FORMAT'] =  parseInt(configData.hourFormat);

  if ('iceBackground' in configData) {
		var iceBack = configData['iceBackground'];
  		console.log('phoneSide: processConfig: iceBack :' + iceBack);
  		//watchData['KEY_ICE_BACKGROUND'] = parseInt(iceBack.substring(2, 4), 16);
  		watchData['KEY_ICE_BACKGROUND'] = parseInt(iceBack, 16);
  }

  if ('iceTextColor' in configData) {
		var iceText = configData['iceTextColor'];
  		watchData['KEY_ICE_TEXTCOLOR'] = parseInt(iceText, 16);
  }

  if ('meBackground' in configData) {
		var meBack = configData['meBackground'];
  		watchData['KEY_ME_BACKGROUND'] = parseInt(meBack, 16);
  }

  if ('meTextColor' in configData) {
		var meText = configData['meTextColor'];
  		watchData['KEY_ME_TEXTCOLOR'] = parseInt(meText, 16);
  }

  if ('showBTStatus' in configData) {
		var btStatus = configData['showBTStatus'];
  		watchData['KEY_SHOW_BT'] = btStatus;
  }

  if ('showBatteryStatus' in configData) {
		var batteryStatus = configData['showBatteryStatus'];
  		watchData['KEY_SHOW_BATTERY'] = batteryStatus;
  }

  console.log('phoneSide: processConfig: watchData setup: ' + JSON.stringify(watchData));

  Pebble.sendAppMessage(watchData, 
     function() {
        console.log('phoneSide: processConfig: Send successful:');
  	  }
  , function() {
      console.log('phoneSide: processConfig: Send app message failed!');
    }
  );
  console.log('phoneSide: processConfig: sendAppMessage completed:');
  window.localStorage.putItem('IceWatch',JSON.stringify(IceWatchOptions));
  console.log('phoneSide: processConfig: after localstorage set: done:');
} // processConfig
