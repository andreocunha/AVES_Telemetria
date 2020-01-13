#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(2, 3); // RX, TX
TinyGPS gps1;

//--------------------------------------------------------------
//Cartao micro SD
#include <SD.h>
#include <SPI.h>

File myFile;
int pinoSS = 10; // Pin 53 para Mega / Pin 10 para UNO

//---------------------------------------------------------------

#define ledVerde 4
#define ledVermelho 5
#define arduino2 9

void setup() {
   serial1.begin(9600);
   Serial.begin(9600);

   pinMode(ledVerde, OUTPUT);
   pinMode(ledVermelho, OUTPUT);
   pinMode(arduino2, OUTPUT);

   digitalWrite(ledVerde, LOW);
   digitalWrite(ledVermelho, LOW);
   digitalWrite(arduino2, LOW);

   Serial.println("Buscando pelo sinal dos satelites...");
   Serial.println();
   Serial.println();

   //--------------------------------------------------------------------
   //cartao micro SD

    pinMode(pinoSS, OUTPUT); // Declara pinoSS como saída
     
    if (SD.begin()) { // Inicializa o SD Card
    Serial.println("SD Card pronto para uso."); // Imprime na tela
    }
     
    else {
    Serial.println("Falha na inicialização do SD Card.");
    digitalWrite(ledVermelho, HIGH);
    while(1);
    }
     
    myFile = SD.open("AVES1.csv", FILE_WRITE); // Cria / Abre arquivo .csv
     
    if (myFile) { // Se o Arquivo abrir imprime:
      
       Serial.print(F("Latitude;"));
       Serial.print(F("Longitude;"));
       Serial.print(F("Idade da Informacao (ms);"));
       Serial.print(F("Data (GMT);"));
       Serial.print(F("Horario (GMT);"));
       Serial.print(F("Velocidade (km/h);"));
       Serial.println(F("Sentido (grau)"));

       myFile.print("Latitude;");
       myFile.print("Longitude;");
       myFile.print("Idade da Informacao (ms);");
       myFile.print("Data (GMT);");
       myFile.print("Horario (GMT);");
       myFile.print("Velocidade (km/h);");
       myFile.println("Sentido (grau)");

       myFile.close(); // Fecha o Arquivo após escrever

    }
     
    else {     // Se o Arquivo não abrir
    Serial.println("Erro ao Abrir Arquivo .csv"); // Imprime na tela
    digitalWrite(ledVermelho, HIGH);
    }
    
     



    //--------------------------------------------------------------------
   
}

int i = 0;

void loop() {
  
  bool recebido = false;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = (gps1.encode(cIn) || recebido);  //Verifica até receber o primeiro sinal dos satelites
  }


  if ( (recebido) ) {  //Mostra apenas após receber o primeiro sinal

    while (i == 0){
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);
      digitalWrite(arduino2, HIGH);
      i++;
    }
    

    myFile = SD.open("AVES1.csv", FILE_WRITE); // Cria / Abre arquivo .csv
    
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);  
     
     //Latitude e Longitude
     //long latitude, longitude; 
     float latitude, longitude; //As variaveis podem ser float, para não precisar fazer nenhum cálculo
     
     unsigned long idadeInfo;
     gps1.f_get_position(&latitude, &longitude, &idadeInfo);   //O método f_get_position é mais indicado para retornar as coordenadas em variáveis float, para não precisar fazer nenhum cálculo    


     
     if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        myFile.print(latitude, 6);  //Mostra a latitude com a precisão de 6 dígitos decimais
        myFile.print(";");
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        myFile.print(longitude, 6);  //Mostra a longitude com a precisão de 6 dígitos decimais
        myFile.print(";");
     }

     if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
        myFile.print(idadeInfo);
        myFile.print(";");
     }


     //Dia e Hora
     int ano;
     byte mes, dia, hora, minuto, segundo, centesimo;
     gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);

     myFile.print("'");
     myFile.print(dia);
     myFile.print("/");
     myFile.print(mes);
     myFile.print("/");
     myFile.print(ano);
     myFile.print("'");
     myFile.print(";");


     myFile.print("'");
     myFile.print(hora);
     myFile.print(":");
     myFile.print(minuto);
     myFile.print(":");
     myFile.print(segundo);
     myFile.print(":");
     myFile.print(centesimo);
     myFile.print("'");
     myFile.print(";");


     //altitude
     float altitudeGPS;
     altitudeGPS = gps1.f_altitude();

     if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
        myFile.print("Altitude (cm): ");
        myFile.println(altitudeGPS);
        myFile.print(";");
     }


     //velocidade
     float velocidade;
     //velocidade = gps1.speed();        //nós
     velocidade = gps1.f_speed_kmph();   //km/h
     //velocidade = gps1.f_speed_mph();  //milha/h
     //velocidade = gps1.f_speed_mps();  //milha/segundo

     
     myFile.print(velocidade, 2);  //Conversão de Nós para Km/h
     myFile.print(";");

    

     //sentito (em centesima de graus)
     unsigned long sentido;
     sentido = gps1.course();

     myFile.println(float(sentido) / 100, 2);

     myFile.close(); // Fecha o Arquivo após escrever

     digitalWrite(arduino2, LOW);

  }
}
