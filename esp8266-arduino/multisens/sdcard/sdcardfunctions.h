#ifdef SDCARD_ACTIVE
// put includes in .ino
// #include <SPI.h>
// #include <SD.h>

File outfile;
String outfilename="dflt_out.tmp";

void sdcard_debug_info(){
    serial_out("Default SD_CHIP_SELECT_PIN: ");
    serial_outln(SD_CHIP_SELECT_PIN);
    serial_out("Current SD_CHIP_SELECT_PIN: ");
    serial_outln(pin_sd_cs);
}

// FAT names are 8.3, as in good old 80's
String genoutfilename(){
  outfilename=String(ESP.getChipId());
  if (outfilename.length()>8){
    // name too long, shorten
    outfilename=outfilename.substring(0,8);
  }
  outfilename+=".txt";
  serial_out("outfilename ",5);
  serial_outln(outfilename,5);
  return (outfilename);
}

/*
void sdcard_info(){
  // set up variables using the SD utility library functions:
  Sd2Card sdcard;

  // print the type of card
  serial_out("\nCard type: ");
  switch (sdcard.type()) {
    case SD_CARD_TYPE_SD1:
      serial_outln("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      serial_outln("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      serial_outln("SDHC");
      break;
    default:
      serial_outln("Unknown");
  }
}
*/

/*
void sdcard_listfiles(){
  
  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  SdVolume volume;
  SdFile root;

  if (!volume.init(sdcard)) {
    serial_outln("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }
  
  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  serial_out("\nVolume type is FAT");
  serial_outln(volume.fatType(), DEC);
  serial_outln();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  serial_out("Volume size (bytes): ");
  serial_outln(volumesize);
  serial_out("Volume size (Kbytes): ");
  volumesize /= 1024;
  serial_outln(volumesize);
  serial_out("Volume size (Mbytes): ");
  volumesize /= 1024;
  serial_outln(volumesize);

  serial_outln("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);

}
*/

void outfilePrintString(String str){
    if (outfile){
        outfile.print(str.c_str());
    }
}
void outfilePrintStringln(String str){
    if (outfile){
        outfile.println(str.c_str());
    }
}

void sdcard_echooutfile(){
    outfile.seek(0);
    byte onechar=0;
    while (onechar!=-1){
        onechar=outfile.read();
        serial_out(onechar);
    }
}

void setup_sd(){
  
  if (!SD.begin(pin_sd_cs)){
    serial_outln("SD card initialization failed.",2);
    serial_out("CS configured to GPIO ",2);
    serial_outln(pin_sd_cs,2);
  }
  outfilename=genoutfilename();
  outfile=SD.open(outfilename.c_str(),FILE_WRITE);
  if (!outfile){
      serial_out("SD.open file failed",2);
      return;
  }
  outfile.println("");
  outfilePrintStringln(String("# debug: opened"));
  outfile.flush();
}

void sdcard_printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

#endif //SDCARD_ACTIVE