# for using makefile add luatool.py to your path

upload: upload_main upload_init
	luatool.py -p /dev/ttyUSB1 -l

upload_main:
	luatool.py -p /dev/ttyUSB1 -f main.lua
	luatool.py -p /dev/ttyUSB1 -f publish.lua

upload_init:
	luatool.py -p /dev/ttyUSB1 -f init.lua

