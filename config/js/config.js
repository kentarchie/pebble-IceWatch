//var IW = require('./js/defs');   // data fields names
//var Defs = IW.IceWatchDefs;
var ConfigData = {};
$().ready(init);

function clearLog()
{
  $('#logger').html('');
} // clearLog

function logger(str)
{
  //var oldStr = $('#logger').html();
  //$('#logger').html(oldStr + '<hr />' + 'config:' + str);
  console.log(str);
} // logger

function init()
{
   logger('init start');
   //logger('init: Defs=:'+typeof Defs+':');
   $('#b-cancel').click(cancelForm);
   $('#b-submit').click(sendForm);

   var query = location.search.substring(1);
   //logger('init: query = :'+query+':');
   //logger('init: decoded query = :'+ decodeURIComponent(query) +':');
   ConfigData = JSON.parse(decodeURIComponent(query).split('&')[0]);
   logger('init: ConfigData = :'+ JSON.stringify(ConfigData) +':');

   setupOptions(ConfigData);
} // init

function decToHexString(d)
{
  return '#' + d.toString(16);
} // decToHexString

function setupOptions()
{
  logger('setupOptions start');
  logger('setupOptions: ConfigData.KEY_CONTACT_NAME = :'+ ConfigData.KEY_CONTACT_NAME +':');
  $('#myName').val(ConfigData['KEY_MY_NAME']);
  $('#iceName').val(ConfigData['KEY_CONTACT_NAME']);
  $('#icePhone').val(ConfigData['KEY_CONTACT_PHONE']);

  $('#hourFormat12').attr('checked',false);
  $('#hourFormat24').attr('checked',false);
  if (ConfigData['KEY_HOUR_FORMAT'] == 12) $('#hourFormat12').attr('checked',true);
  if (ConfigData['KEY_HOUR_FORMAT'] == 24) $('#hourFormat24').attr('checked',true);

  logger('setupOptions: [KEY_ICE_BACKGROUND] config:'+ConfigData['KEY_ICE_BACKGROUND']+': hex=:'+decToHexString(ConfigData['KEY_ICE_BACKGROUND'])+':');
  logger('setupOptions: [KEY_ME_BACKGROUND] config:'+ConfigData['KEY_ME_BACKGROUND']+': hex=:'+decToHexString(ConfigData['KEY_ME_BACKGROUND'])+':');
  logger('setupOptions: [KEY_ICE_TEXTCOLOR] config:'+ConfigData['KEY_ICE_TEXTCOLOR']+': hex=:'+decToHexString(ConfigData['KEY_ICE_TEXTCOLOR'])+':');
  logger('setupOptions: [KEY_ME_TEXTCOLOR] config:'+ConfigData['KEY_ME_TEXTCOLOR']+': hex=:'+decToHexString(ConfigData['KEY_ME_TEXTCOLOR'])+':');
  logger('setupOptions: iceTextColor before:'+$('#iceTextColor').val()+':');
  logger('setupOptions: meTextColor before:'+$('#meTextColor').val()+':');

  logger('setupOptions: iceBackgroundColor before:'+$('#iceBackgroundColor').val()+':');
  $('#iceBackgroundColor').val(decToHexString(ConfigData['KEY_ICE_BACKGROUND']));
  logger('setupOptions: iceBackgoundColor after:'+$('#iceBackgroundColor').val()+':');

  $('#meBackgroundColor').val(decToHexString(ConfigData['KEY_ME_BACKGROUND']));
  $('#iceTextColor').val(decToHexString(ConfigData['KEY_ICE_TEXTCOLOR']));
  $('#meTextColor').val(decToHexString(ConfigData['KEY_ME_TEXTCOLOR']));

  $('#showBatteryStatus').attr('checked',  ConfigData['KEY_SHOW_BATTERY'] == 'true');
  $('#showBTStatus').attr('checked',  ConfigData['KEY_SHOW_BT'] == 'true');

  // from https://github.com/pebble/slate/issues/14
  $('.item-color').change();
} // setupOptions

function makeOptionString()
{
   ConfigData['KEY_CONTACT_NAME'] = $('#iceName').val();
   ConfigData['KEY_CONTACT_PHONE'] = $('#icePhone').val();
   ConfigData['KEY_MY_NAME'] = $('#myName').val();

   ConfigData['KEY_HOUR_FORMAT'] = $('input[name="hourFormat"]:checked').val();

   ConfigData['KEY_ICE_BACKGROUND'] = $('#iceBackgroundColor').val();
   ConfigData['KEY_ICE_TEXTCOLOR'] = $('#iceTextColor').val();
   ConfigData['KEY_ME_BACKGROUND'] = $('#meBackgroundColor').val();
   ConfigData['KEY_ME_TEXTCOLOR'] = $('#meTextColor').val();
   ConfigData['KEY_SHOW_BATTERY'] = ($('#showBatteryStatus').attr('checked')) ? 1 : 0;
   ConfigData['KEY_SHOW_BT'] = ($('#showBTStatus').attr('checked')) ? 1 : 0;
   console.log('optionString=:'+JSON.stringify(ConfigData));
   logger('optionString=:'+JSON.stringify(ConfigData));
   return(JSON.stringify(ConfigData));
} // makeOptionString

function sendForm()
{
   //logger("sendForm: Submit clicked");
   var return_to = getQueryParam('return_to', 'pebblejs://close#');

   logger("sendForm: options = " +  JSON.stringify(makeOptionString()));
   var location = return_to + encodeURIComponent(makeOptionString());
   logger("sendForm: Warping to: " + location);
   document.location = location;
} // sendForm

function cancelForm()
{
   logger("cancelForm: Cancel clicked");
   document.location = "pebblejs://close#";
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
} //getQueryParam
