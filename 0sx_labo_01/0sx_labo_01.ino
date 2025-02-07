const int ledPin = 13;       //Initialise la position de la LED à 13
const int blinkDelay = 250;  //Met le délais du clignottement à 250ms
const int fadeDelay = 9;     //Met le délais de la variation à 9ms

enum Etat { ALLUME, CLIGNOTEMENT, VARIATION, ETEINT };
Etat etatActuel = ALLUME;

void setup() {
  pinMode(ledPin, OUTPUT);     //Informe la LED quelle est un Output
  Serial.begin(9600);          //Fréquence
  digitalWrite(ledPin, HIGH);  //Met l'état de la LED en high
}

void loop() {
  allume();  //Fonction qui allume la LED

  clignotement();  //Fonction qui fait clignoter la LED

  variation();  //Fonction qui fait varier l'intensité de la LED

  eteint();  //Fonction qui eteint la LED
}

void changerEtat(Etat nouvelEtat) {
  etatActuel = nouvelEtat; //Change l'état actuel en un nouvel état
  envoyerMessageEtat();
}

void envoyerMessageEtat() {
  switch (etatActuel) {
    case ALLUME:
      Serial.println("Allumé - 6291623");  //Affiche l'état et le numéro de DA
      break;

    case CLIGNOTEMENT:
      Serial.println("Clignotement - 6291623");  //Affiche l'état et le numéro de DA
      break;

    case VARIATION:
      Serial.println("Variation - 6291623");  //Affiche l'état et le numéro de DA
      break;

    case ETEINT:
      Serial.println("Éteint - 6291623");  //Affiche l'état et le numéro de DA
      break;
  }
}

//Finis
void allume() {
  digitalWrite(ledPin, HIGH);  //Allume la LED
  delay(2000);                 //Délais de 2 secondes
  changerEtat(CLIGNOTEMENT);   //Change l'état de la LED à Clignotement
}

//Finis ?
void clignotement() {
  for (int i = 0; i < 2; ++i) {  //Va repeter la boucle 3 fois avant d'arrêter
    digitalWrite(ledPin, HIGH);  //Allume la led
    delay(blinkDelay);           //Delais de 500ms
    digitalWrite(ledPin, LOW);   //Eteind la led
    delay(blinkDelay);           //Délais de 500ms
  }
  changerEtat(VARIATION);  //Change l'état de la LED à Variation
}

//Finis ?
void variation() {
  for (int i = 255; i >= 0; i -= 5) {  //Boucle qui réduit l'intensité de la LED
    analogWrite(ledPin, i);            //intensité de la LED
    delay(fadeDelay);                  //Délais de 500ms
  }
  changerEtat(ETEINT);  //Change l'état de la LED à Éteint
}

//Finis
void eteint() {
  digitalWrite(ledPin, LOW);  //Éteint la LED
  delay(2000);                //Applique un délai de 2 secondes
  changerEtat(ALLUME);        //Change l'état de la LED à Allumé
}