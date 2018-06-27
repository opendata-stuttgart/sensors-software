# Create Sensor Flash Station on Raspbian


## Install necessary software

Install on the raspberry (raspbian here) as root:

    aptitude install python-pip
    pip install -U platformio

* create /etc/udev/rules.d/95-nodemcu.rules

        # CP210X USB UART
        SUBSYSTEMS=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE:="0666", SYMLINK+="ttyUSBnodemcu$attr{port_number}"


Necessary software

    if [ -z "$rsroot" ] ; then rsroot="/src/raspistation"; echo "rsroot=$rsroot" ;fi
    mkdir -p "$rsroot"
    if [ "$?" != "0" ] ; then echo "cannot create dir /src/raspistation, exiting"; exit 1 ; fi
    pushd "$rsroot"
    git clone https://github.com/paulbarber/raspi-gpio.git
    git clone https://github.com/themadinventor/esptool
    
    # enable i2c
    for modl in snd-bcm2835 i2c-dev
    do
    	if [ -z "$(grep ^$modl /etc/modules)" ] ; then
		echo "$modl" >> /etc/modules
	fi
    done


    popd
