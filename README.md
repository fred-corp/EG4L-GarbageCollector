# IT4L : GarbageCollector

More than your average Trash Can

## Project goals

* Monitor garbage level & weight
* Raise a flag when full
* Optionnal : Monitor Weather data (temperature, humidity, pressure)
* Visualise data on graphs (Grafana)
* Generate optimal collection routes (based on garbage levels)

## BOM

* Feather M0 LoRaWAN or Arduino MRK WAN 1310
* 1x 3.7V 2000mAh liPo Battery
* 1x HC-SR04 Ultrasonic sensor
* 1x HX711 Load Cell Amplifier & Load Cell
* 1x BME280 Temperature, Humidity, Pressure Sensor (Adafruit breakout)
* 1x SG90 servomotor

## Power needs

* 60mA Feather M0 LoRaWAN or Arduino MRK WAN 1310
* 15mA HC-SR04 Ultrasonic sensor
* 1.5mA : HX711 Load Cell Amplifier & Load Cell
* 1mA BME280 Temperature, Humidity, Pressure Sensor
* ~50mA SG90 servomotor

Power consumption is around 130mA, when measuring and transmitting data.  
Data will be transmitted two times a day, so the battery should last for about 900 days.  
Expected battery lifetime : 2 years

When used in a park, one gateway should be enough (considering a 300m radius).  
When used on streets, a gateway should be placed every 300m.

## MQTT Payload

* Battery : UInt8 (percentage)
* Garbage : UInt8 (height)
* Weight : UInt8 (hg, /10 for kg)
* Temperature : Int8 (d°C, /10 for °C)
* Humidity : UInt8 (percentage)
* Pressure : UInt16 (hPa)

Hex string : ```0xBBGGWWTTHHPPPP```

## Acknowledgements

Proudly made by Frédéric Druppel, Théo Engels, Quentin Jadoul & Baudouin Losseau.

Made with ❤️, lots of ☕️, and lack of 🛌  
Published under CreativeCommons BY-NC-SA 4.0

[![Creative Commons License](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-nc-sa/4.0/)  
This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).
