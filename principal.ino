#include <Servo.h>

Servo myservo;

int ECHO1 = 26; //Pin Echo del sensor lateral Izq.

int ECHO2 = 23; //Pin Echo del sensor frontal

int ECHO3 = 24; //Pin Echo del sensor lateral der.

int TRIG1 = 27; //Pin Trigger del sensor lateral izq.

int TRIG2 = 22; //Pin Trigger del sensor frontal

int TRIG3 = 25; //Pin Trigger del sensor lateral der.

int M1P = 10;
int M1N = 11;

int M2P = 12;
int M2N = 13;

int ENA = 8;

int ENB = 9;

int ver1 = 1;


void setup(){
  
  Serial.begin(9600);

  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(ECHO3, INPUT);
  
  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(TRIG3, OUTPUT);
  
  pinMode(M1P, OUTPUT);
  pinMode(M1N, OUTPUT);
  
  pinMode(M2P, OUTPUT);
  pinMode(M2N, OUTPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  myservo.attach(2);

}

int distanciaFrontal(){

  digitalWrite(TRIG2, LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  
  int duracionFront = pulseIn(ECHO2, HIGH);
  int distanciaFront = duracionFront * 0.034 / 2;

  
  return distanciaFront;
}

int distanciaLateralDer(){

  digitalWrite(TRIG1, LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  
  int duracionLatD = pulseIn(ECHO1, HIGH);
  int distanciaLatD = duracionLatD * 0.034 / 2;

  return distanciaLatD;
}

int distanciaLateralIzq(){

  digitalWrite(TRIG3, LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3, LOW);
  
  int duracionLatI = pulseIn(ECHO3, HIGH);
  int distanciaLatI = duracionLatI * 0.034 / 2;
  
  return distanciaLatI;
  
}

int giroAntihorario(int AF, int AD, int AI) {

    
  //===================================================================
  
  if (AF <= 20) {
    myservo.write(15);
    
    if (AD <= 15) {
     myservo.write(72);
    }
    
    if (AI <= 15) {
      myservo.write(15);
    }
  } else {
    myservo.write(42);
  }  
  
  //===================================================================
  
  if (AD <= 15) {
     myservo.write(72);
    
    if (AI <= 15) {
      myservo.write(15);
    }
    
  }
    
  //===================================================================
    
  if (AI <= 15) {
      myservo.write(15);
      
      if (AD <= 15) {
     myservo.write(72);
    }
      
  }
  
  //===================================================================

}

int giroHorario(int BF, int BD, int BI) {

    
  //===================================================================
  
  if (BF <= 20) {
    myservo.write(72);
    
    if (BD <= 15) {
     myservo.write(72);
    }
    
    if (BI <= 15) {
      myservo.write(15);
    }
  } else {
    myservo.write(42);
  }  
  
  //===================================================================
  
  if (BD <= 15) {
      myservo.write(72);
      
      if (BI <= 15) {
     myservo.write(15);
     }
      
  }
    
  //===================================================================
    
  if (BI <= 15) {
      myservo.write(15);
      
      if (BD <= 15) {
     myservo.write(72);
     }
      
  }
  
  //===================================================================
}

int avanzar() {

  digitalWrite(M1P, HIGH);
  digitalWrite(M1N, LOW);
  digitalWrite(M2P, LOW);
  digitalWrite(M2N, HIGH);
  
  analogWrite(ENA, 90);
  analogWrite(ENB, 90);

}

void loop(){
  
  int dist_Front = distanciaFrontal();
  int dist_Lat_D = distanciaLateralDer();
  int dist_Lat_I = distanciaLateralIzq();
  
  avanzar();
    
  giroAntihorario (dist_Front, dist_Lat_D, dist_Lat_I);
  
  
  Serial.print("Distancia Frontal = ");
  Serial.print(dist_Front);
  Serial.println(" cm");
  
  Serial.print("Distancia Later D = ");
  Serial.print(dist_Lat_D);
  Serial.println(" cm");
  
  Serial.print("Distancia Later I = ");
  Serial.print(dist_Lat_I);
  Serial.println(" cm");
  
  Serial.println(" ");
   
  delay(400);

}
