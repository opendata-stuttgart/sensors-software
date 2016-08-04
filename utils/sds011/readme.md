# A logger script for the SDS011

This is a small logger script for the SDS011 particle sensor.
Connect the device via serial to your computer (e.g. via USB2serial) and run the python program. 
To change the device, have the path/name as first argument, like:

	./sds011logger.py /dev/ttyUSB0

To log on console and into a file just use redirection or tee:

	./sds011logger.py /dev/ttyUSB0 | tee -a ~/sdslog_0.csv

Three values per reading are the output, they are TAB separated. 
With a header the output would be like:

    datetime[UTC]	PM2.5[μg/m3]	PM10[μg/m3]
    2016-08-03 22:08:28.293635	12.6	9.4

Time is always in time zone UTC, to avoid time zone offsets and resulting errors or misinterpretations.

The class code was adapted from [FriskByBergen](https://github.com/FriskByBergen/RPiParticle/blob/master/lib/sds011.py).
See [spec sheet](https://github.com/opendata-stuttgart/meta/blob/master/files/SDS011-V1.3.pdf) for details.


