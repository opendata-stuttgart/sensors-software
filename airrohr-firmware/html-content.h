const char TXT_CONTENT_TYPE_JSON[] PROGMEM = "application/json";
const char TXT_CONTENT_TYPE_INFLUXDB[] PROGMEM = "application/x-www-form-urlencoded";
const char TXT_CONTENT_TYPE_TEXT_HTML[] PROGMEM = "text/html; charset=utf-8";
const char TXT_CONTENT_TYPE_TEXT_PLAIN[] PROGMEM = "text/plain";
const char TXT_CONTENT_TYPE_IMAGE_SVG[] PROGMEM = "image/svg+xml";

const char DBG_TXT_TEMPERATURE[] PROGMEM = "Temperature: ";
const char DBG_TXT_HUMIDITY[] PROGMEM = "Humidity: ";
const char DBG_TXT_PRESSURE[] PROGMEM = "Pressure: ";
const char DBG_TXT_START_READING[] PROGMEM = "Start reading ";
const char DBG_TXT_END_READING[] PROGMEM = "End reading ";
const char DBG_TXT_CHECKSUM_IS[] PROGMEM = "Checksum is: ";
const char DBG_TXT_CHECKSUM_SHOULD[] PROGMEM = "Checksum should: ";
const char DBG_TXT_DATA_READ_FAILED[] PROGMEM = "Data read failed";
const char DBG_TXT_COULDNT_BE_READ[] PROGMEM = " couldn't be read";
const char DBG_TXT_UPDATE[] PROGMEM = "[update] ";
const char DBG_TXT_UPDATE_FAILED[] PROGMEM = "Update failed.";
const char DBG_TXT_UPDATE_NO_UPDATE[] PROGMEM = "No update.";
const char DBG_TXT_UPDATE_OK[] PROGMEM = "Update ok.";
const char DBG_TXT_SENDING_TO[] PROGMEM = "## Sending to ";
const char DBG_TXT_SENDING_TO_LUFTDATEN[] PROGMEM = "## Sending to Luftdaten.info ";
const char DBG_TXT_CALL_SENSOR[] PROGMEM = "Call sensor";
const char DBG_TXT_SDS011_VERSION_DATE[] PROGMEM = "SDS011 version date";

const char SENSORS_SDS011[] PROGMEM = "SDS011";
const char SENSORS_PPD42NS[] PROGMEM = "PPD42NS";
const char SENSORS_PMSx003[] PROGMEM = "PMSx003";
const char SENSORS_HPM[] PROGMEM = "Honeywell PM";
const char SENSORS_DHT22[] PROGMEM = "DHT22";
const char SENSORS_DS18B20[] PROGMEM = "DS18B20";
const char SENSORS_HTU21D[] PROGMEM = "HTU21D";
const char SENSORS_BMP180[] PROGMEM = "BMP180";
const char SENSORS_BMP280[] PROGMEM = "BMP280";
const char SENSORS_BME280[] PROGMEM = "BME280";

const char WEB_PAGE_HEADER[] PROGMEM = "<!DOCTYPE html><html>\
<head>\
<title>{t}</title>\
<meta name='viewport' content='width=device-width'>\
<style type='text/css'>\
body{font-family:Arial;margin:0}\
.content{margin:10px}\
.r{text-align:right}\
td{vertical-align:top;}\
a{text-decoration:none;padding:10px;background:#38b5ad;color:white;display:block;width:auto;border-radius:5px;}\
.wifi{background:none;color:blue;padding:5px;display:inline;}\
input[type='text']{width:100%;}\
input[type='password']{width:100%;}\
input[type='submit']{border-radius:5px;font-size:medium;padding:5px;}\
.s_green{padding:9px !important;width:100%;border-style:none;background:#38b5ad;color:white;text-align:left;}\
</style>\
</head><body>\
<div style='min-height:120px;background-color:#38b5ad;margin-bottom:20px'>\
<a href='/' style='background:none;width:0;display:inline'><img src='/images?name=luftdaten_logo' style='float:left;margin:20px'/></a>\
<h3 style='margin:0'>{tt}</h3>\
<small>ID: {id}<br/>MAC: {mac}<br/>{fwt}: {fw}</small></div><div class='content'><h4>{h} {n} {t}</h4>";

const char BR_TAG[] PROGMEM = "<br/>";
const char TABLE_TAG_OPEN[] PROGMEM = "<table>";
const char TABLE_TAG_CLOSE_BR[] PROGMEM = "</table>";
const char EMPTY_ROW[] PROGMEM = "<tr><td colspan='3'>&nbsp;</td></tr>";

const char WEB_PAGE_FOOTER[] PROGMEM = "<br/><br/><a href='/' style='display:inline;'>{t}</a><br/><br/><br/>\
<a href='https://codefor.de/stuttgart/' target='_blank' style='display:inline;background:none;color:black;'>&copy; Open Knowledge Lab Stuttgart a.o. (Code for Germany)</a>\
</div></body></html>\r\n";

const char WEB_ROOT_PAGE_CONTENT[] PROGMEM = "<a href='/values'>{t}</a><br/>\
<a href='https://maps.luftdaten.info/' target='_blank'>{map}</a><br/>\
<a href='/config'>{conf}</a><br/>\
<a href='/removeConfig'>{conf_delete}</a><br/>\
<a href='/reset'>{restart}</a><br/>\
<table style='width:100%;'>\
<tr><td style='width:33%;'><a href='/debug?lvl=0'>Debug null</a></td>\
<td style='width:33%;'><a href='/debug?lvl=1'>Debug Error</a></td>\
<td style='width:33%;'><a href='/debug?lvl=2'>Debug Warning</a></td>\
</tr><tr>\
<td><a href='/debug?lvl=3'>Debug Info low</a></td>\
<td><a href='/debug?lvl=4'>Debug Info medium</a></td>\
<td><a href='/debug?lvl=5'>Debug Info high</a></td>\
</tr>\
</table>\
";

const char WEB_CONFIG_SCRIPT[] PROGMEM = "<script>\
function setSSID(ssid){document.getElementById('wlanssid').value=ssid.innerText||ssid.textContent;document.getElementById('wlanpwd').focus();}\
function load_wifi_list(){var x=new XMLHttpRequest();x.open('GET','/wifi');x.onload = function(){if (x.status === 200) {document.getElementById('wifilist').innerHTML = x.responseText;}};x.send();}\
</script>";

const char WEB_REMOVE_CONFIG_CONTENT[] PROGMEM = "<h3>{t}</h3>\
<table><tr><td><form method='POST' action='/removeConfig'><input type='submit' class='s_green' name='submit' value='{b}'/></form></td><td><a href='/'>{c}</a></td></tr></table>\
";

const char WEB_RESET_CONTENT[] PROGMEM = "<h3>{t}</h3>\
<table><tr><td><form method='POST' action'/reset'><input type='submit' class='s_green' name='submit' value='{b}'/></form></td><td><a href='/'>{c}</a></td></tr></table>\
";

const char WEB_IOS_REDIRECT[] PROGMEM = "<html><body>Redirecting...\
<script type=\"text/javascript\">\
window.location = \"http://192.168.4.1/config\";\
</script>\
</body></html>";
