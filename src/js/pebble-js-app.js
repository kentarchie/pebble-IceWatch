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
  //console.log('phoneSide: processConfig: charAt(0) = :'+ e.response.charAt(0) + ':');
  //console.log('phoneSide: processConfig: slice(-1)(0) = :'+ e.response.slice(-1) + ':');
  //console.log('phoneSide: processConfig: response.length = :'+ e.response.length + ':');

  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log("phoneSide: processConfig: configData = " + JSON.stringify(configData));
  var watchData = {};
  // defaults
  watchData['KEY_CONTACT_NAME']   = 'Emergency Contact Name';
  watchData['KEY_CONTACT_PHONE']  = '123-555-1234';
  watchData['KEY_MY_NAME']    = 'My Name';
  watchData['KEY_12OR24'] = 12;

  if (configData.iceName)   watchData['KEY_CONTACT_NAME']   =  configData.iceName;
  if (configData.icePhone)  watchData['KEY_CONTACT_PHONE']  =  configData.icePhone;
  if (configData.myName)    watchData['KEY_MY_NAME']    =  configData.myName;
  if (configData.radioHour) watchData['KEY_12OR24'] =  parseInt(configData.radioHour);
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
