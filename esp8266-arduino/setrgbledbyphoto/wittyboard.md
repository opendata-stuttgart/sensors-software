# Witty Cloud Board

Original site (chinese):
http://site.gizwits.com/en/developer/

http://www.schatenseite.de/2016/04/22/esp8266-witty-cloud-modul/


http://tech.scargill.net/new-esp-boards/

Albrecht says:
December 19, 2015 at 6:02 pm

Yes, these two boards have shown up several weeks ago. I ordered both, the Wemos D1 mini and 2 of the Gizwits Witty Cloud Boards (the right one). The Gizwits boards already arrived here. I have played around a little bit with them the last days. It is not bad what you get for a little over 2.70€ but there are some drawbacks to mention.

The board has a width of 12 pins (not breadboard friendly).

The micro-USB connector on the top board is for power only, the USB-Serial-chip on the bottom board is a CH340 with a micro-USB data and power connector. You can’t bypass the LDO on the top board (no extra pin). When powering up from the lower USB-serial-adapter board it is starting in flash mode, you need then to press the reset button once to start in normal operation mode.

Connected onboard inputs and outputs:
The on-top light resistor is connected to the ADC. The measurable range is quite limited, especially when it comes to bright light.
PIN 4: Button below antenna on top board, pulls low when pressed
PIN 12: green LED in RGB-LED
PIN 13: blue LED in RGB-LED
PIN 15: red LED in RGB-LED
The LEDs are still glowing a little bit when not initialized as output.

Adam is probably right with his hint at the position of the small metal switch under the antenna ... unfortunately. The WiFi-performance is not as good as what I expected from an ESP-12f module. The direct comparison between my 2 Gizwits Witty Cloud boards and my other ESP8266-boards using the ESP8266/Arduino WiFiScan sketch shows that some other ESP8266-boards have better sensitivity (measured from the same position on my desk in my office).

At all it is a nice all-in-one board for learning (e. g. student courses), because it is very cheap and equipped with directly usable inputs and outputs.
