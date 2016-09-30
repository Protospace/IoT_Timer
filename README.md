# IoT_Timer
Internet of Things Demonstration using ESP8266

This project demonstrates

* Using an ESP8266 with I2C LED display
* Using an ESP8266 to send data to a "cloud" data service
* Using PHP to retrieve said data

When loaded onto the ESP8266 (NodeMCU in my case), it will monitor a pin for power. If power is detected it signals the data service that a session started (passing the machine identifier), and counts seconds. After the session is over the data service is pinged again to say so.

Data is retreived in raw JSON format currently just to show it is there.

![Fritzing](https://github.com/Protospace/IoT_Timer/blob/master/iot-esp8266_bb.png?raw=true)

![Photo](https://github.com/Protospace/IoT_Timer/blob/master/iot__arduino__esp8266.jpg?raw=true)
