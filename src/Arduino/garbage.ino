#include <DFRobot_HX711.h>
#include <HCSR04.h>

#define trig (0)
#define echo (1)

#define DT (2)
#define CLK (3)


DFRobot_HX711 MyScale(DT, CLK);                    



HCSR04 hc(trig, echo);
float dist;

unsigned long last_dist_m = millis();
void setup() {
  Serial.begin(9600);
  MyScale.setCalibration(1992);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  get_dist();
  Serial.print("dist");
  Serial.println(dist);

  Serial.print(MyScale.readWeight(), 1);
  Serial.println(" g");
  delay(2000);
}


void get_dist(){
  if(millis()-last_dist_m>60){
    dist = hc.dist();
    last_dist_m = millis();
  }
}