Made by: Action, 2021

It uses a rotary encoder and an RGB LED... as you turn the rotary encoder, the RGB LED starts to scroll through the colour wheel.

Plug in the rotary encoder like this:
CLK --> PIN 2
DT --> PIN 3
SW --> PIN 4

Plug in the RGB LED like this:
RedPin --> 11
GreenPin --> 10
BluePin --> 9

It should then work once the arduino is plugged in and turned on.
It also prints to the console what value it's at (kind of fun if you want to know)

Sorry about the terrible variable names and bad commenting. This was made a little while ago so the code may not be the greatest. 
It's not too complicated so you should be able to understand it.

Basically it just increases a main colour value, if it goes past 255, it starts mixing two colours. 
Example, if R=255 --> Start mixing 255R + nG until G>255. After, subtract from R colour value until R=0 --> Then add B until B=255, and so on.
