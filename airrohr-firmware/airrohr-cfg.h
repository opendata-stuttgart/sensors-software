

// This file is generated, please do not edit.
// Change airrohr-cfg.h.py instead.

enum ConfigEntryType : unsigned short {
	Config_Type_Bool,
	Config_Type_UInt,
	Config_Type_Time,
	Config_Type_String,
	Config_Type_Password
};

struct ConfigShapeEntry {
	enum ConfigEntryType cfg_type;
	unsigned short cfg_len;
	const __FlashStringHelper* cfg_key;
	union {
		void* as_void;
		bool* as_bool;
		unsigned int* as_uint;
		char* as_str;
	} cfg_val;
};

enum ConfigShapeId {
	Config_current_lang,
	Config_wlanssid,
	Config_wlanpwd,
	Config_www_username,
	Config_www_password,
	Config_fs_ssid,
	Config_fs_pwd,
	Config_www_basicauth_enabled,
	Config_dht_read,
	Config_htu21d_read,
	Config_ppd_read,
	Config_sds_read,
	Config_pms_read,
	Config_hpm_read,
  Config_npm_read,
	Config_sps30_read,
	Config_bmp_read,
	Config_bmx280_read,
	Config_sht3x_read,
	Config_ds18b20_read,
	Config_dnms_read,
	Config_dnms_correction,
	Config_temp_correction,
	Config_gps_read,
	Config_send2dusti,
	Config_ssl_dusti,
	Config_send2madavi,
	Config_ssl_madavi,
	Config_send2sensemap,
	Config_send2fsapp,
	Config_send2aircms,
	Config_send2csv,
	Config_auto_update,
	Config_use_beta,
	Config_has_display,
	Config_has_sh1106,
	Config_has_flipped_display,
	Config_has_lcd1602,
	Config_has_lcd1602_27,
	Config_has_lcd2004,
	Config_has_lcd2004_27,
	Config_display_wifi_info,
	Config_display_device_info,
	Config_debug,
	Config_sending_intervall_ms,
	Config_time_for_wifi_config,
	Config_senseboxid,
	Config_send2custom,
	Config_host_custom,
	Config_url_custom,
	Config_port_custom,
	Config_user_custom,
	Config_pwd_custom,
	Config_ssl_custom,
	Config_send2influx,
	Config_host_influx,
	Config_url_influx,
	Config_port_influx,
	Config_user_influx,
	Config_pwd_influx,
	Config_measurement_name_influx,
	Config_ssl_influx,
};
const char CFG_KEY_CURRENT_LANG[] PROGMEM = "current_lang";
const char CFG_KEY_WLANSSID[] PROGMEM = "wlanssid";
const char CFG_KEY_WLANPWD[] PROGMEM = "wlanpwd";
const char CFG_KEY_WWW_USERNAME[] PROGMEM = "www_username";
const char CFG_KEY_WWW_PASSWORD[] PROGMEM = "www_password";
const char CFG_KEY_FS_SSID[] PROGMEM = "fs_ssid";
const char CFG_KEY_FS_PWD[] PROGMEM = "fs_pwd";
const char CFG_KEY_WWW_BASICAUTH_ENABLED[] PROGMEM = "www_basicauth_enabled";
const char CFG_KEY_DHT_READ[] PROGMEM = "dht_read";
const char CFG_KEY_HTU21D_READ[] PROGMEM = "htu21d_read";
const char CFG_KEY_PPD_READ[] PROGMEM = "ppd_read";
const char CFG_KEY_SDS_READ[] PROGMEM = "sds_read";
const char CFG_KEY_PMS_READ[] PROGMEM = "pms_read";
const char CFG_KEY_HPM_READ[] PROGMEM = "hpm_read";
const char CFG_KEY_NPM_READ[] PROGMEM = "npm_read";
const char CFG_KEY_SPS30_READ[] PROGMEM = "sps30_read";
const char CFG_KEY_BMP_READ[] PROGMEM = "bmp_read";
const char CFG_KEY_BMX280_READ[] PROGMEM = "bmx280_read";
const char CFG_KEY_SHT3X_READ[] PROGMEM = "sht3x_read";
const char CFG_KEY_DS18B20_READ[] PROGMEM = "ds18b20_read";
const char CFG_KEY_DNMS_READ[] PROGMEM = "dnms_read";
const char CFG_KEY_DNMS_CORRECTION[] PROGMEM = "dnms_correction";
const char CFG_KEY_TEMP_CORRECTION[] PROGMEM = "temp_correction";
const char CFG_KEY_GPS_READ[] PROGMEM = "gps_read";
const char CFG_KEY_SEND2DUSTI[] PROGMEM = "send2dusti";
const char CFG_KEY_SSL_DUSTI[] PROGMEM = "ssl_dusti";
const char CFG_KEY_SEND2MADAVI[] PROGMEM = "send2madavi";
const char CFG_KEY_SSL_MADAVI[] PROGMEM = "ssl_madavi";
const char CFG_KEY_SEND2SENSEMAP[] PROGMEM = "send2sensemap";
const char CFG_KEY_SEND2FSAPP[] PROGMEM = "send2fsapp";
const char CFG_KEY_SEND2AIRCMS[] PROGMEM = "send2aircms";
const char CFG_KEY_SEND2CSV[] PROGMEM = "send2csv";
const char CFG_KEY_AUTO_UPDATE[] PROGMEM = "auto_update";
const char CFG_KEY_USE_BETA[] PROGMEM = "use_beta";
const char CFG_KEY_HAS_DISPLAY[] PROGMEM = "has_display";
const char CFG_KEY_HAS_SH1106[] PROGMEM = "has_sh1106";
const char CFG_KEY_HAS_FLIPPED_DISPLAY[] PROGMEM = "has_flipped_display";
const char CFG_KEY_HAS_LCD1602[] PROGMEM = "has_lcd1602";
const char CFG_KEY_HAS_LCD1602_27[] PROGMEM = "has_lcd1602_27";
const char CFG_KEY_HAS_LCD2004[] PROGMEM = "has_lcd2004";
const char CFG_KEY_HAS_LCD2004_27[] PROGMEM = "has_lcd2004_27";
const char CFG_KEY_DISPLAY_WIFI_INFO[] PROGMEM = "display_wifi_info";
const char CFG_KEY_DISPLAY_DEVICE_INFO[] PROGMEM = "display_device_info";
const char CFG_KEY_DEBUG[] PROGMEM = "debug";
const char CFG_KEY_SENDING_INTERVALL_MS[] PROGMEM = "sending_intervall_ms";
const char CFG_KEY_TIME_FOR_WIFI_CONFIG[] PROGMEM = "time_for_wifi_config";
const char CFG_KEY_SENSEBOXID[] PROGMEM = "senseboxid";
const char CFG_KEY_SEND2CUSTOM[] PROGMEM = "send2custom";
const char CFG_KEY_HOST_CUSTOM[] PROGMEM = "host_custom";
const char CFG_KEY_URL_CUSTOM[] PROGMEM = "url_custom";
const char CFG_KEY_PORT_CUSTOM[] PROGMEM = "port_custom";
const char CFG_KEY_USER_CUSTOM[] PROGMEM = "user_custom";
const char CFG_KEY_PWD_CUSTOM[] PROGMEM = "pwd_custom";
const char CFG_KEY_SSL_CUSTOM[] PROGMEM = "ssl_custom";
const char CFG_KEY_SEND2INFLUX[] PROGMEM = "send2influx";
const char CFG_KEY_HOST_INFLUX[] PROGMEM = "host_influx";
const char CFG_KEY_URL_INFLUX[] PROGMEM = "url_influx";
const char CFG_KEY_PORT_INFLUX[] PROGMEM = "port_influx";
const char CFG_KEY_USER_INFLUX[] PROGMEM = "user_influx";
const char CFG_KEY_PWD_INFLUX[] PROGMEM = "pwd_influx";
const char CFG_KEY_MEASUREMENT_NAME_INFLUX[] PROGMEM = "measurement_name_influx";
const char CFG_KEY_SSL_INFLUX[] PROGMEM = "ssl_influx";
static constexpr ConfigShapeEntry configShape[] PROGMEM = {
	{ Config_Type_String, sizeof(cfg::current_lang)-1, FPSTR(CFG_KEY_CURRENT_LANG), cfg::current_lang },
	{ Config_Type_String, sizeof(cfg::wlanssid)-1, FPSTR(CFG_KEY_WLANSSID), cfg::wlanssid },
	{ Config_Type_Password, sizeof(cfg::wlanpwd)-1, FPSTR(CFG_KEY_WLANPWD), cfg::wlanpwd },
	{ Config_Type_String, sizeof(cfg::www_username)-1, FPSTR(CFG_KEY_WWW_USERNAME), cfg::www_username },
	{ Config_Type_Password, sizeof(cfg::www_password)-1, FPSTR(CFG_KEY_WWW_PASSWORD), cfg::www_password },
	{ Config_Type_String, sizeof(cfg::fs_ssid)-1, FPSTR(CFG_KEY_FS_SSID), cfg::fs_ssid },
	{ Config_Type_Password, sizeof(cfg::fs_pwd)-1, FPSTR(CFG_KEY_FS_PWD), cfg::fs_pwd },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_WWW_BASICAUTH_ENABLED), &cfg::www_basicauth_enabled },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_DHT_READ), &cfg::dht_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HTU21D_READ), &cfg::htu21d_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_PPD_READ), &cfg::ppd_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SDS_READ), &cfg::sds_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_PMS_READ), &cfg::pms_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HPM_READ), &cfg::hpm_read },
  { Config_Type_Bool, 0, FPSTR(CFG_KEY_NPM_READ), &cfg::npm_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SPS30_READ), &cfg::sps30_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_BMP_READ), &cfg::bmp_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_BMX280_READ), &cfg::bmx280_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SHT3X_READ), &cfg::sht3x_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_DS18B20_READ), &cfg::ds18b20_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_DNMS_READ), &cfg::dnms_read },
	{ Config_Type_String, sizeof(cfg::dnms_correction)-1, FPSTR(CFG_KEY_DNMS_CORRECTION), cfg::dnms_correction },
	{ Config_Type_String, sizeof(cfg::temp_correction)-1, FPSTR(CFG_KEY_TEMP_CORRECTION), cfg::temp_correction },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_GPS_READ), &cfg::gps_read },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2DUSTI), &cfg::send2dusti },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SSL_DUSTI), &cfg::ssl_dusti },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2MADAVI), &cfg::send2madavi },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SSL_MADAVI), &cfg::ssl_madavi },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2SENSEMAP), &cfg::send2sensemap },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2FSAPP), &cfg::send2fsapp },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2AIRCMS), &cfg::send2aircms },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2CSV), &cfg::send2csv },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_AUTO_UPDATE), &cfg::auto_update },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_USE_BETA), &cfg::use_beta },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_DISPLAY), &cfg::has_display },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_SH1106), &cfg::has_sh1106 },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_FLIPPED_DISPLAY), &cfg::has_flipped_display },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_LCD1602), &cfg::has_lcd1602 },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_LCD1602_27), &cfg::has_lcd1602_27 },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_LCD2004), &cfg::has_lcd2004 },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_HAS_LCD2004_27), &cfg::has_lcd2004_27 },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_DISPLAY_WIFI_INFO), &cfg::display_wifi_info },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_DISPLAY_DEVICE_INFO), &cfg::display_device_info },
	{ Config_Type_UInt, 0, FPSTR(CFG_KEY_DEBUG), &cfg::debug },
	{ Config_Type_Time, 0, FPSTR(CFG_KEY_SENDING_INTERVALL_MS), &cfg::sending_intervall_ms },
	{ Config_Type_Time, 0, FPSTR(CFG_KEY_TIME_FOR_WIFI_CONFIG), &cfg::time_for_wifi_config },
	{ Config_Type_String, sizeof(cfg::senseboxid)-1, FPSTR(CFG_KEY_SENSEBOXID), cfg::senseboxid },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2CUSTOM), &cfg::send2custom },
	{ Config_Type_String, sizeof(cfg::host_custom)-1, FPSTR(CFG_KEY_HOST_CUSTOM), cfg::host_custom },
	{ Config_Type_String, sizeof(cfg::url_custom)-1, FPSTR(CFG_KEY_URL_CUSTOM), cfg::url_custom },
	{ Config_Type_UInt, 0, FPSTR(CFG_KEY_PORT_CUSTOM), &cfg::port_custom },
	{ Config_Type_String, sizeof(cfg::user_custom)-1, FPSTR(CFG_KEY_USER_CUSTOM), cfg::user_custom },
	{ Config_Type_Password, sizeof(cfg::pwd_custom)-1, FPSTR(CFG_KEY_PWD_CUSTOM), cfg::pwd_custom },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SSL_CUSTOM), &cfg::ssl_custom },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SEND2INFLUX), &cfg::send2influx },
	{ Config_Type_String, sizeof(cfg::host_influx)-1, FPSTR(CFG_KEY_HOST_INFLUX), cfg::host_influx },
	{ Config_Type_String, sizeof(cfg::url_influx)-1, FPSTR(CFG_KEY_URL_INFLUX), cfg::url_influx },
	{ Config_Type_UInt, 0, FPSTR(CFG_KEY_PORT_INFLUX), &cfg::port_influx },
	{ Config_Type_String, sizeof(cfg::user_influx)-1, FPSTR(CFG_KEY_USER_INFLUX), cfg::user_influx },
	{ Config_Type_Password, sizeof(cfg::pwd_influx)-1, FPSTR(CFG_KEY_PWD_INFLUX), cfg::pwd_influx },
	{ Config_Type_String, sizeof(cfg::measurement_name_influx)-1, FPSTR(CFG_KEY_MEASUREMENT_NAME_INFLUX), cfg::measurement_name_influx },
	{ Config_Type_Bool, 0, FPSTR(CFG_KEY_SSL_INFLUX), &cfg::ssl_influx },
};
