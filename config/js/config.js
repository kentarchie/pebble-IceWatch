var IW = require('./js/defs');   // data fields names
var Defs = IW.IceWatchDefs;
$().ready(init);

function clearLog()
{
  $('#logger').html('');
} // clearLog

function logger(str)
{
  var oldStr = $('#logger').html();
  $('#logger').html('config: ' + oldStr + '<hr />' + str);
} // logger

function init()
{
   logger('init start');
   logger('init: Defs=:'+typeof Defs+':');
   $('#b-cancel').click(cancelForm);
   $('#b-submit').click(sendForm);

   //Set form values to whatever is passed in.
   loadOptions();
} // init

function loadOptions() {
  var storeString = JSON.stringify(localStorage);
  logger('loadOptions storeString=:'+storeString+':');
  logger('loadOptions start');

  if (localStorage[Defs.ConfigMyName]) {
        $('#myName').val(localStorage[Defs.ConfigMyName]);
  }
  if (localStorage[Defs.ConfigIceName]) $('#iceName').val(localStorage[Defs.ConfigIceName]);
  if (localStorage[Defs.ConfigIcePhone]) $('#icePhone').val(localStorage[Defs.ConfigIcePhone]);
  if (localStorage[Defs.ConfigHourFormat]) {
     $('#hourFormat12').attr('checked',false);
     $('#hourFormat24').attr('checked',false);
     if (localStorage[Defs.ConfigHourFormat] == 12) $('#hourFormat12').attr('checked',true);
     if (localStorage[Defs.ConfigHourFormat] == 24) $('#hourFormat24').attr('checked',true);
  }

  if (localStorage[Defs.ConfigIceBackground]) 
          $('#iceBackgroundColor').val(localStorage[Defs.ConfigIceBackground]);
  if (localStorage[Defs.ConfigIceTextColor]) 
          $('#iceTextColor').val(localStorage[Defs.ConfigIceTextColor]);
  if (localStorage[Defs.ConfigMeBackground]) 
          $('#meBackgroundColor').val(localStorage[Defs.ConfigMeBackground]);
  if (localStorage[Defs.ConfigMeTextColor]) 
          $('#meTextColor').val(localStorage[Defs.ConfigMeTextColor]);

  if (localStorage[Defs.ConfigShowBattery]) 
          $('#showBatteryStatus').attr('checked', localStorage[Defs.ConfigShowBattery] == 'true');
  if (localStorage[Defs.ConfigShowBT]) 
          $('#showBTStatus').attr('checked', localStorage[Defs.ConfigShowBT] == 'true');
} // loadOptions

function saveOptions()
{
   var hourFormatVal = $('input[name="hourFormat"]:checked').val();
   var options = {
       "iceName"            : $('#iceName').val()
       ,"icePhone"          : $('#icePhone').val()
       ,"myName"            : $('#myName').val()
       ,"hourFormat"        : hourFormatVal
       ,"batteryON"         : true
       ,"iceBackground"     : $('#iceBackgroundColor').val()
       ,"iceTextColor"      : $('#iceTextColor').val()
       ,"meBackground"      : $('#meBackgroundColor').val()
       ,"meTextColor"       : $('#meTextColor').val()
       ,"showBatteryStatus" : ($('#showBatteryStatus').attr('checked')) ? "on" : "off"
       ,"showBTStatus"      : ($('#showBTStatus').attr('checked')) ? "on" : "off"
    };
   //logger("iceBackgroundColor = " +  $('#iceBackgroundColor').val());
   logger("saveOptions: showBTStatus = " +  ($('#showBTStatus').attr('checked')) ? "on" : "off";
   logger("saveOptions: showBatteryStatus.attr = " +  ($('#showBatteryStatus').attr('checked')) ? "on" : "off";

   //logger('saveOptions: options=:'+ JSON.stringify(options)+':');

   localStorage[Defs.ConfigMyName]        = options[Defs.ConfigMyName];
   localStorage[Defs.ConfigIceName]       = options[Defs.ConfigIceName];
   localStorage[Defs.ConfigIcePhone]      = options[Defs.ConfigIcePhone];
   localStorage[Defs.ConfigHourFormat]    = options[Defs.ConfigHourFormat];
   localStorage[Defs.ConfigIceBackground] = options[Defs.ConfigIceBackground];
   localStorage[Defs.ConfigIceTextColor]  = options[Defs.ConfigIceTextColor];
   localStorage[Defs.ConfigMeBackground]  = options[Defs.ConfigMeBackground];
   localStorage[Defs.ConfigMeTextColor]   = options[Defs.ConfigMeTextColor];
   localStorage[Defs.ConfigShowBT]        = options[Defs.ConfigShowBT];
   localStorage[Defs.ConfigShowBattery]   = options[Defs.ConfigShowBattery];

   return options;
} // saveOptions

function sendForm()
{
   //logger("configPage: Submit clicked");
   var return_to = getQueryParam('return_to', 'pebblejs://close#success');

   //logger("options = " +  JSON.stringify(saveOptions()));
   var location = return_to + encodeURIComponent(JSON.stringify(saveOptions()));
   //logger("configPage: Warping to: " + location);
   document.location = location;
} // sendForm

function cancelForm()
{
   logger("configPage: Cancel clicked");
   document.location = "pebblejs://close#cancel";
} // cancelForm

function getQueryParam(variable, defaultValue) {
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}
