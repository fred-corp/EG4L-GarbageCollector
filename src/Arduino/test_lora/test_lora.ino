#include <MKRWAN.h>

LoRaModem modem;

String appEui = "0000000000000000";
String appKey = "0CE9DDC6B18F78A7017D1E5546D31759";
int err;
int connected;

void setup() {
  // put your setup code here, to run once:

  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong at attempted join");
    while (1) {}
  }
  modem.setPort(3);


}

void loop() {
  // put your main code here, to run repeatedly:

  modem.beginPacket();
  modem.print("FFFFFFFF");
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
  delay(10000);
}
