# NodeMCU Temperature and Humidity Sensor for HomeKit (Homebride)

## Requirements
 * 1x NodeMCU V3
 * 1x DHT-22
 * Computer (Linux/macOS) with Homebridge installed
 * HomeKit compatible Device (iPhone, iPad, Apple TV)
 

## Sensor
### Source Files
[src/sensor/sensor.ino](./src/sensor/sensor.ino)

## Bridge

### Ubuntu/Raspbian
Install `curl`
```bash
sudo apt install curl
```

### macOS
Install `curl`
```bash
brew install curl
```

### Source Files
[src/bridge/temperature\_humidity\_logger.sh](src/bridge/temperature_humidity_logger.sh)

## Credits
 * [Muhammad Afzal - Temperature Monitoring With DHT22 & Arduino](https://create.arduino.cc/projecthub/attari/temperature-monitoring-with-dht22-arduino-15b013)
 * [ESPWebServer - HelloServer](https://github.com/esp8266/ESPWebServer/tree/master/examples/HelloServer)
