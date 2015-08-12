$().ready(init);

function init()
{
   console.log("configPage: config page ready");

   $("#b-cancel").click(cancelForm);
   $("#b-submit").click(sendform);

   //Set form values to whatever is passed in.
   console.log('configPage: getting passed parameters');
	loadOptions();
} // init

function loadOptions() {
  var $backgroundColorPicker = $('#backgroundColorPicker');
  var $timeFormatCheckbox = $('#timeFormatCheckbox');

  if (localStorage.myName) $('#myName').value = localStorage.myName;
  if (localStorage.iceName) $('#iceName').value = localStorage.iceName;
  if (localStorage.icePhone) $('#icePhone').value = localStorage.icePhone;
  if (localStorage.radioHour) {
  	 $('#radioHour12').checked = false;
  	 $('#radioHour24').checked = false;
  	 if(localStorage.radioHour == 12) $('#radioHour12').checked = true;
  	 if(localStorage.radioHour == 24) $('#radioHour24').checked = true;
  }
}

function saveOptions()
{
   console.log("saveOptions called");
   var options = {}
   options['myName']   = $('#myName').val();
   options['iceName']  = $('#iceName').val();
   options['icePhone'] = $('#icePhone').val();
	if($('#radioHour12).checked) options['radioHour'] = 12;
	if($('#radioHour24).checked) options['radioHour'] = 24;
   //console.log('saveOptions: options=:'+ JSON.stringify(options)+':');

   localStorage.myName = options.myName;
   localStorage.iceName = options.iceName;
   localStorage.icePhone = options.icePhone;
   localStorage.radioHour = options.radioHour;

   return options;
} // saveOptions

function sendForm()
{
   console.log("configPage: Submit clicked");
	var return_to = getQueryParam('return_to', 'pebblejs://close#');

   var location = return_to + encodeURIComponent(JSON.stringify(saveOptions()));
   console.log("configPage: Warping to: " + location);
   document.location.href = location;
} // sendForm

function cancelForm()
{
   console.log("configPage: Cancel clicked");
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
