/*
** EPITECH PROJECT, 2022
** Arduino
** File description:
** ProjetPerso
*/

Servo Rservo;
Servo Lservo;
SoftwareSerial mySerial(rxPin, txPin);

const byte FrontTRIGGER_PIN = 4; // Broche TRIGGER
const byte FrontECHO_PIN = 5;    // Broche ECHO

const byte RearTRIGGER_PIN = 8; // Broche TRIGGER
const byte RearECHO_PIN = 9;    // Broche ECHO

const unsigned long MEASURE_TIMEOUT = 25000UL;

const float SOUND_SPEED = 340.0 / 1000;

int min = 0;
int max = 180;

char input = '\0';

void setup() // like initialize game
{

    pinMode(FrontTRIGGER_PIN, OUTPUT);
    digitalWrite(FrontTRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(FrontECHO_PIN, INPUT);

    pinMode(RearTRIGGER_PIN, OUTPUT);
    digitalWrite(RearTRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(RearECHO_PIN, INPUT);

    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    Rservo.attach(RservoPin, min, max);
    Lservo.attach(LservoPin, min, max);
    mySerial.begin(9600);
    Serial.begin(9600);
}

void loop()
{
    event();

    float front_distance_cm = calc_distance(FrontTRIGGER_PIN, FrontECHO_PIN);
    float rear_distance_cm = calc_distance(RearTRIGGER_PIN, RearECHO_PIN);

    update(front_distance_cm, rear_distance_cm);

    delay(100);
}

char event()
{
    if (mySerial.available()){
        if (mySerial.available() > 0)   //do {
            input = mySerial.read();    // } while (mySerial.available() > 0);
        print(input);
        delay(3);
    }

    return (input);
}

void update(float front_distance_cm, float rear_distance_cm)
{
    deplacements(input, front_distance_cm, rear_distance_cm);
}

int calc_distance(const byte TRIGGER_PIN, const byte ECHO_PIN)
{
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
    float distance_cm = ((measure / 2.0 * SOUND_SPEED) / 10);

    return (distance_cm);
}

void print(char input)
{
    switch (input) {
    case 65:
        Serial.println("Avant");
        mySerial.println("Avant");
        break;
    case 83:
        Serial.println("Stop");
        mySerial.println("Stop");
        break;
    case 82:
        Serial.println("Arriere");
        mySerial.println("Arriere");
        break;
    case 71:
        Serial.println("Gauche");
        mySerial.println("Gauche");
        break;
    case 68:
        Serial.println("Droite");
        mySerial.println("Droite");
        break;
    default: break;
    }


    // Serial.print(distance_cm, 2);
    // Serial.print(F("cm, "));
    // Serial.print('\n');
    // mySerial.print(distance_cm, 2);
    // mySerial.print(F("cm, "));
    // mySerial.print('\n');

}

void deplacements(char input, float front, float rear)
{

    for (int i = 0; retest[i].i; i++){
        if (input == retest[i].i){
            retest[i].ptr(front, rear);
            return;
        }
        if (i == 4){
            retest[i].ptr(front, rear);
            return;
        }
    }

    // switch (input) {
    // // case 'A':
    //     // avance(front);
    //     // break;
    // case 'R':
    //     recule(rear);
    //     break;
    // // case 'D':
    //     // droite(front);
    //     // break;
    // // case 'G':
    //     // gauche(front);
    //     // break;
    // case 'S': panic(); break;
    // default: panic();break;
    // }
}

void avance(float front, float rear)
{
    Serial.println("La");
    if (front >= 10){
        send_write(LFront, RFront);
    } else {
        panic(front, rear);
    }
}

void droite(float front, float rear)
{
    if (front >= 10){
        send_write(Stop, RFront);
    } else {
        panic(front, rear);
    }
}

void gauche(float front, float rear)
{
    if (front >= 10){
        send_write(LFront, Stop);
    } else {
        panic(front, rear);
    }
}

void recule(float front, float rear)
{
    if (rear >= 10){
        send_write(LRev, RRev);
    } else {
        panic(front, rear);
    }
}

void send_write(int left, int right)
{
    Lservo.write(left);
    Rservo.write(right);
}

void panic(float rip1, float rip2)
{
    Lservo.write(Stop);
    Rservo.write(Stop);
}
