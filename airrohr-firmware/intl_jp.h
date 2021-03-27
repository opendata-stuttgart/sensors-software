/* 
 *  airRohr firmware
 *  Copyright (C) 2016-2018 Code for Stuttgart a.o. 
 * 
 *  Japanese translation
 * 
 *	Texts should be as short as possible
 */

#define INTL_LANG "JP"
#define INTL_PM_SENSOR "粒子状物質センサー"
const char INTL_CONFIGURATION[] PROGMEM = "構成";
#define INTL_WIFI_SETTINGS "WiFi設定"
#define INTL_WIFI_NETWORKS "wifiネットワークをロード中 ..."
#define INTL_LANGUAGE "言語"
const char INTL_NO_NETWORKS[] PROGMEM =  "WiFiネットワークが見つからない";
const char INTL_NETWORKS_FOUND[] PROGMEM = "ネットワークを発見。";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "高度な設定（何をしているか分かっている場合のみ";
const char INTL_SAVE[] PROGMEM = "保存";
const char INTL_SENSORS[] PROGMEM = "センサー";
const char INTL_MORE_SENSORS[] PROGMEM = "その他のセンサー";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Tera Sensor Next PM ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "補正量（単位：dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "補正（単位：°C";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "認証";
#define INTL_REPORT_ISSUE "問題を報告する"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "設定モードのWiFiセンサー";
const char INTL_FS_WIFI_NAME[] PROGMEM = "ネットワーク名";
const char INTL_MORE_SETTINGS[] PROGMEM = "より多くの設定";
const char INTL_AUTO_UPDATE[] PROGMEM = "ファームウェアの自動更新";
const char INTL_USE_BETA[] PROGMEM = "ベータ版ファームウェアの読み込み";
const char INTL_DISPLAY[] PROGMEM = "有機EL SSD1306";
const char INTL_SH1106[] PROGMEM = "有機EL SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "有機ELディスプレイフリップ";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Wifi情報の表示";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "デバイス情報の表示";
const char INTL_DEBUG_LEVEL[] PROGMEM = "デバッグ&amp;nbsp;レベル";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "測定間隔（秒";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "持続時間ルータモード";
const char INTL_MORE_APIS[] PROGMEM = "その他のAPI";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "カスタムAPIへのデータ送信";
const char INTL_SERVER[] PROGMEM = "サーバー";
const char INTL_PATH[] PROGMEM = "パス";
const char INTL_PORT[] PROGMEM = "ポート";
const char INTL_USER[] PROGMEM = "ユーザー";
const char INTL_PASSWORD[] PROGMEM = "パスワード";
const char INTL_MEASUREMENT[] PROGMEM = "計測";
const char INTL_SEND_TO[] PROGMEM = "v}に送る";
const char INTL_READ_FROM[] PROGMEM = "v}から読む。";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "センサーが再起動しています。";
const char INTL_RESTART_DEVICE[] PROGMEM = "デバイスの再起動";
const char INTL_DELETE_CONFIG[] PROGMEM = "保存した設定の削除";
const char INTL_RESTART_SENSOR[] PROGMEM = "センサーの再起動";
#define INTL_HOME "ホーム"
#define INTL_BACK_TO_HOME "ホームページに戻る"
const char INTL_CURRENT_DATA[] PROGMEM = "現在のデータ";
const char INTL_DEVICE_STATUS[] PROGMEM = "デバイスの状態";
#define INTL_ACTIVE_SENSORS_MAP "アクティブセンサーマップ（外部リンク"
#define INTL_CONFIGURATION_DELETE "設定の削除"
#define INTL_CONFIGURATION_REALLY_DELETE "本当に設定を削除していいのか？"
#define INTL_DELETE "削除"
#define INTL_CANCEL "キャンセル"
#define INTL_REALLY_RESTART_SENSOR "本当にセンサーを再起動するのか？"
#define INTL_RESTART "再起動"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "設定の保存と再起動";
#define INTL_FIRMWARE "ファームウェアバージョン"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "デバッグレベルを";
#define INTL_NONE "オフ"
#define INTL_ERROR "エラーのみ"
#define INTL_WARNING "警告"
#define INTL_MIN_INFO "min.info"
#define INTL_MED_INFO "mid.info"
#define INTL_MAX_INFO "max.info"
#define INTL_CONFIG_DELETED "設定が削除された"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "コンフィグレーションの削除ができない"
#define INTL_CONFIG_NOT_FOUND "コンフィグレーションが見つからない"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "最初の測定までまだ{v}秒。";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " 最後の測定からの秒数";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "パーティクルライタ";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "粒子状物質";
const char INTL_TEMPERATURE[] PROGMEM = "温度";
const char INTL_HUMIDITY[] PROGMEM = "湿度";
const char INTL_PRESSURE[] PROGMEM = "空気圧";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "L.A.分";
const char INTL_LA_MAX[] PROGMEM = "LA最大";
const char INTL_LATITUDE[] PROGMEM = "緯度";
const char INTL_LONGITUDE[] PROGMEM = "経度";
const char INTL_ALTITUDE[] PROGMEM = "高度";
const char INTL_TIME_UTC[] PROGMEM = "時間(UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "信号強度";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "信号品質";
#define INTL_NUMBER_OF_MEASUREMENTS "測定回数"
#define INTL_TIME_SENDING_MS "アップロードにかかった時間"
#define INTL_SENSOR "センサー"
#define INTL_PARAMETER "パラメータ"
#define INTL_VALUE "価値"

#include "./airrohr-logo-common.h"
