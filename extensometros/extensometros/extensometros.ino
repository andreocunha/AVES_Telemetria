#define GF 2.1f //Gage Factor
#define R 120.3f //Resistencia formula gage

double e; //deformacao
double DR; //variacao na resistencia
double Vx;
double Vr;

void setup() {
  Serial.begin(9600);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);

}

void loop() {
  Vx = (double)((analogRead(A4)- analogRead(A3))*5.00/1024.00);
  Vr = (double)(analogRead(A4)*5.00/1024.00);
  DR = (double)((5 * Ref) / Vr) - Ref;
  Serial.print("VX: ");
  Serial.println(Vx, 6);

  
  
  Serial.println();
  delay(250);
}
