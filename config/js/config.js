$().ready(init);

function clearLog()
{
  $('#logger').html('');
} // clearLog

function logger(str)
{
  var oldStr = $('#logger').html();
  $('#logger').html(oldStr + '<hr />' + str);
} // logger

(function(){
   clearLog();
   $('#b-cancel').click(cancelForm);
   $('#b-submit').click(sendForm);
   loadOptions();
})();

function init()
{
   logger('init start');
   $('#b-cancel').click(cancelForm);
   $('#b-submit').click(sendForm);

   //Set form values to whatever is passed in.
   loadOptions();
} // init

function loadOptions() {
  var storeString = JSON.stringify(localStorage);
  //logger( JSON.stringify(localStorage));
  logger('loadOptions start');

  if (localStorage[IceWatchDefs.ConfigMyName]) {
        $('#myName').val(localStorage[IceWatchDefs.ConfigMyName]);
  }
  if (localStorage[IceWatchDefs.ConfigIceName]) $('#iceName').val(localStorage[IceWatchDefs.ConfigIceName]);
  if (localStorage[IceWatchDefs.ConfigIcePhone]) $('#icePhone').val(localStorage[IceWatchDefs.ConfigIcePhone]);
  if (localStorage[IceWatchDefs.ConfigHourFormat]) {
     $('#hourFormat12').prop('checked',false);
     $('#hourFormat24').prop('checked',false);
       if (localStorage[IceWatchDefs.ConfigHourFormat] == 12) $('#hourFormat12').prop('checked',true);
       if (localStorage[IceWatchDefs.ConfigHourFormat] == 24) $('#hourFormat24').prop('checked',true);
  }

  if (localStorage[IceWatchDefs.ConfigIceBackground]) 
          $('#iceBackgroundColor').val(localStorage[IceWatchDefs.ConfigIceBackground]);
  if (localStorage[IceWatchDefs.ConfigIceTextColor]) 
          $('#iceTextColor').val(localStorage[IceWatchDefs.ConfigIceTextColor]);
  if (localStorage[IceWatchDefs.ConfigMeBackground]) 
          $('#meBackgroundColor').val(localStorage[IceWatchDefs.ConfigMeBackground]);
  if (localStorage[IceWatchDefs.ConfigMeTextColor]) 
          $('#meTextColor').val(localStorage[IceWatchDefs.ConfigMeTextColor]);

  if (localStorage[IceWatchDefs.ConfigShowBattery]) 
          $('#showBatteryStatus').attr('checked', localStorage[IceWatchDefs.ConfigShowBattery] == 'true');
  if (localStorage[IceWatchDefs.ConfigShowBT]) 
          $('#showBTStatus').attr('checked', localStorage[IceWatchDefs.ConfigShowBT] == 'true');
} // loadOptions

function saveOptions()
{
   var hourFormatVal = $('input[name="hourFormat"]:checked').val();
   var options = {
       "iceName"             : $('#iceName').val()
       ,"icePhone"           : $('#icePhone').val()
       ,"myName"             : $('#myName').val()
        ,"hourFormat"        : hourFormatVal
        ,"batteryON"         : true
        ,"iceBackground"     : $('#iceBackgroundColor').val()
        ,"iceTextColor"      : $('#iceTextColor').val()
        ,"meBackground"      : $('#meBackgroundColor').val()
        ,"meTextColor"       : $('#meTextColor').val()
        ,"showBatteryStatus" : $('#showBatteryStatus').attr('checked')
        ,"showBTStatus"      : $('#showBTStatus').attr('checked')
    };
   //logger("iceBackgroundColor = " +  $('#iceBackgroundColor').val());
   logger("showBTStatus = " +  $('#showBTStatus').attr('checked'));
   //logger("showBatteryStatus.val = " +  $('#showBatteryStatus').val());
   //logger("showBatteryStatus.checked = " +  $('#showBatteryStatus').checked);
   logger("showBatteryStatus.attr = " +  $('#showBatteryStatus').attr('checked'));

   //logger('saveOptions: options=:'+ JSON.stringify(options)+':');

   localStorage[IceWatchDefs.ConfigMyName]        = options[IceWatchDefs.ConfigMyName];
   localStorage[IceWatchDefs.ConfigIceName]       = options[IceWatchDefs.ConfigIceName];
   localStorage[IceWatchDefs.ConfigIcePhone]      = options[IceWatchDefs.ConfigIcePhone];
   localStorage[IceWatchDefs.ConfigHourFormat]    = options[IceWatchDefs.ConfigHourFormat];
   localStorage[IceWatchDefs.ConfigIceBackground] = options[IceWatchDefs.ConfigIceBackground];
   localStorage[IceWatchDefs.ConfigIceTextColor]  = options[IceWatchDefs.ConfigIceTextColor];
   localStorage[IceWatchDefs.ConfigMeBackground]  = options[IceWatchDefs.ConfigMeBackground];
   localStorage[IceWatchDefs.ConfigMeTextColor]   = options[IceWatchDefs.ConfigMeTextColor];
   localStorage[IceWatchDefs.ConfigShowBT]        = options[IceWatchDefs.ConfigShowBT];
   localStorage[IceWatchDefs.ConfigShowBattery]   = options[IceWatchDefs.ConfigShowBattery];

   return options;
} // saveOptions

function sendForm()
{
   //logger("configPage: Submit clicked");
   var return_to = getQueryParam('return_to', 'pebblejs://close#');

   //logger("options = " +  JSON.stringify(saveOptions()));
   var location = return_to + encodeURIComponent(JSON.stringify(saveOptions()));
   //logger("configPage: Warping to: " + location);
   document.location = location;
} // sendForm

function cancelForm()
{
   //logger("configPage: Cancel clicked");
   saveOptions();
   //document.location = "pebblejs://close";
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
