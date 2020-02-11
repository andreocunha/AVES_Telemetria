#define GF 2.1f //Gage Factor
#define R 120.3f //Resistencia formula gage
#define Ref 100000 //Resistencia conhacida 

double e; //deformacao
double DR; //variacao na resistencia
double Vx; //tensao para calc resistencia

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Vx = (double)(analogRead(A0)*5.00/1024.00);
  Serial.print("VX: ");
  Serial.println(Vx, 6);
  DR = (double)((5 * Ref) / Vx) - Ref;
  Serial.print("DR: ");
  Serial.println(DR);
  e = (double)(1/GF)*(DR/R);
  Serial.println(e, 6);
  delay(500);
}
