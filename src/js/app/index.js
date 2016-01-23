// this code runs inside the Pebble phone app to start the config page
// and manage communication with the config page and the watch
var IW = require('./defs');
var Defs = IW.IceWatchDefs;

var options = {};

// field name definitions are in src/js/defs.js

//Pebble.addEventListener('ready', Init);  // on Pebble phone app Settings selected
Pebble.addEventListener('showConfiguration', SetupConfig); // When Pebble phone app Settings selected
Pebble.addEventListener('webviewclosed', ProcessConfig); // when Submit button pressed

// if watchapp/face not running, this is executed and watchapp/face is started
function Init()
{
  console.log('phoneSide: Init called!');
} // Init

// gather saved configuration data and open the configuration web page
function SetupConfig()
{
  console.log('phoneSide: SetupConfig start');
  var optionString = window.localStorage.getItem('IceWatch');
  if(!optionString) {
     console.log('phoneSide: optionString empty');
     optionString = '{}';
  }
  var IceWatchOptions = JSON.parse(optionString);
  console.log('phoneSide: SetupConfig: myName from storage=:'+IceWatchOptions[Defs.ConfigMyName]+':');

  var url= 'http://archie-perkins.com/pebble/IceWatch/index.html?'+encodeURIComponent(optionString);
  console.log('phoneSide: url=:'+url+':');

  Pebble.openURL(url); // open the config web page
  console.log('phoneSide: SetupConfig done');
} // SetupConfig

function ProcessConfig(e)
{
  console.log('phoneSide: ProcessConfig: start');
  console.log('phoneSide: ProcessConfig: response = :'+ e.response + ':');

  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('phoneSide: ProcessConfig: configData = ' + JSON.stringify(configData));
  var watchData = {};
  // default config settings
  watchData[Defs.WatchIceName] 	= 'Emergency Contact Name';
  watchData[Defs.WatchIcePhone] 	= '123-555-1234';
  watchData[Defs.WatchMyName] 	= 'My Name';
  watchData[Defs.WatchHourFormat] 	= 12;
  watchData[Defs.WatchIceBackground] = '0x000000';
  watchData[Defs.WatchIceTextColor] 	= '0xffffff';
  watchData[Defs.WatchMeBackground] 	= '0x000000';
  watchData[Defs.WatchMeTextColor] 	= '0xffffff';
  watchData[Defs.WatchShowBT] 	= 'on';
  watchData[Defs.WatchShowBattery] 	= 'on';
  watchData[Defs.WatchBTConnected] 	= true;

// replace defaults with saved settings
  if (Defs.ConfigIceName in configData) 
       watchData[Defs.WatchIceName]   =  configData[Defs.ConfigIceName];

  if (Defs.ConfigIcePhone in configData) 
       watchData[Defs.WatchIcePhone]  =  configData[Defs.ConfigIcePhone];

  if (Defs.ConfigMyName in configData) 
       watchData[Defs.WatchMyName]    =  configData[Defs.ConfigMyName];

  if (Defs.ConfigHourFormat in configData) 
       watchData[Defs.WatchHourFormat] =  parseInt(configData[Defs.ConfigHourFormat]);

  if (Defs.ConfigIceBackground in configData) {
        var iceBack = configData[Defs.ConfigIceBackground];
        console.log('phoneSide: ProcessConfig: iceBack :' + iceBack);
        watchData[Defs.WatchIceBackground] = parseInt(iceBack, 16);
  }

  if (Defs.ConfigIceTextColor in configData) {
        var iceText = configData[Defs.ConfigIceTextColor];
          watchData[Defs.WatchIceTextColor] = parseInt(iceText, 16);
  }

  if (Defs.ConfigMeBackground in configData) {
        var meBack = configData[Defs.ConfigMeBackground];
          watchData[Defs.WatchMeBackground] = parseInt(meBack, 16);
  }

  if (Defs.ConfigMeTextColor in configData) {
        var meText = configData[Defs.ConfigMeTextColor];
          watchData[Defs.WatchMeTextColor] = parseInt(meText, 16);
  }

  if (Defs.ConfigShowBT in configData) {
        var btStatus = configData[Defs.ConfigShowBT];
          watchData[Defs.WatchShowBT] = btStatus;
  }

  if (Defs.ConfigShowBattery in configData) {
        var batteryStatus = configData[Defs.ConfigShowBattery];
          watchData[Defs.WatchShowBattery] = batteryStatus;
  }

  console.log('phoneSide: ProcessConfig: watchData setup: ' + JSON.stringify(watchData));

  Pebble.sendAppMessage(watchData, 
     function() { /* passed function */
        console.log('phoneSide: ProcessConfig: Send successful:');
        }
  , function() { /* failed function */
      console.log('phoneSide: ProcessConfig: Send app message failed!');
    }
  );
  console.log('phoneSide: ProcessConfig: sendAppMessage completed:');
  window.localStorage.putItem('IceWatch',JSON.stringify(IceWatchOptions)); // safe config data
  console.log('phoneSide: ProcessConfig: after localstorage set: done:');
} // ProcessConfig
