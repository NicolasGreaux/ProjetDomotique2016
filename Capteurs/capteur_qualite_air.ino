#include <Wire.h>

char tabValeur[6];
int resultat = 0;
int j = 0;

void setup() {
  // put your setup code here, to run once:
Wire.begin();
Serial.begin(9600);
Wire.beginTransmission(0x70);
Wire.write(9);
Wire.endTransmission();
}


void loop() {
  // put your main code here, to run repeatedly:
j = 0;
Wire.requestFrom(0x70, 6);
while(Wire.available())
{
int i = Wire.read();
Serial.println(i);
tabValeur[j] = i;
j++;
}
Serial.println("----------");
delay(1000);
valeurCapteur(tabValeur);
}

void valeurCapteur(char *tabValeurs)
{
resultat = (tabValeurs[0] - 13)*(1600/229) + 400;
Serial.println(resultat);
Serial.println("----------");
}

