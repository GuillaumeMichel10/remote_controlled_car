#define capteur 5

void setup() {
    pinMode(capteur, INPUT);
    Serial.begin(9600);
}

void loop() {
    if (digitalRead(capteur))
        Serial.println("Noire");
    else
        Serial.println("blanc");

    delay (100);
}
