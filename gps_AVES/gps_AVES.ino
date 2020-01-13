#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(2, 3); // RX, TX
TinyGPS gps1;

#define ledVerde 5
#define ledVermelho 6

void setup() {
   serial1.begin(9600);
   Serial.begin(9600);

   pinMode(ledVerde, OUTPUT);
   pinMode(ledVermelho, OUTPUT);

   digitalWrite(ledVerde, LOW);
   digitalWrite(ledVermelho, HIGH);

   Serial.println("Buscando pelo sinal dos satelites...");
   Serial.println();
   Serial.println();

   
   Serial.print("Latitude");
   Serial.print("\t");
   Serial.print("Longitude");
   Serial.print("\t");
   Serial.print("Idade da Informacao (ms): ");
   Serial.print("\t");
   Serial.print("Data (GMT): ");
   Serial.print("\t");
   Serial.print("Horario (GMT): ");
   Serial.print("\t");
   Serial.print("Velocidade (km/h): ");
   Serial.print("\t");
   Serial.println("Sentido (grau): ");
   
}

void loop() {
  
  bool recebido = false;
  //static unsigned long delayPrint;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = (gps1.encode(cIn) || recebido);  //Verifica até receber o primeiro sinal dos satelites
  }


  if ( (recebido) /*&& ((millis() - delayPrint) > 30)*/ ) {  //Mostra apenas após receber o primeiro sinal. Após o primeiro sinal, mostra a cada segundo.
     //delayPrint = millis();
     
     
     //Latitude e Longitude
     //long latitude, longitude; 
     float latitude, longitude; //As variaveis podem ser float, para não precisar fazer nenhum cálculo
     
     unsigned long idadeInfo;
     gps1.f_get_position(&latitude, &longitude, &idadeInfo);   //O método f_get_position é mais indicado para retornar as coordenadas em variáveis float, para não precisar fazer nenhum cálculo    


     
     if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print(latitude, 6);  //Mostra a latitude com a precisão de 6 dígitos decimais
        Serial.print("\t");
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print(longitude, 6);  //Mostra a longitude com a precisão de 6 dígitos decimais
        Serial.print("\t");
     }

     if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
        Serial.print(idadeInfo);
        Serial.print("\t");
     }


     //Dia e Hora
     int ano;
     byte mes, dia, hora, minuto, segundo, centesimo;
     gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);

     Serial.print("'");
     Serial.print(dia);
     Serial.print("/");
     Serial.print(mes);
     Serial.print("/");
     Serial.print(ano);
     Serial.print("'");
     Serial.print("\t");


     Serial.print("'");
     Serial.print(hora);
     Serial.print(":");
     Serial.print(minuto);
     Serial.print(":");
     Serial.print(segundo);
     Serial.print(":");
     Serial.print(centesimo);
     Serial.print("'");
     Serial.print("\t");


     //altitude
     float altitudeGPS;
     altitudeGPS = gps1.f_altitude();

     if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
        Serial.print("Altitude (cm): ");
        Serial.println(altitudeGPS);
        Serial.print("\t");
     }


     //velocidade
     float velocidade;
     //velocidade = gps1.speed();        //nós
     velocidade = gps1.f_speed_kmph();   //km/h
     //velocidade = gps1.f_speed_mph();  //milha/h
     //velocidade = gps1.f_speed_mps();  //milha/segundo

     
     Serial.print(velocidade, 2);  //Conversão de Nós para Km/h
     Serial.print("\t");

    

     //sentito (em centesima de graus)
     unsigned long sentido;
     sentido = gps1.course();

     Serial.print(float(sentido) / 100, 2);
     Serial.println("\t");


     //satelites e precisão
     unsigned short satelites;
     unsigned long precisao;
     satelites = gps1.satellites();
     precisao =  gps1.hdop();

     if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
        Serial.print("Satelites: ");
        Serial.print(satelites);
        Serial.print("\t");
     }

     if (precisao != TinyGPS::GPS_INVALID_HDOP) {
        Serial.print("Precisao (centesimos de segundo): ");
        Serial.println(precisao);
     }


     //float distancia_entre;
     //distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);

     //float sentido_para;
     //sentido_para = gps1.course_to(lat1, long1, lat2, long2);
  }
}
