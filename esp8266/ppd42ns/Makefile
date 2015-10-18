# for using makefile add luatool.py to your path

upload: upload_main upload_init
	luatool.py -l

upload_main:
	luatool.py -f main.lua
	luatool.py -f http.lua

upload_init:
	luatool.py -f init.lua

noop:
	# upload empty init.lua and reboot
	luatool.py -r -f noop_init/init.lua

