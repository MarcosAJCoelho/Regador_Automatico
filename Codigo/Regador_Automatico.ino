
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define UMIDADE_A A0
#define UMIDADE_D 8
#define CHUVA_A A1
#define CHUVA_D 9
#define RELE 5

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(UMIDADE_D, INPUT);
  pinMode(CHUVA_D, INPUT);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);
  dht.begin();
}
 
void loop() {
  delay(20000);
  float umidade_ar = dht.readHumidity();
  float temperatura = dht.readTemperature();
  float umidade_solo_a = analogRead(UMIDADE_A);
  float chuva_a = analogRead(CHUVA_A);
  boolean umidade_solo_d = digitalRead(UMIDADE_D);
  boolean chuva_d = digitalRead(CHUVA_D);
  umidade_solo_a =  100 - ((100 * umidade_solo_a) / 1023);
  chuva_a = 100 - ((100 * chuva_a) / 1023);
  Serial.print("Umidade do Ar: ");
  Serial.print(umidade_ar);
  Serial.println(" %");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" ºC");
  Serial.print("Umidade do Solo: ");
  Serial.print(umidade_solo_a);
  Serial.println(" %");
  Serial.print("Chuva: ");
  Serial.print(chuva_a);
  Serial.println(" %");

  
  if (temperatura > 25) {
    if ((chuva_d) && (umidade_ar <= 80) && (umidade_solo_a <= 70 )) {
      digitalWrite(RELE, LOW );
      Serial.println("Ligado");
    }
    else {
      digitalWrite(RELE, HIGH);
      Serial.println("Desligado");
    }
  }
  else {
    if ((chuva_d) && (umidade_ar <= 60) && (umidade_solo_a <= 40 )) {
      digitalWrite(RELE, LOW);
      Serial.println("Ligado");
    }
    else {
      digitalWrite(RELE, HIGH);
      Serial.println("Desligado");
    }
  }
}
