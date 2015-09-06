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
   logger('Ready to Zepto!')
   $("#b-cancel").click(cancelForm);
   $("#b-submit").click(sendForm);
   logger("init called ");
	loadOptions();
})();

function init()
{
   //logger("configPage: config page ready");

   $("#b-cancel").click(cancelForm);
   $("#b-submit").click(sendform);

   //Set form values to whatever is passed in.
   logger("init called ");
	loadOptions();
} // init

function loadOptions() {
  var $backgroundColorPicker = $('#backgroundColorPicker');
  var $timeFormatCheckbox = $('#timeFormatCheckbox');

  var storeString = JSON.stringify(localStorage);
  //logger(storeString);
  logger("Test Storage");
  logger( JSON.stringify(localStorage));

  if (localStorage.myName) {
  	  $('#myName').val(localStorage.myName);
	  logger('myName=' + localStorage.myName);
  }
  if (localStorage.iceName) $('#iceName').val(localStorage.iceName);
  if (localStorage.icePhone) $('#icePhone').val(localStorage.icePhone);
  logger('loadOptions: radiohour=:'+ localStorage.radioHour +':');
  if (localStorage.radioHour) {
	 $('#radioHour12').prop('checked',false);
	 $('#radioHour14').prop('checked',false);
  	 if(localStorage.radioHour == 12) $('#radioHour12').prop('checked',true);
  	 if(localStorage.radioHour == 24) $('#radioHour24').prop('checked',true);
  }
  if (localStorage.iceBackgroundColor) $('#iceBackgroundColor').val(localStorage.iceBackgroundColor);
} // loadOptions

function saveOptions()
{
   //logger("saveOptions called");
   var radioVal = $('input[name="radioHour"]:checked').val();
	logger('saveOptions: radiohour=:'+ radioVal +':');
   var options = {
   	"iceName"  : $('#iceName').val()
   	,"icePhone" : $('#icePhone').val()
   	,"myName"   : $('#myName').val()
		,"radioHour" : radioVal
		,"batteryON" : true
		,"iceBackground" : $('#iceBackgroundColor').val()
		,"iceTextColor" : 6
		,"meBackground" : 7
		,"meTextColor" : 8
	};
   logger("iceBackgroundColor = " +  $('#iceBackgroundColor').val());

   logger('saveOptions: options=:'+ JSON.stringify(options)+':');

   localStorage.myName = options.myName;
   localStorage.iceName = options.iceName;
   localStorage.icePhone = options.icePhone;
   localStorage.radioHour = options.radioHour;
   localStorage.iceBackgroundColor = options.iceBackground;

   return options;
} // saveOptions

function sendForm()
{
   //logger("configPage: Submit clicked");
	var return_to = getQueryParam('return_to', 'pebblejs://close#');

   logger("options = " +  JSON.stringify(saveOptions()));
   var location = return_to + encodeURIComponent(JSON.stringify(saveOptions()));
   logger("configPage: Warping to: " + location);
   document.location = location;
} // sendForm

function cancelForm()
{
   //logger("configPage: Cancel clicked");
   document.location = "pebblejs://close";
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
