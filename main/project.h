#ifndef PROJECT_H
#define PROJECT_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <time.h>

#define BUZ_PIN 10
#define BTNR_PIN 15
#define BTNG_PIN 14
#define BTNY_PIN 13
#define BTNB_PIN 12
#define BTNN_PIN 11
#define LEDR_PIN 16
#define LEDG_PIN 17
#define LEDY_PIN 18
#define LEDB_PIN 19

extern volatile int flagR;
extern volatile int flagG;
extern volatile int flagY;
extern volatile int flagB;
extern volatile int flagN;

extern volatile int v[];
extern volatile int n;
extern volatile int Highscore;
extern volatile int gameState;
extern volatile int roundn;

void btn_callback(uint gpio, uint32_t events);
int getRandomNumber();
void addNewColor();
void soundCreator(int freq, int duration);
void piscaLED(int PIN, int freq, int duration);
void piscaSEQ();
void waitInputs();
void emptyArray();
void endingSong();
void Homecoming();

#endif
