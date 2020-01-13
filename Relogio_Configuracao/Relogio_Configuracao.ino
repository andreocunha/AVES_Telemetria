
//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>
 
//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(2, 3);
 
void setup()
{
  //Aciona o relogio
  rtc.halt(false);
   
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  //rtc.setDOW(SUNDAY);      //Define o dia da semana
  rtc.setTime(23, 0, 0);     //Define o horario
  rtc.setDate(1, 1, 2020);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
   
  Serial.begin(9600);
}
 
void loop()
{
  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.println(rtc.getDateStr(FORMAT_SHORT));
  //Serial.print(" ");
  //Serial.println(rtc.getDOWStr(FORMAT_SHORT));
   
  //Aguarda 1 segundo e repete o processo
  delay (1000);
}
