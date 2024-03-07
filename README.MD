# RFID Reader Example Code 
Made for use by students in workshops run by the Melbourne University Electrical Engineering Club and any other interested parties.

This code implements both an RFID Reading Mode and Writing Mode, selectable by a boolean allowing for easy code extension. The PiicoDev RFID Reader has 4 selectable I2C addresses, so the variable storing the address may need to be updated, or set the reader to use the default address with the dip switches. The 'verified' card needs to be stored into the given variable by enabling reader mode, scanning the card, and then inputting the data that is read.

I created this because the example code for the PiicoDev RFID Reader Modules was written in micropython, and these are the cheapest RFID readers available.
Link: https://core-electronics.com.au/piicodev-rfid-module.html

<img src="piicodev-rfid-module.png" width="350"/>
