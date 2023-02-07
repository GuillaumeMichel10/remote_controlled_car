/*
** EPITECH PROJECT, 2022
** Arduino
** File description:
** my
*/

#include <Servo.h>
#include <SoftwareSerial.h>

//Deplacements////////

#define RservoPin 6
#define LservoPin 7

#define RFront 100
#define LFront 80

#define RRev 80
#define LRev 100

#define Stop 90

///////////////////////

//Emetteur////////////

#define rxPin 11 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 10 // Broche 10 en tant que TX, à raccorder sur RX du HC-05

typedef struct test_s{
    int i;
    void (*ptr)(float front, float rear);
}test_t;

test_t retest[6] =
{
    {'A', &avance},
    {'R', &recule},
    {'G', &gauche},
    {'D', &droite},
    {'S', &panic},
    {'\0', NULL}
};