# Virtual machine as flashstation and debugging tool for luftdaten.info

Goal: create a small virtual machine with all necessary drivers and tools to flash and debug sensor stations of [luftdaten.info](https://luftdaten.info). 
Many systems lack driver support or make it overly complex to install a simple usb2serial chip device (affected systems: Windows, OSX).
Idea is to start a virtual machine, hand over the USB and everyhing is fine.


Necessary:
* support for esp8266 nodmcu platforms
* git, esptool(s)
	https://github.com/igrr/esptool-ck

* scripts for flashing and debugging


git clone https://github.com/themadinventor/esptool
git clone 


# System install

* https://wiki.alpinelinux.org/wiki/Installation
* https://wiki.alpinelinux.org/wiki/VirtualBox_guest_additions


    apk add git
    apk add virtualbox-additions-grsec
