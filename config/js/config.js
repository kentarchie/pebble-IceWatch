// code that runs in the configuration web page
var ConfigData = {};
$().ready(init);

function clearLog()
{
  $('#logger').html('');
} // clearLog

function logger(str)
{
  console.log('Config.js: ' + str);
} // logger

function init()
{
   logger('init start');
   $('#b-cancel').click(cancelForm);
   $('#b-submit').click(sendForm);

   var query = location.search.substring(1);
   ConfigData = JSON.parse(decodeURIComponent(query).split('&')[0]);
   logger('init: ConfigData = :'+ JSON.stringify(ConfigData) +':');
   logger('init: ConfigData[model] = :'+ ConfigData['model'] +':');

   setupOptions(ConfigData);
   phoneSetup('icePhone');
} // init

function decToHexString(d)
{
  return '#' + d.toString(16);
} // decToHexString

function setupOptions()
{
  logger('setupOptions: ConfigData.KEY_CONTACT_NAME = :'+ ConfigData.KEY_CONTACT_NAME +':');
  $('#myName').val(ConfigData['KEY_MY_NAME']);
  $('#iceName').val(ConfigData['KEY_CONTACT_NAME']);

  $('#icePhone').val(ConfigData['KEY_CONTACT_PHONE']);

  $('#hourFormat12').attr('checked',false);
  $('#hourFormat24').attr('checked',false);
  if (ConfigData['KEY_HOUR_FORMAT'] == 12) $('#hourFormat12').attr('checked',true);
  if (ConfigData['KEY_HOUR_FORMAT'] == 24) $('#hourFormat24').attr('checked',true);

  $('#showBatteryStatus').attr('checked',  ConfigData['KEY_SHOW_BATTERY'] == 'true');
  $('#showBTStatus').attr('checked',  ConfigData['KEY_SHOW_BT'] == 'true');

  if(ConfigData['model']['platform'] != 'aplite') {
     logger('setupOptions: [KEY_ICE_BACKGROUND] config:'+ConfigData['KEY_ICE_BACKGROUND']+': hex=:'+decToHexString(ConfigData['KEY_ICE_BACKGROUND'])+':');
     logger('setupOptions: [KEY_ME_BACKGROUND] config:'+ConfigData['KEY_ME_BACKGROUND']+': hex=:'+decToHexString(ConfigData['KEY_ME_BACKGROUND'])+':');
     logger('setupOptions: [KEY_ICE_TEXTCOLOR] config:'+ConfigData['KEY_ICE_TEXTCOLOR']+': hex=:'+decToHexString(ConfigData['KEY_ICE_TEXTCOLOR'])+':');
     logger('setupOptions: [KEY_ME_TEXTCOLOR] config:'+ConfigData['KEY_ME_TEXTCOLOR']+': hex=:'+decToHexString(ConfigData['KEY_ME_TEXTCOLOR'])+':');
   
     $('#iceBackgroundColor').val(decToHexString(ConfigData['KEY_ICE_BACKGROUND']));
     $('#meBackgroundColor').val(decToHexString(ConfigData['KEY_ME_BACKGROUND']));
     $('#iceTextColor').val(decToHexString(ConfigData['KEY_ICE_TEXTCOLOR']));
     $('#meTextColor').val(decToHexString(ConfigData['KEY_ME_TEXTCOLOR']));
   }
   else {
     $('#colorPicker').hide();
   }
} // setupOptions

function makeOptionString()
{
   ConfigData['KEY_CONTACT_NAME'] = $('#iceName').val();
   ConfigData['KEY_CONTACT_PHONE'] = $('#icePhone').val();
   ConfigData['KEY_MY_NAME'] = $('#myName').val();

   ConfigData['KEY_HOUR_FORMAT'] = parseInt($('input[name="hourFormat"]:checked').val());

   ConfigData['KEY_ICE_BACKGROUND'] = $('#iceBackgroundColor').val();
   ConfigData['KEY_ICE_TEXTCOLOR'] = $('#iceTextColor').val();
   ConfigData['KEY_ME_BACKGROUND'] = $('#meBackgroundColor').val();
   ConfigData['KEY_ME_TEXTCOLOR'] = $('#meTextColor').val();
   ConfigData['KEY_SHOW_BATTERY'] = ($('#showBatteryStatus').attr('checked')) ? 1 : 0;
   ConfigData['KEY_SHOW_BT'] = ($('#showBTStatus').attr('checked')) ? 1 : 0;
   logger('optionString=:'+JSON.stringify(ConfigData));
   return(JSON.stringify(ConfigData));
} // makeOptionString

function sendForm()
{
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

// from http://jsfiddle.net/mykisscool/VpNMA/
function phoneSetup(phoneElement) 
{
   $('#'+phoneElement)
	.keydown(function (e) {
		var key = e.charCode || e.keyCode || 0;
		$phone = $(this);

		// Auto-format- do not expose the mask as the user begins to type
		if (key !== 8 && key !== 9) {
			if ($phone.val().length === 4) $phone.val($phone.val() + ')');
			if ($phone.val().length === 5) $phone.val($phone.val() + ' ');
			if ($phone.val().length === 9) $phone.val($phone.val() + '-');
		}

		// Allow numeric (and tab, backspace, delete) keys only
		return (key == 8 || 
				key == 9 ||
				key == 46 ||
				(key >= 48 && key <= 57) ||
				(key >= 96 && key <= 105));	
	})
	
	.bind('focus click', function () {
		$phone = $(this);
		
		if ($phone.val().length === 0) {
			$phone.val('(');
		}
		else {
			var val = $phone.val();
			$phone.val('').val(val); // Ensure cursor remains at the end
		}
	})
	
	.blur(function () {
		$phone = $(this);
		if ($phone.val() === '(') $phone.val('');
	});
}
