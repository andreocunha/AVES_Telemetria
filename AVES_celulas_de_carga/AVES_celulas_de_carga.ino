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

float calibration_factor1 = 102800;
float calibration_factor2 = 102500;
float calibration_factor3 = 103200;
float calibration_factor4 = 102800;
float calibration_factor5 = 101900;

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
  Serial.println("Balança Zerada\n");
  Serial.println("Pesos em kg\n");
  Serial.print("Peso1:\t");
  Serial.print("Peso2:\t");
  Serial.print("Peso3:\t");
  Serial.print("Peso4:\t");
  Serial.println("Peso5:");
}

void loop()
{
  
  peso1 = balanca1.get_units();
  Serial.print(peso1, 3);
  Serial.print("\t");

  
  peso2 = balanca2.get_units();
  Serial.print(peso2, 3);
  Serial.print("\t");

  
  peso3 = balanca3.get_units();
  Serial.print(peso3, 3);
  Serial.print("\t");

  
  peso4 = balanca4.get_units();
  Serial.print(peso4, 3);
  Serial.print("\t");

  
  peso5 = balanca5.get_units();
  Serial.println(peso5, 3);
 
  delay(500);
}
