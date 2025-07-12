#include <SoftwareSerial.h>

// Define SoftwareSerial pins (D6 = RX, D5 = TX)
SoftwareSerial mySerial(D6, D5);

void setup() {
  Serial.begin(115200); // Serial monitor
  mySerial.begin(9600); // Start with base 9600
  Serial.println("NodeMCU 2: UART Slave Initialized");
}

void loop() {
  // Check for baud rate change command
  if (mySerial.available()) {
    String command = mySerial.readStringUntil('\n');
    command.trim();
    if (command.startsWith("BAUD:")) {
      int baud = command.substring(5).toInt();
      mySerial.end();
      delay(50); // Allow line to settle
      mySerial.begin(baud);
      Serial.print("NodeMCU 2: Switched to baud ");
      Serial.println(baud);
      return;
    }

    // Echo message back
    Serial.print("NodeMCU 2: Received '");
    Serial.print(command);
    Serial.println("'");

    mySerial.println(command);
    Serial.println("NodeMCU 2: Echoed message");
  }
}
