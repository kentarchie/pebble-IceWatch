// this code runs inside the Pebble phone app to start the config page
// and manage communication with the config page and the watch

var options = {};
var ProdURL= 'http://archie-perkins.com/pebble/IceWatch/index.html';
var TestURL= 'http://localhost:8080';

// field name definitions are in src/js/defs.js

//Pebble.addEventListener('ready', Init);  // on Pebble phone app Settings selected
Pebble.addEventListener('showConfiguration', SetupConfig); // When Pebble phone app Settings selected
Pebble.addEventListener('webviewclosed', ProcessConfig); // when Save button pressed

// when the configuration parameters are returned from the watch, do this,
// which includes opening the web page
// Commonly, this code would be in the callback in showConfiguration
Pebble.addEventListener('appmessage',
  	function(e) {
    		var configData = JSON.stringify(e.payload);
    		console.log('phoneside: appmessage: Received message: ' + configData);
         	var url = ProdURL+'?' + encodeURIComponent(configData);
         	//var url = TestURL+'?' + encodeURIComponent(configData);         
         	console.log('phoneSide: appmessage: url=:'+url+':');
         	Pebble.openURL(url); // open the config web page
         	console.log('phoneSide: appmessage: done');
  	}
);

// if watchapp/face not running, this is executed and watchapp/face is started
function Init()
{
  console.log('phoneSide: Init called!');
} // Init

//First we call the watch to get the current configuration parameters
function SetupConfig()
{
  console.log('phoneSide: SetupConfig start');
  var watchData = {};
  watchData["KEY_MESSAGE_TYPE"] = 'setup';
  Pebble.sendAppMessage(watchData 
     ,function() { /* passed function */
        console.log('phoneSide: SetupConfig: Send successful:');
     }
     ,function() { /* failed function */
      console.log('phoneSide: SetupConfig: Send app message failed!');
    }
  );
  console.log('phoneSide: SetupConfig: sendAppMessage completed:');

  /*
  var optionString = window.localStorage.getItem('IceWatch');
  if(!optionString) {
     console.log('phoneSide: optionString empty');
     optionString = '{}';
  }
  var IceWatchOptions = JSON.parse(optionString);

  var url= 'http://archie-perkins.com/pebble/IceWatch/index.html?'+encodeURIComponent(optionString);
  console.log('phoneSide: url=:'+url+':');

  Pebble.openURL(url); // open the config web page
  console.log('phoneSide: SetupConfig done');
  */
} // SetupConfig

function ProcessConfig(e)
{
  console.log('phoneSide: ProcessConfig: start');
  console.log('phoneSide: ProcessConfig: response = :'+ e.response + ':');
  if(e == undefined || e.response == undefined) {
  	console.log('phoneSide: ProcessConfig: response empty');
	return;
  }

  var configData = JSON.parse(decodeURIComponent(e.response));
  configData["KEY_MESSAGE_TYPE"] = 'config';
  //turn the color values into integers
  configData["KEY_ICE_BACKGROUND"] = parseInt(configData["KEY_ICE_BACKGROUND"],16);
  configData["KEY_ICE_TEXTCOLOR"]  = parseInt(configData["KEY_ICE_TEXTCOLOR"],16);
  configData["KEY_ME_BACKGROUND"]  = parseInt(configData["KEY_ME_BACKGROUND"],16);
  configData["KEY_ME_TEXTCOLOR"]   = parseInt(configData["KEY_ME_TEXTCOLOR"],16);
  console.log('phoneSide: ProcessConfig: configData = ' + JSON.stringify(configData));
  Pebble.sendAppMessage(configData, 
     function() { /* passed function */
        console.log('phoneSide: ProcessConfig: Send to watch successful:');
        }
  , function() { /* failed function */
      console.log('phoneSide: ProcessConfig: Send to watch message failed!');
    }
  );
  console.log('phoneSide: ProcessConfig: sendAppMessage completed:');
  return;
} // ProcessConfig
