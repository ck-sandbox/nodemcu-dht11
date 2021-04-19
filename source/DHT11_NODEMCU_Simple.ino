#include "DHT.h"
#include <ESP8266WiFi.h>

const char *ssid = "SSID_OF_WIFI";  // Wifi SSID of your Internet connection
const char *pass = "password";      // Replace with password for your wifi

#define DHTPIN  D3                  //pin where the DHT11 is connected
DHT dht(DHTPIN, DHT11);

WiFiClient client;


void setup()
{
  Serial.begin(115200); // Serial monitor Baudrate
  Serial.setTimeout(2000);
  delay(1000);
  
  // Wait for serial to initialize.
  while(!Serial) { }
  
  dht.begin();

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass); // Connecting ESP8266 with Internet enabled Wifi with above mentioned credentials
  while (WiFi.status() != WL_CONNECTED)
  {
  // If the connection was unsuccesfull, it will try again and again
  delay(500);
  Serial.print(".");
}

  // Connection succesfull
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("");
  Serial.println("");
}

int timeSinceLastRead = 0;

void loop()
{
  // Report every 5 seconds.
  if(timeSinceLastRead > 5000) {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C \n");

    timeSinceLastRead = 0;
  }
  delay(100); // 100ms
  timeSinceLastRead += 100;
}
