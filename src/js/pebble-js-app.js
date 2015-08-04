var initialized = false;
var options = {};

Pebble.addEventListener("ready", init);
Pebble.addEventListener("showConfiguration", setupConfig);
Pebble.addEventListener("webviewclosed", processConfig);

function init()
{
  console.log("phoneSide: init called!");
  initialized = true;
} // init

function setupConfig()
{
  console.log("phoneSide: setupConfig start");
  var optionsString = window.localStorage.getItem('IceWatch');
  if(!optionString) optionString = "{}";
  var IceWatchOptions = JSON.parse(optionString);
  console.log("phoneSide: setupConfig: myName from storage=:"+IceWatchOptions.myName+":");
  var url= 'http://archie-perkins.com/pebble/IceWatch/index.html?'+encodeURIComponent(optionString);
  //var url= 'http://archie-perkins.com/pebble/IceWatch/index.html';
  Pebble.openURL(url);
} // setupConfig

function processConfig(e)
{
  console.log("phoneSide: webviewclosed: configuration closed");
  // webview closed
  //Using primitive JSON validity and non-empty check
  //if (e.response.charAt(0) == "{" && e.response.slice(-1) == "}" && e.response.length > 5) {

  console.log('phoneSide: webviewclosed: response = :'+ e.response + ':');
  console.log('phoneSide: webviewclosed: charAt(0) = :'+ e.response.charAt(0) + ':');
  console.log('phoneSide: webviewclosed: slice(-1)(0) = :'+ e.response.slice(-1) + ':');
  console.log('phoneSide: webviewclosed: response.length = :'+ e.response.length + ':');

  var options = JSON.parse(decodeURIComponent(e.response));
  var optionsString = window.localStorage.getItem('IceWatch');
  var IceWatchOptions = JSON.parse(optionString);
  if(options['myName'] && (options['myName'] != '')) {
  	  IceWatchOptions['myName'] = options['myName'];
	  document.getElementById('myName').value = options['myName'];
  }

    console.log("phoneSide: webviewclosed: Options = " + JSON.stringify(options));
    // Send to watchapp
    var dict = {};
    dict['KEY_CONTACT_NAME']     = options['iceName'];
    dict['KEY_CONTACT_PHONE']    = options['icePhone'];
    dict['KEY_MY_NAME']          = options['myName'];
    //dict['KEY_12OR24']         = options['radioHour'];
	 //dict['KEY_BATTERY_ON']     = options[''];
	 //dict['KEY_ICE_BACKGROUND'] = options[''];
	 //dict['KEY_ICE_TEXTCOLOR']  = options[''];
	 //dict['KEY_ME_BACKGROUND']  = options[''];
	 //dict['KEY_ME_TEXTCOLOR']   = options[''];

    Pebble.sendAppMessage(dict, function() {
      console.log('phoneSide: webviewclosed: Send successful: ' + JSON.stringify(dict));
    }, function() {
      console.log('phoneSide: webviewclosed: Send app message failed!');
    });
    window.localStorage.putItem('IceWatch',JSON.stringify(IceWatchOptions));
  //} else {
  //  console.log("phoneSide: webviewclosed: Cancelled");
 // }
} // processConfig
