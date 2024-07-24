const int ledPin = 13; // Pripojte LED na pin 13 (na doskách s integrovanou LED)

void setup() {
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);
  // Inicializácia LED pinu ako výstup
  pinMode(ledPin, OUTPUT);
  // Uistite sa, že LED je vypnutá pri štarte
  digitalWrite(ledPin, HIGH); // Zapnúť LED
  delay(3000);
  digitalWrite(ledPin, LOW);
  
}

void loop() {
  // Skontrolujte, či sú k dispozícii dáta zo sériovej linky
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    Serial.print("Command:");
    Serial.println(command);
    command.trim();
    Serial.println("");


    if (command == "LEDON") {
      digitalWrite(ledPin, HIGH); // Zapnúť LED
    } else if (command == "LEDOFF") {
      digitalWrite(ledPin, LOW); // Vypnúť LED
    }
  }
}
