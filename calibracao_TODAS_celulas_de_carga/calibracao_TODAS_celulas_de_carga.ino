#include <Arduino.h>

#include "HX711.h"

#define DOUT1 2
#define CLK1 3

#define DOUT2 4
#define CLK2 5

#define DOUT3 6
#define CLK3 7

#define DOUT4 8
#define CLK4 9

HX711 balanca1;
HX711 balanca2;
HX711 balanca3;
HX711 balanca4;

float calibration_factor1 = 106000;
float calibration_factor2 = 104000;
float calibration_factor3 = 101500;
float calibration_factor4 = 94500;

float peso1;
float peso2;
float peso3;
float peso4;


void zeraBalanca ()
{
  Serial.println();
  balanca1.tare();
  balanca2.tare();
  balanca3.tare();
  balanca4.tare();
  Serial.println("Balança Zerada\n");
  Serial.println("Pesos em kg\n");
}

void setup() {
  Serial.begin(9600);
  balanca1.begin(DOUT1, CLK1);
  balanca2.begin(DOUT2, CLK2);
  balanca3.begin(DOUT3, CLK3); 
  balanca4.begin(DOUT4, CLK4); 

  balanca1.set_scale(calibration_factor1);
  balanca2.set_scale(calibration_factor2);
  balanca3.set_scale(calibration_factor3);
  balanca4.set_scale(calibration_factor4);
  zeraBalanca();
}


void loop()
{

  balanca1.set_scale(calibration_factor1);                     // ajusta fator de calibração
  balanca2.set_scale(calibration_factor2);
  balanca3.set_scale(calibration_factor3);
  balanca4.set_scale(calibration_factor4);
  
  Serial.print("Peso1: ");                                    // imprime no monitor serial
  Serial.print(balanca1.get_units(), 3);                      // imprime peso da balança com 3 casas decimais
  Serial.print(" kg");
  Serial.print("      Fator de Calibração 1: ");               // imprime no monitor serial
  Serial.println(calibration_factor1);                        // imprime fator de calibração

  Serial.print("Peso2: ");
  Serial.print(balanca2.get_units(), 3);
  Serial.print(" kg");
  Serial.print("      Fator de Calibração 2: ");
  Serial.println(calibration_factor2);

  Serial.print("Peso3: ");
  Serial.print(balanca3.get_units(), 3);
  Serial.print(" kg");
  Serial.print("      Fator de Calibração 3: ");
  Serial.println(calibration_factor3);

  Serial.print("Peso4: ");
  Serial.print(balanca4.get_units(), 3);
  Serial.print(" kg");
  Serial.print("      Fator de Calibração 4: ");
  Serial.println(calibration_factor4);
  
  Serial.println("\n");
  delay(500) ;                                               // atraso de 0,5 segundo
 
  if (Serial.available())                                    // reconhece letra para ajuste do fator de calibração
  {
    char temp = Serial.read();

    switch (temp){

      //---------------------------------------------------------------------
      // PARA CALIBRAR A PRIMEIRA CELULA DE CARGA
      case 'a':
        calibration_factor1 += 100;
        break;

      case 'b':
        calibration_factor1 -= 100;
        break;

      case 'c':
        calibration_factor1 += 1000;
        break;

      case 'd':
        calibration_factor1 -= 1000;
        break;

      case 'e':
        calibration_factor1 += 10000;
        break;

      case 'f':
        calibration_factor1 -= 10000;
        break;
      //---------------------------------------------------------------------

      //---------------------------------------------------------------------
      // PARA CALIBRAR A SEGUNDA CELULA DE CARGA
      case 'g':
        calibration_factor2 += 100;
        break;

      case 'h':
        calibration_factor2 -= 100;
        break;

      case 'i':
        calibration_factor2 += 1000;
        break;

      case 'j':
        calibration_factor2 -= 1000;
        break;

      case 'k':
        calibration_factor2 += 10000;
        break;

      case 'l':
        calibration_factor2 -= 10000;
        break;
      //---------------------------------------------------------------------

      //---------------------------------------------------------------------
      // PARA CALIBRAR A TERCEIRA CELULA DE CARGA
      case 'm':
        calibration_factor3 += 100;
        break;

      case 'n':
        calibration_factor3 -= 100;
        break;

      case 'o':
        calibration_factor3 += 1000;
        break;

      case 'p':
        calibration_factor3 -= 1000;
        break;

      case 'q':
        calibration_factor3 += 10000;
        break;

      case 'r':
        calibration_factor3 -= 10000;
        break;
      //---------------------------------------------------------------------

      //---------------------------------------------------------------------
      // PARA CALIBRAR A QUARTA CELULA DE CARGA
      case 's':
        calibration_factor4 += 100;
        break;

      case 't':
        calibration_factor4 -= 100;
        break;

      case 'u':
        calibration_factor4 += 1000;
        break;

      case 'v':
        calibration_factor4 -= 1000;
        break;

      case 'w':
        calibration_factor4 += 10000;
        break;

      case 'x':
        calibration_factor4 -= 10000;
        break;
      //---------------------------------------------------------------------
    }
    
  }
}
