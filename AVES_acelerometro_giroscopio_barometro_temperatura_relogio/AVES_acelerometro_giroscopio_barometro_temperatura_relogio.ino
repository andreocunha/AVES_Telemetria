//Carrega a biblioteca Wire
#include<Wire.h>
#include <Adafruit_BMP085.h> //INCLUSÃO DE BIBLIOTECA DO BAROMETRO
 
Adafruit_BMP085 bmp; //OBJETO DO TIPO Adafruit_BMP085 (I2C)

#define ledVerde 5
#define ledVermelho 4
#define start 9
 
//Endereco I2C do MPU6050
const int MPU=0x68;  

//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

//-------------------------------------------------------------------------------------
// Cartao micro SD
#include <SD.h>
#include <SPI.h>
 
File myFile;
 
int pinoSS = 10; // Pin 53 para Mega / Pin 10 para UNO e NANO

//-------------------------------------------------------------------------------------
//Relogio

//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>
 
//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(2, 3); //SDA e SCL

//---------------------------------------------------------------------------------------

void setup()
{
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(start, INPUT);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, LOW);

  if (!bmp.begin()){ //SE O SENSOR BAROMETRO NÃO FOR INICIALIZADO, FAZ
  Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões."); //IMPRIME O TEXTO NO MONITOR SERIAL
  digitalWrite(ledVermelho, HIGH);
  while(1){} //SEMPRE ENTRE NO LOOP
  }
  
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
  
  delay(350);

//-----------------------------------------------------------------------
//Cartao micro SD
  pinMode(pinoSS, OUTPUT); // Declara pinoSS como saída
 
  if (SD.begin()) { // Inicializa o SD Card
    Serial.println("SD Card pronto para uso."); // Imprime na tela
  }
   
  else {
    Serial.println("Falha na inicialização do SD Card.");
    digitalWrite(ledVermelho, HIGH);
    while(1){}
  }

//------------------------------------------------------------------------
// Setup do Relogio

//Aciona o relogio
  rtc.halt(false);
   
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  //rtc.setDOW(SUNDAY);      //Define o dia da semana
  //rtc.setTime(16, 47, 0);     //Define o horario
  //rtc.setDate(10, 1, 2020);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);

//--------------------------------------------------------------------------

}

int i = 0;

void loop()
{
  if(digitalRead (start)  == HIGH){

    
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);

    myFile = SD.open("AVES.csv", FILE_WRITE); // Cria / Abre arquivo .csv

    //---------------------------------------------------------------------------------
    //Gravando os dados no cartao
    if (myFile) {

      while(1){
        myFile = SD.open("AVES.csv", FILE_WRITE); // Cria / Abre arquivo .csv

        while(i == 0){             
          Serial.print("Hora;");
          Serial.print("Data;");  
          Serial.print("Acel. X;");
          Serial.print("Acel. Y;");
          Serial.print("Acel. Z;");
          Serial.print("Gir. X;");
          Serial.print("Gir. Y;");
          Serial.print("Gir. Z;");
          Serial.print("Temp 1;");
          Serial.print("Temp 2;");
          Serial.print("Pressao (PA);");
          Serial.print("Altitude (m);");
          Serial.print("Pressão a nível do mar (PA);");
          Serial.println("Altitude real (m)");
      
          Serial.println("Escrevendo no Arquivo .csv"); // Imprime na tela
          myFile.print("Hora;");
          myFile.print("Data;");  
          myFile.print("Acel. X;");
          myFile.print("Acel. Y;");
          myFile.print("Acel. Z;");
          myFile.print("Gir. X;");
          myFile.print("Gir. Y;");
          myFile.print("Gir. Z;");
          myFile.print("Temp 1;");
          myFile.print("Temp 2;");
          myFile.print("Pressao (PA);");
          myFile.print("Altitude (m);");
          myFile.print("Pressão a nível do mar (PA);");
          myFile.println("Altitude real (m)");

          i++;

        }
        
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H) 
        Wire.endTransmission(false);
    
        //Solicita os dados do sensor
        Wire.requestFrom(MPU,14,true);  
    
        //Armazena o valor dos sensores nas variaveis correspondentes
        AcX=Wire.read()<<8|Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
        AcY=Wire.read()<<8|Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ=Wire.read()<<8|Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        Tmp=Wire.read()<<8|Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        GyX=Wire.read()<<8|Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyY=Wire.read()<<8|Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyZ=Wire.read()<<8|Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
      
         
        //Mostra os valores do acelerometro, giroscopio e barometro no monitor serial
        Serial.print(rtc.getTimeStr()); //horas
        Serial.print(";");
        Serial.print(rtc.getDateStr(FORMAT_SHORT)); //data
        Serial.print(";");
        Serial.print(AcX);
        Serial.print(";");
        Serial.print(AcY);
        Serial.print(";");
        Serial.print(AcZ);
        Serial.print(";");
        Serial.print(GyX);
        Serial.print(";");
        Serial.print(GyY);
        Serial.print(";");
        Serial.print(GyZ);
        Serial.print(";");
        Serial.print(Tmp/340.00+36.53);
        Serial.print(";");
        Serial.print(bmp.readTemperature()); //IMPRIME NO MONITOR SERIAL A TEMPERATURA
        Serial.print(";");      
        Serial.print(bmp.readPressure()); //IMPRIME NO MONITOR SERIAL A PRESSÃO
        Serial.print(";");     
        Serial.print(bmp.readAltitude()); //IMPRIME NO MONITOR SERIAL A ALTITUDE APROXIMADA
        Serial.print(";");    
        Serial.print(bmp.readSealevelPressure()); //IMPRIME NO MONITOR SERIAL A PRESSÃO A NÍVEL DO MAR
        Serial.print(";");
        Serial.println(bmp.readAltitude(101500)); //IMPRIME NO MONITOR SERIAL A ALTITUDE REAL
  
        //------------------------------------------------------------------------------------------------------
        //gravando no cartao micro sd
        myFile.print(rtc.getTimeStr()); //horas
        myFile.print(";");
        myFile.print(rtc.getDateStr(FORMAT_SHORT)); //data
        myFile.print(";");
        myFile.print(AcX);
        myFile.print(";");
        myFile.print(AcY);
        myFile.print(";");
        myFile.print(AcZ);
        myFile.print(";");
        myFile.print(GyX);
        myFile.print(";");
        myFile.print(GyY);
        myFile.print(";");
        myFile.print(GyZ);
        myFile.print(";");
        myFile.print(Tmp/340.00+36.53);
        myFile.print(";");
        myFile.print(bmp.readTemperature()); //IMPRIME NO MONITOR myFile A TEMPERATURA
        myFile.print(";");      
        myFile.print(bmp.readPressure()); //IMPRIME NO MONITOR myFile A PRESSÃO
        myFile.print(";");     
        myFile.print(bmp.readAltitude()); //IMPRIME NO MONITOR myFile A ALTITUDE APROXIMADA
        myFile.print(";");    
        myFile.print(bmp.readSealevelPressure()); //IMPRIME NO MONITOR myFile A PRESSÃO A NÍVEL DO MAR
        myFile.print(";");
        myFile.println(bmp.readAltitude(101500)); //IMPRIME NO MONITOR SERIAL A ALTITUDE REAL

        myFile.close(); // Fecha o Arquivo após escrever
        Serial.println("Terminado."); // Imprime na tela
        Serial.println(" ");
  
        //-----------------------------------------------------------------------------------------------------------
  
      }
    }
   
  }

}
