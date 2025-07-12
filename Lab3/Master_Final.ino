#include <SoftwareSerial.h>

// Define SoftwareSerial pins (D6 = RX, D5 = TX)
SoftwareSerial mySerial(D6, D5);

// Test parameters
const int baudRates[] = {9600, 38400, 115200};
const int messageSizes[] = {10, 50, 100};
const int intervals[] = {0, 10, 100}; // Delay in ms
const unsigned long testDuration = 10000; // 10 seconds per test
const int timeout = 500; // 500ms timeout for response

void setup() {
  Serial.begin(115200);
  Serial.println("NodeMCU 1: UART Master Stress Test");
}

void loop() {
  for (int baud : baudRates) {
    mySerial.begin(baud);
    Serial.print("Testing baud rate: ");
    Serial.println(baud);
    mySerial.print("BAUD:");
    mySerial.println(baud);
    delay(200); // Allow slave to switch

    bool skipBaud = false;

    for (int size : messageSizes) {
      for (int interval : intervals) {
        float errorRate = runTest(baud, size, interval);
        if (errorRate > 50.0) {
          Serial.print("High baud rate issue detected at ");
          Serial.print(baud);
          Serial.println(" — Skipping remaining tests for this rate.\n");
          skipBaud = true;
          break;
        }
        delay(2000);
      }
      if (skipBaud) break;
    }

    mySerial.end();
  }

  Serial.println("All tests complete. Restarting in 10 seconds...\n");
  delay(10000);
}

float runTest(int baud, int size, int interval) {
  Serial.print("Test: Baud=");
  Serial.print(baud);
  Serial.print(", Size=");
  Serial.print(size);
  Serial.print(" bytes, Interval=");
  Serial.print(interval);
  Serial.println("ms");

  unsigned long startTime = millis();
  int messagesSent = 0, messagesReceived = 0, errors = 0;
  unsigned long bytesSent = 0;
  int sequence = 0;

  String baseMessage = "D";
  while (baseMessage.length() < size - 6) baseMessage += "X";

  while (millis() - startTime < testDuration) {
    String message = String(sequence) + ":" + baseMessage;
    mySerial.println(message);
    bytesSent += message.length() + 2;
    messagesSent++;
    sequence++;

    unsigned long responseStart = millis();
    String receivedData = "";
    bool received = false;

    while (millis() - responseStart < timeout) {
      if (mySerial.available()) {
        char c = mySerial.read();
        if (c == '\n') {
          received = true;
          break;
        }
        receivedData += c;
      }
    }

    receivedData.trim();

    if (received && receivedData == message) {
      messagesReceived++;
    } else {
      errors++;
      if (!received) {
        Serial.println("Timeout error");
      } else {
        Serial.print("Mismatch: Expected '");
        Serial.print(message);
        Serial.print("', Got '");
        Serial.print(receivedData);
        Serial.println("'");
      }
    }

    if (interval > 0) delay(interval);
  }

  float durationSeconds = testDuration / 1000.0;
  float throughput = bytesSent / durationSeconds;
  float messageRate = messagesSent / durationSeconds;
  float errorRate = (errors * 100.0) / messagesSent;

  Serial.println("Test Results:");
  Serial.print("Messages Sent: "); Serial.println(messagesSent);
  Serial.print("Messages Received: "); Serial.println(messagesReceived);
  Serial.print("Errors: "); Serial.println(errors);
  Serial.print("Error Rate: "); Serial.print(errorRate); Serial.println("%");
  Serial.print("Throughput: "); Serial.print(throughput); Serial.println(" bytes/s");
  Serial.print("Message Rate: "); Serial.print(messageRate); Serial.println(" msg/s");
  Serial.println();

  return errorRate;
}
