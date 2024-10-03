#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include <SoftwareSerial.h>


SoftwareSerial mySerial(D5, D6); 
#include <ModbusMaster.h>
ModbusMaster node;

#define MAX485_DE 16
#define MAX485_RE_NEG 5

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

// Replace the next variables with your SSID/Password combination
const char* ssid = ""; // "Syergie Indo Prima"
const char* password = "";//"cahayaharapanhati";
const char* mqtt_server = "192.168.101.10";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


// LED Pin
const int led1_pin = 2;
const int led2_pin = 4;
const int led3_pin = 5;
const int pwm_pin = 23; 

// button pin
const int button1_pin = 18;
const int button2_pin = 19;

int button1_state;
int button2_state;
int pwm_value;

int analog;

void setup() {
  mySerial.begin(9600);

    pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);

  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  pinMode(led3_pin, OUTPUT);

  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);

  node.begin(1, mySerial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);


}

void setup_wifi() {
  delay(10);
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  
  if (String(topic) == "out1") {
    uint8_t result;
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("ON");
      node.writeSingleCoil(128, 1);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
    else if(messageTemp == "off"){
      Serial.println("OFF");
      node.writeSingleCoil(128, 0);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
  }


  if (String(topic) == "out2") {
    uint8_t result;
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("ON");
      node.writeSingleCoil(129, 1);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
    else if(messageTemp == "off"){
      Serial.println("OFF");
      node.writeSingleCoil(129, 0);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
  }


  if (String(topic) == "out3") {
    uint8_t result;
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("ON");
      node.writeSingleCoil(130, 1);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
    else if(messageTemp == "off"){
      Serial.println("OFF");
      node.writeSingleCoil(130, 0);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
  }


  if (String(topic) == "out4") {
    uint8_t result;
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("ON");
      node.writeSingleCoil(131, 1);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
    else if(messageTemp == "off"){
      Serial.println("OFF");
      node.writeSingleCoil(1315, 0);
  
      if (result == node.ku8MBSuccess) {
        Serial.println("Coil written successfully");
      } else {
        Serial.print("Error: ");
        Serial.println(result, HEX);
      }

    }
  }



  if (String(topic) == "button2_send") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("ON");
      digitalWrite(led2_pin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("OFF");
      digitalWrite(led2_pin, LOW);
    }
  }

  if (String(topic) == "button3_send") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("ON");
      digitalWrite(led3_pin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("OFF");
      digitalWrite(led3_pin, LOW);
    }
  }





}



void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");

      client.subscribe("out1");
      client.subscribe("out2");
      client.subscribe("out3");
      client.subscribe("out4");
      client.subscribe("button2_send");
      client.subscribe("button3_send");
      client.subscribe("slider1_send");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

 int result;
  uint16_t data[10]; // Array to store the read data
  
  // Read holding registers starting from address 0, read 10 registers
  result = node.readHoldingRegisters(0, 10);
 
  // Check if the read operation was successful
  if (result == node.ku8MBSuccess) {
    // Print each register value
    for (int i = 0; i < 10; i++) {
      data[i] = node.getResponseBuffer(i); // Get the value of each register
      if (i == 1){
          Serial.println(data[i]);
      }
      
      /*
      Serial.print("Register ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(data[i]);
      */
      }
    
  } else {
    Serial.println("Failed to read holding registers!");
  }
  

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    
    //kirim data 
    analog = analogRead(35);   
    char analog_send[8];
    dtostrf(analog, 1, 2, analog_send);
    
    client.publish("potensiometer", analog_send);
    
    button1_state = !digitalRead(button1_pin);
    if (button1_state == 1){
      client.publish("sensor1", "on");
    } else{
      client.publish("sensor1", "off");
    }


    button2_state = !digitalRead(button2_pin);
    if (button2_state == 1){
      client.publish("sensor2", "on");
    } else{
      client.publish("sensor2", "off");
    }



  }
}
