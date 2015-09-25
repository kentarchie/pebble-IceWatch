//$().ready(init);

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
   $("#b-cancel").click(cancelForm);
   $("#b-submit").click(sendForm);
	loadOptions();
})();

function init()
{
   $("#b-cancel").click(cancelForm);
   $("#b-submit").click(sendform);

   //Set form values to whatever is passed in.
	loadOptions();
} // init

function loadOptions() {
  var storeString = JSON.stringify(localStorage);
  //logger( JSON.stringify(localStorage));

  if (localStorage.myName) {
  	  $('#myName').val(localStorage.myName);
  }
  if (localStorage.iceName) $('#iceName').val(localStorage.iceName);
  if (localStorage.icePhone) $('#icePhone').val(localStorage.icePhone);
  if (localStorage.hourFormat) {
	 $('#hourFormat12').prop('checked',false);
	 $('#hourFormat24').prop('checked',false);
  	 if (localStorage.hourFormat == 12) $('#hourFormat12').prop('checked',true);
  	 if (localStorage.hourFormat == 24) $('#hourFormat24').prop('checked',true);
  }

  if (localStorage.iceBackgroundColor) 
  		$('#iceBackgroundColor').val(localStorage.iceBackgroundColor);
  if (localStorage.iceTextColor) 
  		$('#iceTextColor').val(localStorage.iceTextColor);
  if (localStorage.meBackgroundColor) 
  		$('#meBackgroundColor').val(localStorage.meBackgroundColor);
  if (localStorage.meTextColor) 
  		$('#meTextColor').val(localStorage.meTextColor);

  if (localStorage.showBatteryStatus) 
  		$('#showBatteryStatus').attr('checked', localStorage.showBatteryStatus == 'true');
  if (localStorage.showBTStatus) 
  		$('#showBTStatus').attr('checked', localStorage.showBTStatus == 'true');
} // loadOptions

function saveOptions()
{
   var hourFormatVal = $('input[name="hourFormat"]:checked').val();
   var options = {
   	"iceName"  : $('#iceName').val()
   	,"icePhone" : $('#icePhone').val()
   	,"myName"   : $('#myName').val()
		,"hourFormat" : hourFormatVal
		,"batteryON" : true
		,"iceBackground" : $('#iceBackgroundColor').val()
		,"iceTextColor" : $('#iceTextColor').val()
		,"meBackground" : $('#meBackgroundColor').val()
		,"meTextColor" : $('#meTextColor').val()
		,"showBTStatus" : $('#showBTStatus').attr('checked'()
		,"showBatteryStatus" : $('#showBatteryStatus').attr('checked')
	};
   //logger("iceBackgroundColor = " +  $('#iceBackgroundColor').val());
   logger("showBTStatus = " +  $('#showBTStatus').attr('checked'));
   //logger("showBatteryStatus.val = " +  $('#showBatteryStatus').val());
   //logger("showBatteryStatus.checked = " +  $('#showBatteryStatus').checked);
   logger("showBatteryStatus.attr = " +  $('#showBatteryStatus').attr('checked'));

   //logger('saveOptions: options=:'+ JSON.stringify(options)+':');

   localStorage.myName = options.myName;
   localStorage.iceName = options.iceName;
   localStorage.icePhone = options.icePhone;
   localStorage.hourFormat = options.hourFormat;
   localStorage.iceBackgroundColor = options.iceBackground;
   localStorage.iceTextColor = options.iceTextColor;
   localStorage.meBackgroundColor = options.meBackground;
   localStorage.meTextColor = options.meTextColor;
   localStorage.showBTStatus = options.showBTStatus;
   localStorage.showBatteryStatus = options.showBatteryStatus;

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
