#include <ESP8266WiFi.h>
#include <Wire.h>

//Remplacer par la clé API thingspeak de votre channel
String apiKey = "*******************";
const char* ssid = "********************";
const char* password = "********************";

const char* server = "api.thingspeak.com";

float resultatMisir;
float valeurMisir;
int misir;

float resultatVZ;
float valeurVZ;
int VZ;

int cpt = 0;
int tabValeur[6];

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Wire.begin();//I2C
  delay(10);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
//Connexion WIFI
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
//////////////////////////////////
}

void loop() {
  
  while (cpt < 30)
  {
   //Récupération valeur capteur MISIR
    valeurMisir = analogRead(A0);
    resultatMisir = resultatMisir + valeurMisir;
    Serial.println(resultatMisir);
  ////////////////////////////////////

  //Récupération valeur capteur VZ
    int j = 0;
    Wire.beginTransmission(0x70);
    Wire.write(9);
    Wire.endTransmission();
    Wire.requestFrom(0x70, 6);
    while (Wire.available())
    {
      int i = Wire.read();
      tabValeur[j] = i;
      j++;
    }
    valeurVZ = (tabValeur[0] - 13) * (1600 / 229) + 400;
    resultatVZ = resultatVZ + valeurVZ;
    Serial.println(resultatVZ);
  /////////////////////////////////////
    cpt++;
    Serial.println(cpt);
    
    delay(1000);
    return;
  }

  VZ = resultatVZ / 30;
  Serial.println(VZ);
  
  misir = resultatMisir / 30;
  Serial.println(misir);
  
//Envoie des données au serveur toute les 30 secondes
  if (client.connect(server, 80)) { // "184.106.153.149" ou api.thingspeak.com
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(VZ);
    postStr += "&field2=";
    postStr += String(misir);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println("OK");
  }
  client.stop();

  Serial.println("Waiting…");
  //Thingspeak à besoin de minimum 15s de delais entre chaque updates
  delay(20000);
/////////////////////////////////////
  misir = 0;
  resultatMisir = 0;

  VZ = 0;
  resultatVZ = 0;
  
  cpt = 0;

}







