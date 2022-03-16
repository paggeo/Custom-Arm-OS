#include <Wire.h>

#define ADDRESS 21

const char *answer = "HELLO_I2C";

void setup() {

  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  Serial.begin(230400); 
  Wire.setClock(100000);
  Wire.begin(ADDRESS);
  Wire.onRequest(request_data);
  Wire.onReceive(receive_data);
  

  
  Serial.println("I2C Slave Initialized.");
}

void receive_data() {
  //Serial.println("pas kalaaa?.");
  while (Wire.available() > 0) {
    char buffer[32];
    char b = Wire.read();
    sprintf(buffer, "Received: %2.2X - %c", b, b);
    Serial.println(buffer);
  }
}

void request_data() {

  // Send response back to Master
  Wire.write(answer,strlen(answer));
  
  // Print to Serial Monitor
  Serial.print("Sent Data: ");
  Serial.println(answer);
}

void loop() {
  delay(50);
}
