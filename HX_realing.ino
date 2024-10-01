#include "HX711.h"

float calibration_factor = 7050; //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  1
#define CLK  2
#define BT 19   // Bouton de tare sur pin 19
#define TB 14   // Nouveau bouton sur pin 14 pour lire la valeur du capteur
#define MO 7  // switch mode
#define D1 1000


HX711 scale;

int number;
char *result = (char*) malloc(8);  // Allouer de la mémoire pour 8 chiffres + \0

void removeDashes(char* str) {
  int j = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != '-') {
      str[j++] = str[i];  // Copier les caractères qui ne sont pas "-"
    }
  }
  str[j] = '\0';  // Terminer la chaîne
}

void Tare(){
   scale.set_scale(calibration_factor);
      Serial.println("Tare activé pour les deux capteurs");
      scale.tare();  // Réinitialiser la balance
      delay(500);    // Petit délai pour éviter les déclenchements multiples
}

void Real(){
  number = (int) scale.get_units();  // Convertir en int
    sprintf(result, "%07d", number);  // Formater avec 8 chiffres
    removeDashes(result); 
    Serial.println(result);  // Afficher le résultat formaté
    delay(D1); // Délai pour éviter les déclenchements multiples
}

void setup() {
  Serial.begin(9600);
  Serial.println("demarrage");

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  delay(6000);
  scale.tare(); // Assumer qu'il n'y a pas de poids sur la balance au démarrage
  pinMode(BT, INPUT_PULLUP);  // Bouton de tare
  pinMode(TB, INPUT_PULLUP);  // Nouveau bouton pour lire la valeur
  pinMode(MO, INPUT_PULLUP);  // switch mode
  Serial.println("mise a zero");
}
//ajouter un siwch pour avoir un mode continue et mode commande.
//ajouter un commande lecture et tare.
void loop() {
  // Vérifier si le bouton de tare (BT) est pressé
  while (Serial.available() == 0) {
    if (digitalRead(BT) == LOW) {
     Tare();
    }
  
  if (digitalRead(TB) == LOW||digitalRead(MO) == LOW){
    Real();
  }

  delay(100); // Boucle principale avec un petit délai
}
  String serialcontrol = Serial.readString();
  serialcontrol.trim();
  if (serialcontrol == "tare"){
    Tare();
  } else {
    Real();
  }
}
