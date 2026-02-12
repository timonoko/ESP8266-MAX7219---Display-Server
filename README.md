# ESP8266-01 MD_MAX72XX - Display

8266 broke down after only 6 years. Made micropython-version with ESP32.
Starts with boot.py

The clent "ulostus3" is now quite special, it codes the message in hexadecimal for maximal transparency.

=========

Server-type Wifi clock, which only shows messages from my desktop machine. 

Example: 192.168.1.24/M/"The time is $(date +'%H:%M')"

Brightness: 192.168.1.24/BMinus and 192.168.1.24/BPlus

That display is from Banggood.  "MAX7219 Dot Matrix Module 4-in-1 LED" -- two of those: "#define MAX_DEVICES 8". 

Does not understand UTF-8-ÄÖÅ : "iconv -f UTF-8 -t ISO-8859-1" 

I have 3 of these. They show ALL IMPORTANT STUFF in every room, so no need to check your phone or computer all the time.

*NEW*: Added 60 seconds timer, exclaims "**\*POIKKI\***" if wifi is not working.

<IMG src=kuva.png>
