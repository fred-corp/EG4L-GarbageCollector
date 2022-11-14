#include <Servo.h>

#include <BMP280_DEV.h>
#include <Device.h>

#include <HX711.h>

#include <MKRWAN.h>
#include <HCSR04.h>


#define trig (0)
#define echo (1)

Servo myservo;


HCSR04 hc(trig, echo);
float dist;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 7;

const long calibZero = -88180; // Calibration factor

HX711 scale;

LoRaModem modem;

long reading;


float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP280_DEV bmp280;


String appEui = "0000000000000000";
String appKey = "0CE9DDC6B18F78A7017D1E5546D31759";
int err;
int connected;

uint8_t payload[9];

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

  bmp280.begin(); 
  bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set the standby time to 2 seconds
  bmp280.startNormalConversion();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  myservo.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
if (scale.is_ready()) {
    reading = scale.read() - calibZero;
    reading = -reading/168;
    reading = reading/100;
    

    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
  payload[2]=(uint8_t)reading;


  dist = hc.dist();
  if (dist>80){
    dist = 80;
  }
  payload[1]=(uint8_t) dist;
  Serial.println("dist");
  Serial.println(dist);
  if (bmp280.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {
    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));  
  }
  payload[3]=(uint8_t)temperature;
  payload[4]=(uint8_t)altitude;
  payload[5]=(int)pressure>>8;
  payload[6]=(uint8_t)pressure;

  payload[7] = 0x1;

  payload[0] = 0xE7;

  payload[8] = 27 + random(-4,8);

  // Serial.println(payload);
  // Serial.println(String((int)dist, HEX));
  // Serial.println(String((int)reading, HEX));
  // Serial.println(String((int)temperature, HEX));
  // Serial.println(String((int)altitude, HEX));
  // Serial.println(String(pressure, HEX));

  modem.beginPacket();
  modem.write(payload,9);

  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }

  if(reading>10 && dist<40){
    myservo.write(180);
    Serial.println("servo");
  }
  else{
    myservo.write(0);
  }
  delay(10000);
}
