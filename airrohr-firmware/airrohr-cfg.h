
enum ConfigEntryType {
	Config_Type_Bool,
	Config_Type_UInt,
	Config_Type_String
};

struct ConfigShapeEntry {
	ConfigEntryType cfg_type;
	const char* cfg_key;
	union {
		void* as_void;
		bool* as_bool;
		unsigned int* as_uint;
		char* as_str;
	} cfg_val;
};

static constexpr ConfigShapeEntry configShape[] PROGMEM = {
#define Config_Bool(varname) { Config_Type_Bool, #varname, &cfg::varname }
#define Config_String(varname) { Config_Type_String, #varname, cfg::varname }
#define Config_UInt(varname) { Config_Type_UInt, #varname, &cfg::varname }
	Config_String(current_lang),
	Config_String(wlanssid),
	Config_String(wlanpwd),
	Config_String(www_username),
	Config_String(www_password),
	Config_String(fs_ssid),
	Config_String(fs_pwd),
	Config_Bool(www_basicauth_enabled),
	Config_Bool(dht_read),
	Config_Bool(htu21d_read),
	Config_Bool(ppd_read),
	Config_Bool(sds_read),
	Config_Bool(pms_read),
	Config_Bool(hpm_read),
	Config_Bool(sps30_read),
	Config_Bool(bmp_read),
	Config_Bool(bmx280_read),
	Config_Bool(ds18b20_read),
	Config_Bool(dnms_read),
	Config_String(dnms_correction),
	Config_Bool(gps_read),
	Config_Bool(send2dusti),
	Config_Bool(ssl_dusti),
	Config_Bool(send2madavi),
	Config_Bool(ssl_madavi),
	Config_Bool(send2sensemap),
	Config_Bool(send2fsapp),
	Config_Bool(send2aircms),
	Config_Bool(send2csv),
	Config_Bool(auto_update),
	Config_Bool(use_beta),
	Config_Bool(has_display),
	Config_Bool(has_sh1106),
	Config_Bool(has_flipped_display),
	Config_Bool(has_lcd1602),
	Config_Bool(has_lcd1602_27),
	Config_Bool(has_lcd2004_27),
	Config_Bool(display_wifi_info),
	Config_Bool(display_device_info),
	Config_UInt(debug),
	Config_UInt(sending_intervall_ms),
	Config_UInt(time_for_wifi_config),
	Config_String(senseboxid),
	Config_Bool(send2custom),
	Config_String(host_custom),
	Config_String(url_custom),
	Config_UInt(port_custom),
	Config_String(user_custom),
	Config_String(pwd_custom),
	Config_Bool(ssl_custom),
	Config_Bool(send2influx),
	Config_String(host_influx),
	Config_String(url_influx),
	Config_UInt(port_influx),
	Config_String(user_influx),
	Config_String(pwd_influx),
	Config_String(measurement_name_influx),
	Config_Bool(ssl_influx),

#undef Config_Bool
#undef Config_String
#undef Config_Int
};

