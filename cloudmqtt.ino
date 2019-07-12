#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "****"; // Enter your WiFi name
const char* password =  "****"; // Enter WiFi password
const char* mqttServer = "postman.cloudmqtt.com";
const int mqttPort = 14259;
const char* mqttUser = "****"; // Enter your cloudmqtt username (register here if you dont have an id https://www.cloudmqtt.com/)
const char* mqttPassword = "****"; / /Enter your cloudmqtt password
long randNumber;

WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
      Serial.begin(115200);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
      delay(500);
        Serial.println("Connecting to WiFi..");
      }
      Serial.println("Connected to the WiFi network");

      
}

void loop() {
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(1000);
    }
  }
  randNumber = random(300); // Generate a random number from 0 to 299
  client.publish("Random/Number", String(randNumber).c_str(), true); //Topic name
  client.subscribe("Random/Number");
  delay(1000);
}