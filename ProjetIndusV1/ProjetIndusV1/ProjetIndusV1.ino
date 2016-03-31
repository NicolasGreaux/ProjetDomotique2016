// IUT de Nice Cote d'Azur
// LP AII année 2015-2016
// Auteur : Gréaux Nicolas

//Code pour le projet Industriel : Arrosage automatique



#include "LiquidCrystal.h" //ajout de la librairie

#define HUMIDITE_MIN 250  // Seuil a partir de lequel la pompe se met en route
#define HUMIDITE_MAX 750  // Seuil d'arret de la pompe

//Variables
int MisirValue = 0; // Variable du Misir
int h1 = 0;      // Variable d'humidité du capteur 1
int h2 = 0;      // Variable d'humidité du capteur 2
int H = 0;       // Moyenne des deux capteurs d'humidité
String moteur = "Eteint";

//Pin
int PinMisir = A0;  //Pin Out du capteur Co2 Misir
int PinH1 = A1;   // Pin Out du capteur d'humidité 1
int PinH2 = A2;   // Pin Out du capteur d'humidité 2
int PinM = 0;    // Pin de commande du moteur de la pompe

LiquidCrystal lcd(11,10,5,4,3,2); //liaison 4 bits de données

void setup() {
  
  //Initialisation du LCD
   lcd.begin(16,2); //utilisation d'un écran 16 colonnes et 2 lignes
   lcd.write("Salut la LP AII!"); //petit test pour vérifier que tout marche
}

void loop() {
  MisirValue = analogRead(PinMisir);
  h1 = analogRead(PinH1);
  h2 = analogRead(PinH2);
  H = (h1 + h2) / 2;
  
  if (H > HUMIDITE_MAX)
  {
    digitalWrite(PinM,LOW);
    moteur = "Eteint";
  }
  else if (H < HUMIDITE_MIN)
  {
    digitalWrite(PinM,HIGH);
    moteur = "Allumé";
  }

  Serial.print(MisirValue);

  // met le curseur sur la colonne 0, ligne 0
  // (note: ligne 1 est la seconde ligne, car on compte a partir de 0):
  lcd.setCursor(0, 0);
  // Affichage de la premiere partie du message
  lcd.print("Statut pompe:");
  
  lcd.setCursor(0, 1);
  // Affichage du capteur d'humidité:
  lcd.print(moteur);

  delay(1000);

  lcd.setCursor(0, 0);
  // Affichage de la premiere partie du message
  lcd.print("Valeur Misir:");
  
  lcd.setCursor(0, 1);
  // Affichage du capteur d'humidité:
  lcd.print(MisirValue);

  delay(1000);
}


