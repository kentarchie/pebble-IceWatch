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
  console.log("phoneSide: webviewclosed: configuration closed");
  //console.log('phoneSide: webviewclosed: response = :'+ e.response + ':');
  //console.log('phoneSide: webviewclosed: charAt(0) = :'+ e.response.charAt(0) + ':');
  //console.log('phoneSide: webviewclosed: slice(-1)(0) = :'+ e.response.slice(-1) + ':');
  //console.log('phoneSide: webviewclosed: response.length = :'+ e.response.length + ':');

  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log("phoneSide: webviewclosed: configData = " + JSON.stringify(configData));
  var watchData = {};
  // defaults
  watchData['iceName']   = 'Emergency Contact Name';
  watchData['icePhone']  = '123-555-1234';
  watchData['myName']    = 'My Name';
  watchData['radioHour'] = 12;

  if (configData.iceName) watchData['iceName'] =  configData.iceName;
  if (configData.icePhone) watchData['icePhone'] =  configData.icePhone;
  if (configData.myName) watchData['myName'] =  parseInt(configData.myName);

  Pebble.sendAppMessage(watchData, 
     function() {
        console.log('phoneSide: webviewclosed: Send successful: ' + JSON.stringify(watchdata));
  	  }
  , function() {
      console.log('phoneSide: webviewclosed: Send app message failed!');
    }
  );
  window.localStorage.putItem('IceWatch',JSON.stringify(IceWatchOptions));
} // processConfig
