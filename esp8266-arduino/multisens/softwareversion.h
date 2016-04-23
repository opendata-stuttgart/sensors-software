// version info, TODO generate/update externally?
// 

// your initials/acronym, put it into sensorconfig.h and change there
// #define SOFTWARE_VERSION_INITIALS "UNDEF"
// the version
// git tag 0.2.4814a5d // set tag
// git describe --tags // get tag
// set version in softwareversion.h
#ifndef SOFTWARE_VERSION_INITIALS
#define SOFTWARE_VERSION_INITIALS "MULTISENS"
#endif
#define SOFTWARE_VERSION_NUMBER "0.6"

// changelog 
// 0.6: MQTT loop (process incoming/ping)
// 0.5: MQTT implemented, 
//      counter restarts after sending to APIs
//      Strings from values (avoid multiple Float2String)
// 0.4: mqtt tested
// 0.3 WIRELESS_ACTIVE option (for offline use)
// 0.2 introduce version number