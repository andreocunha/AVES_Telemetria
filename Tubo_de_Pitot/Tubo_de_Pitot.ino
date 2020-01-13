#include <Wire.h>

// ---Tubo de Pitot----------------------------------------------
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#endif
#define PITOT_ADRESS 0x28 // O endereço do Pitot na rede I²C (0x36 or 0x46)
#define PITOT_RANGE 10.0

uint8_t pitotRead[5]; // Vetor de 5 bytes que recebe os valores do Pitot
uint8_t pitotStatus = 0;
uint16_t rawPressure = 0;       // Valor inteiro cru da pressão do pitot
uint16_t rawTemperature = 0;    // Valor inteiro cru da temperatura do pitot

float pressure;
float temperature;
float velocity;
const float rho = 1.2251; // A constante do ar lá


void setup() {
  Serial.begin(9600);
 //-----------------Setup Pitot
  char i;
  // Inicializa o mestre(o arduino) I²C com uma das bibliotecas disponíveis
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000);
  Serial.println("Transmissao OK");
  delay(300);
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  delay(300);

  //------------- Inicializa o Pitot
  Wire.requestFrom(PITOT_ADRESS, 4);    // request 4 bytes

  delay(300);
  
  pitotStatus = pitotRead[0] >> 6; // Pega os 2 bits mais significativos que representam o status do Pitot
  // Ele serve pro Pitot falar se está "tudo jóia" com ele
  // Leia o datasheet do sensor para mais informações
  if (pitotStatus == 3) { // Se o código entrar aqui, deu ruim fí
    Serial.println("Deu ruim fi");
    return; // Isso aqui é pra evitar que continue. O código nem roda
  }
}

void loop() {
//*****************Tubo de Pitot***********************************
  readPitot();
  rawPressure = (pitotRead[0] & 0x3F) << 8;
  rawPressure |= pitotRead[1];
  // Coisa semelhante é feita pra temperatura. Figure it out.
  rawTemperature = pitotRead[2] << 3;
  rawTemperature |= pitotRead[3] >> 5;
  // Aplica a conversão do valor cru para celsius usando a função dada pelo datasheet do sensor.
  temperature = 0.0977 * (rawTemperature - 511);
  
//******************PLOT DE DADOS PITOT*****************************
  //Serial.print("Pitot: ");
  Serial.print(rawPressure);
  Serial.print(" | ");
   //Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" | ");
 
}


void readPitot() {
  int i = 0;
  Wire.requestFrom(PITOT_ADRESS, 4);    // Pede 4 bytes pro Pitot
  while (Wire.available()) { // Espera a linha i²c ficar livre
    pitotRead[i] = Wire.read();
    i++;
  }

}
