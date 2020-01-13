#include "HX711.h"

#define DOUT1 2
#define CLK1 3

#define DOUT2 4
#define CLK2 5

#define DOUT3 6
#define CLK3 7

#define DOUT4 8
#define CLK4 9

#define DOUT5 10
#define CLK5 11

HX711 balanca1;
HX711 balanca2;
HX711 balanca3;
HX711 balanca4;
HX711 balanca5;

float calibration_factor1 = 101800;
float calibration_factor2 = 101800;
float calibration_factor3 = 101800;
float calibration_factor4 = 101800;
float calibration_factor5 = 101800;

float peso1;
float peso2;
float peso3;
float peso4;
float peso5;

void setup() {
  Serial.begin(9600);
  balanca1.begin(DOUT1, CLK1);
  balanca2.begin(DOUT2, CLK2);
  balanca3.begin(DOUT3, CLK3); 
  balanca4.begin(DOUT4, CLK4); 
  balanca5.begin(DOUT5, CLK5); 

  balanca1.set_scale(calibration_factor1);
  balanca2.set_scale(calibration_factor2);
  balanca3.set_scale(calibration_factor3);
  balanca4.set_scale(calibration_factor4);
  balanca5.set_scale(calibration_factor5);
  zeraBalanca();
}

void zeraBalanca ()
{
  Serial.println();
  balanca1.tare();
  balanca2.tare();
  balanca3.tare();
  balanca4.tare();
  balanca5.tare();
  Serial.println("Balança Zerada");
}

void loop()
{
  Serial.print("Peso1: ");
  peso1 = balanca1.get_units();
  Serial.print(peso1, 3);
  Serial.print(" kg");
  Serial.print("\t");

  Serial.print("Peso2: ");
  peso2 = balanca2.get_units();
  Serial.print(peso2, 3);
  Serial.print(" kg");
  Serial.print("\t");

  Serial.print("Peso3: ");
  peso3 = balanca3.get_units();
  Serial.print(peso3, 3);
  Serial.print(" kg");
  Serial.print("\t");

  Serial.print("Peso4: ");
  peso4 = balanca4.get_units();
  Serial.print(peso4, 3);
  Serial.print(" kg");
  Serial.print("\t");

  Serial.print("Peso5: ");
  peso5 = balanca5.get_units();
  Serial.print(peso5, 3);
  Serial.println(" kg");
 
  delay(500);
}
