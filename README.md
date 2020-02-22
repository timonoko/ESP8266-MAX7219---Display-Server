# ESP8266-01 MD_MAX72XX - Wall-Clock
Server-type Wifi clock, which only shows messages from my desktop machine. 

Example: 192.168.1.24/M/"The time is $(date +'%H:%M')"

Brightness: 192.168.1.24/M/BMinus and 192.168.1.24/M/BPlus

That display is from Banggood.  "MAX7219 Dot Matrix Module 4-in-1 LED" -- two of those: "#define MAX_DEVICES 8". 

Does not understand ÄÖ : "iconv -f UTF-8 -t ISO-8859-1" 

<IMG src=kuva.png>
