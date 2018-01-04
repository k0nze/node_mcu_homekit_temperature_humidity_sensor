// uncomment to see debug messages over serial port
//#define DEBUG

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DHT.h>

// WiFi network, password, static IP, gateway and subnet
const char* ssid = "SSID";
const char* password = "PASSWORD";
#define IP 192,168,0,42
#define GATEWAY 192,168,0,1
#define SUBNET 255,255,255,0

// let webserver listen on port 80
ESP8266WebServer server(80);

// pin and type of the temperature and humidity sensor
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// if a client connects to http://IP "works" will be returned
void handleRoot() {
  server.send(200, "text/plain", "works");
}

// if a client connects to an URL which is not http://IP{/,/temperature,/humidity} a 404 error will be returned
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// if a client connects to http://IP/temperature the current temperature will be returned
void handleTemperature() {
  char message[20];
  float temp;
  
  temp = dht.readTemperature();
  sprintf(message, "%f", temp);
  server.send(200, "text/plain", message);
}

// if a client connects to http://IP/humidity the current humidity will be returned
void handleHumidity() {
  char message[20];
  float hum;
  
  hum = dht.readHumidity();
  sprintf(message, "%f", hum);
  server.send(200, "text/plain", message);
}

void setup() {
  #if defined(DEBUG)
  // setup UART
  Serial.begin(9600);
  #endif

  // setup DHT-22
  dht.begin();

  // setup Wifi connection
  IPAddress ip(IP);   
  IPAddress gateway(GATEWAY);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
    #if defined(DEBUG)
    Serial.print(".");
    #endif
  }
  #if defined(DEBUG)
  Serial.println();
  Serial.println("success!");
  Serial.print("IP address is: ");
  Serial.println(WiFi.localIP());
  #endif

  // setup webserver
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.on("/temperature", handleTemperature);
  server.on("/humidity", handleHumidity);
  
  server.begin();
  #if defined(DEBUG)
  Serial.println("HTTP server started");
  #endif
}

// event loop
void loop() {
   server.handleClient();
}
