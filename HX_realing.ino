#include "HX711.h"

float calibration_factor = 7050; //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  1
#define CLK  2
#define BT 19   // Bouton de tare sur pin 19
#define TB 14   // Nouveau bouton sur pin 14 pour lire la valeur du capteur
HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Démarrage");

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  delay(6000);
  scale.tare(); // Assumer qu'il n'y a pas de poids sur la balance au démarrage
  pinMode(BT, INPUT_PULLUP);  // Bouton de tare
  pinMode(TB, INPUT_PULLUP);  // Nouveau bouton pour lire la valeur
  Serial.println("Mise à zéro");
}

void loop() {
  // Vérifier si le bouton de tare (BT) est pressé
  if (digitalRead(BT) == LOW) {
    scale.set_scale(calibration_factor);
    Serial.println("Tare activé pour les deux capteurs");
    scale.tare();  // Réinitialiser la balance
    delay(500);    // Petit délai pour éviter les déclenchements multiples
  }
  
  // Lire la valeur lorsque le bouton TB est pressé
  if (digitalRead(TB) == LOW) {
    Serial.print("Lecture: ");
    Serial.print(scale.get_units(), 1); // scale.get_units() renvoie un float
    Serial.print(" g"); // Affichage en grammes
    Serial.println();
    delay(500); // Délai pour éviter les déclenchements multiples
  }

  delay(100); // Boucle principale avec un petit délai
}
