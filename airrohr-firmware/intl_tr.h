/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Turkish translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "TR";
#define INTL_PM_SENSOR "Hava Kirliliği (Ince Toz) Ölçüm sensörü"
const char INTL_CONFIGURATION[] PROGMEM = "Yapılandırma";
#define INTL_WIFI_SETTINGS "WiFi bağlantı ayarları"
#define INTL_WIFI_NETWORKS " wifi ağlar yükleniyor ..."
#define INTL_LANGUAGE "Lisan"
const char INTL_NO_NETWORKS[] PROGMEM =  "No WiFi-Ağ Bulunamadı";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Bulunan Ağlar: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ileri ayarlar: (Uzmanlar için)";
const char INTL_SAVE[] PROGMEM = "Sakla";
const char INTL_SENSORS[] PROGMEM = "Sensörler";
const char INTL_MORE_SENSORS[] PROGMEM = "More Sensors";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="dB (A) 'da düzeltme";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "yetkilendirme";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi Sensörü Yapılandırma modunda";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Isim";
const char INTL_MORE_SETTINGS[] PROGMEM ="Daha fazla ayar";
const char INTL_AUTO_UPDATE[] PROGMEM = "Yazılımı (Firmware) Otomatik güncelle ";
const char INTL_USE_BETA[] PROGMEM = "Beta Yazılımı(Firmware) yükle";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED ekranını çevirin";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "WiFi Bilgilerini Görüntüle";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Cihaz Bilgilerini Görüntüle";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;seviye";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = " Ölçüm aralığı";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Süre yönlendirici(Router) modu";
const char INTL_MORE_APIS[] PROGMEM = "Daha fazla uygulama programlama arayüzü (API)";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "uygulama programlama arayüzüne (API)veri gönder";
const char INTL_SERVER[] PROGMEM = "Sunucu";
const char INTL_PATH[] PROGMEM = "Yol";
const char INTL_PORT[] PROGMEM = "kapı";
const char INTL_USER[] PROGMEM = "kullanıcı";
const char INTL_PASSWORD[] PROGMEM = "parola";
const char INTL_SEND_TO[] PROGMEM = "Gönder {v}";
const char INTL_READ_FROM[] PROGMEM = "Oku {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "sistem yeniden yükleniyor";
const char INTL_RESTART_DEVICE[] PROGMEM = "Cihazı yeniden bağlat";
const char INTL_DELETE_CONFIG[] PROGMEM = "konfigürasyonu sil";
const char INTL_RESTART_SENSOR[] PROGMEM = "sensörü yeniden bağlat ";
#define INTL_HOME "genel bakış"
#define INTL_BACK_TO_HOME "Ana sayfaya geri dön"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktüel veriler";
const char INTL_DEVICE_STATUS[] PROGMEM = "Cihaz durumu";
#define INTL_ACTIVE_SENSORS_MAP "Aktif sensörler haritası(external link)"
#define INTL_CONFIGURATION_DELETE "Konfigürasyonu sil"
#define INTL_CONFIGURATION_REALLY_DELETE "Konfigürasyonu silmek istediğinizden emin misiniz??"
#define INTL_DELETE "Sil"
#define INTL_CANCEL "vazgeç"
#define INTL_REALLY_RESTART_SENSOR "Sensörü tekrar bağlatmak istediğinizden emin misiniz?"
#define INTL_RESTART "yeniden bağlat"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Kaydet ve yeniden bağlat";
#define INTL_FIRMWARE "Firmware sürümü"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Debug ayarı ";
#define INTL_NONE "off"
#define INTL_ERROR "hatalar"
#define INTL_WARNING "uyarılar"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "ortalama info"
#define INTL_MAX_INFO "maks. info"
#define INTL_CONFIG_DELETED "Konfigürasyon silindi"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfigürasyon silinemiyor"
#define INTL_CONFIG_NOT_FOUND "Konfigürasyon bulunamadı"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Still {v} ilk ölçüme kadar geçen saniye.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " Son ölçümden bu yana geçen saniye.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Ince Toz(Hava Kirliliği) / litre";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Ince Toz(Hava Kirliliği)";
const char INTL_TEMPERATURE[] PROGMEM = "sıcaklık";
const char INTL_HUMIDITY[] PROGMEM = "nem";
const char INTL_PRESSURE[] PROGMEM = "hava basıncı";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Enlem";
const char INTL_LONGITUDE[] PROGMEM = "Boylam";
const char INTL_ALTITUDE[] PROGMEM = "Rakım";
const char INTL_DATE[] PROGMEM = "tarih";
const char INTL_TIME[] PROGMEM = "zaman";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "sinyal gücü";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "sinyal kalitesi";
#define INTL_NUMBER_OF_MEASUREMENTS "Ölçümlerin sayısı"
#define INTL_TIME_SENDING_MS "Göndermede harcanan süre"
#define INTL_SENSOR "algılayıcı(Sensör)"
#define INTL_PARAMETER "Parametre"
#define INTL_VALUE "değer"

#include "./airrohr-logo-common.h"
