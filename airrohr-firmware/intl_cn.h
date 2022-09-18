/* 
 *  airRohr firmware
 *  Copyright (C) 2016-2018 Code for Stuttgart a.o. 
 *
 *  Chinese translation
 * 
 *	Texts should be as short as possible
 */

#define INTL_LANG "CN"
#define INTL_PM_SENSOR "颗粒物传感器"
const char INTL_CONFIGURATION[] PROGMEM = "配置";
#define INTL_WIFI_SETTINGS "WiFi设置"
#define INTL_WIFI_NETWORKS "加载wifi网络..."
#define INTL_LANGUAGE "语种"
const char INTL_NO_NETWORKS[] PROGMEM =  "没有找到WiFi网络";
const char INTL_NETWORKS_FOUND[] PROGMEM = "发现网络。";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "高级设置（仅在您知道自己在做什么的情况下）。";
const char INTL_SAVE[] PROGMEM = "保存";
const char INTL_SENSORS[] PROGMEM = "传感器";
const char INTL_MORE_SENSORS[] PROGMEM = "更多传感器";
const char INTL_SDS011[] PROGMEM = "SDS011({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Tera传感器下一个PM({pm})";
const char INTL_NPM_FULLTIME[] PROGMEM = "Next PM fulltime";
const char INTL_IPS[] PROGMEM = "Piera Systems IPS-7100 ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_SCD30[] PROGMEM = "SCD30 ({t}, {h}, CO₂)";
const char INTL_DS18B20[] PROGMEM = "DS18B20({t})";
const char INTL_DNMS[] PROGMEM = "DNMS({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "修正，单位：dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "以℃为单位进行校正";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "";
const char INTL_NEO6M[] PROGMEM = "GPS（NEO 6M）";
const char INTL_BASICAUTH[] PROGMEM = "认证";
#define INTL_REPORT_ISSUE "报告问题"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi传感器在配置模式下";
const char INTL_FS_WIFI_NAME[] PROGMEM = "网络名称";
const char INTL_MORE_SETTINGS[] PROGMEM = "更多设置";
const char INTL_AUTO_UPDATE[] PROGMEM = "自动更新固件";
const char INTL_USE_BETA[] PROGMEM = "加载测试版固件";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED显示屏翻转";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "显示Wifi信息";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "显示设备信息";

#define INTL_STATIC_IP_TEXT ""
const char INTL_STATIC_IP[] PROGMEM = "";
const char INTL_STATIC_SUBNET[] PROGMEM = "";
const char INTL_STATIC_GATEWAY[] PROGMEM = "";
const char INTL_STATIC_DNS[] PROGMEM = "";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;级别";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "测量间隔(秒)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "持续时间路由器模式";
const char INTL_POWERSAVE[] PROGMEM = "";
const char INTL_MORE_APIS[] PROGMEM = "更多API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "发送数据到自定义API";
const char INTL_SERVER[] PROGMEM = "服务器";
const char INTL_PATH[] PROGMEM = "路径";
const char INTL_PORT[] PROGMEM = "港口";
const char INTL_USER[] PROGMEM = "用户";
const char INTL_PASSWORD[] PROGMEM = "密码";
const char INTL_MEASUREMENT[] PROGMEM = "计量";
const char INTL_SEND_TO[] PROGMEM = "发送至{v}";
const char INTL_READ_FROM[] PROGMEM = "改为{五}。";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "传感器正在重新启动。";
const char INTL_RESTART_DEVICE[] PROGMEM = "重新启动设备";
const char INTL_DELETE_CONFIG[] PROGMEM = "删除保存的配置";
const char INTL_RESTART_SENSOR[] PROGMEM = "重新启动传感器";
#define INTL_HOME "首页"
#define INTL_BACK_TO_HOME "返回首页"
const char INTL_CURRENT_DATA[] PROGMEM = "当前数据";
const char INTL_DEVICE_STATUS[] PROGMEM = "设备状态";
#define INTL_ACTIVE_SENSORS_MAP "有源传感器地图(外部链接)"
#define INTL_CONFIGURATION_DELETE "删除配置"
#define INTL_CONFIGURATION_REALLY_DELETE "你确定要删除配置？"
#define INTL_DELETE "删除"
#define INTL_CANCEL "取消"
#define INTL_REALLY_RESTART_SENSOR "你确定要重新启动传感器吗？"
#define INTL_RESTART "重新启动"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "保存配置并重新启动";
#define INTL_FIRMWARE "固件版本"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "设置调试级别为";
#define INTL_NONE "关闭"
#define INTL_ERROR "唯恐有误"
#define INTL_WARNING "警示"
#define INTL_MIN_INFO "最小信息"
#define INTL_MED_INFO "中部信息"
#define INTL_MAX_INFO "最大信息量"
#define INTL_CONFIG_DELETED "配置被删除"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "不能删除配置"
#define INTL_CONFIG_NOT_FOUND "未找到配置"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "距离第一次测量还有{v}秒。";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " 自上次测量以来的秒数。";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "粒子升";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "颗粒物";
const char INTL_TEMPERATURE[] PROGMEM = "温度";
const char INTL_HUMIDITY[] PROGMEM = "湿度";
const char INTL_PRESSURE[] PROGMEM = "气压";
const char INTL_DEW_POINT[] PROGMEM = "";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA最大";
const char INTL_LATITUDE[] PROGMEM = "纬度";
const char INTL_LONGITUDE[] PROGMEM = "经度";
const char INTL_ALTITUDE[] PROGMEM = "海拔";
const char INTL_TIME_UTC[] PROGMEM = "时间(UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "信号强度";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "信号质量";
#define INTL_NUMBER_OF_MEASUREMENTS "测量数量"
#define INTL_TIME_SENDING_MS "上传时间"
#define INTL_SENSOR "传感器"
#define INTL_PARAMETER "参数"
#define INTL_VALUE "价值"

#include "./airrohr-logo-common.h"
