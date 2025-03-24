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

![ESP32-PT2258-Circuit-V1](https://github.com/user-attachments/assets/471f295f-806f-4bff-ad0c-1b315757b7df)

Another random note - I'm NOT a dev... and only understand lots of code on a surface level.  So I used ChatGPT to develope most of it - and I have to say
that my mind was BLOWN by how pleasant, educational, and productive the process was.   From idea to prototype was mere hours - one afternoon and then
the next morning.  If I had not have had a couple of wiring errors it would have been just one afternoon.   Because I had trouble with the wiring, 
ChatGPT got a bit confused in the troubleshooting, thinking it was a code issue, when it was a harware issue.  Once that was fixed... we made
serious tracks!

