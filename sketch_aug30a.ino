#include <ESP8266WiFi.h>
#include <Servo.h>
 
const int relayPin = D1;
const int chipSelect = D8;
const char* ssid = "PLDTHOMEDSL9J9E0";
const char* password = "garingagaringa";
  
WiFiServer server(80);
  
void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(relayPin, OUTPUT);
    
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
  
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match the request
  
  int value = LOW;
  if (request.indexOf("/relay=on") != -1) {
    digitalWrite(relayPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/relay=off") != -1){
    digitalWrite(relayPin, LOW);
    value = LOW;
  }  
}
