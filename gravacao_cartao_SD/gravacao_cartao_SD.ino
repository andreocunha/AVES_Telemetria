#include <SD.h>
#include <SPI.h>

 
File myFile;
 
int pinoSS = 10; // Pin 53 para Mega / Pin 10 para UNO
 
void setup() { // Executado uma vez quando ligado o Arduino


Serial.begin(9600); // Define BaundRate
pinMode(pinoSS, OUTPUT); // Declara pinoSS como saída

delay(500);
 
if (SD.begin()) { // Inicializa o SD Card
Serial.println("SD Card pronto para uso."); // Imprime na tela
}
 
else {
Serial.println("Falha na inicialização do SD Card.");
return;
}
 
myFile = SD.open("AVES.csv", FILE_WRITE); // Cria / Abre arquivo .csv
 
if (myFile) { // Se o Arquivo abrir imprime:
Serial.println("Escrevendo no Arquivo .csv"); // Imprime na tela
myFile.print("teste1"); // Escreve no Arquivo
myFile.print(";"); // Escreve no Arquivo
myFile.print("teste2"); // Escreve no Arquivo
myFile.print(";"); // Escreve no Arquivo
myFile.println("teste3"); // Escreve no Arquivo
myFile.print("teste4"); // Escreve no Arquivo
myFile.print(";"); // Escreve no Arquivo
myFile.print("teste5"); // Escreve no Arquivo
myFile.print(";"); // Escreve no Arquivo
myFile.println("teste6"); // Escreve no Arquivo
myFile.close(); // Fecha o Arquivo após escrever
Serial.println("Terminado."); // Imprime na tela
Serial.println(" ");
}
 
else {     // Se o Arquivo não abrir
Serial.println("Erro ao Abrir Arquivo .csv"); // Imprime na tela
}

 
}
 
void loop() {
 
// Como a função é executada somente uma vez, esta área permanece em branco
 
}
