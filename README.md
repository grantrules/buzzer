# Buzzer

The lock on my apartment building is broken and I had a wifi Arduino and servo laying around so I made something so I could buzz myself in remotely

It's using a Wemos D1 clone from here: https://www.ebay.com/itm/352672397532

And an SG90 servo

The Arduino runs an HTTP service that'll move the servo.

The Node.js app calls the Arduino service
