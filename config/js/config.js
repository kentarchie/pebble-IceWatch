$().ready(init);

function init()
{
   console.log("configPage: config page ready");

   $("#b-cancel").click(cancelForm);
   $("#b-submit").click(sendform);

   //Set form values to whatever is passed in.
   console.log('configPage: getting passed parameters');
   var urlData = window.location.search.substring(1);
   console.log('configPage: urlData =:'+ urlData +':');
   var obj = JSON.parse(decodeURIComponent(urlData));
   console.log('configPage: param obj=:'+ JSON.stringify(obj())+':');
   for(key in obj) {
      $("#"+[key]).val(obj[key]);
      $("#"+[key]).val(obj[key]).slider("refresh");       
   }
} // init

function saveOptions()
{
   console.log("saveOptions called");
   var options = {}
   options['myName']   = document.getElementById('myName').value;
   options['iceName']  = document.getElementById('iceName').value;
   options['icePhone'] = document.getElementById('icePhone').value;
   //console.log('saveOptions: options=:'+ JSON.stringify(options)+':');
   return options;
} // saveOptions

function sendForm()
{
   console.log("configPage: Submit clicked");
   var location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(saveOptions()));
   console.log("configPage: Warping to: " + location);
   document.location.href = location;
} // sendForm

function cancelForm()
{
   console.log("configPage: Cancel clicked");
   document.location = "pebblejs://close";
} // cancelForm
