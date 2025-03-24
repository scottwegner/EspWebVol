ESP32 and PT2258 digital volume control chip controlled via web/mqtt/hubitat/httpPost

This project is for a little device that is almost hardly necessary in today's world with lots of fully featured whole-home audio solutions.
But I built it to meet a very specific need - I have an amp and FM tuner set up to tune in a local FM station and send the audio 
thoughout speakers in my house.  I have the volume of the amp set at a level which is great most of the time - but when I 
want it changed - I have to go into the basement and change it!   What a hassle right?!  So....

This project just connects up an ESP32 to a PT2258 digital volume control chip so that I can control the stereo line level between the 
AMP and tuner in a number of ways:

1 - just direct from a simple web page and links that say "volume up" and "volume down"
2 - using an http post link and setting an absolute value 0-100 eg: http://x.x.x.x/volume/set?volume=80
3 - via mqtt so that I can automate and use with other home automation ecosystems.  For example - I have it tied to Hubitat for easy access.

I'll post schematics and PCB files as I finish them.

So far the prototype works swimingly!  So, yay team!

