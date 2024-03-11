/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <time.h>
#include "project.h"


const int melody[] = {

  // At Doom's Gate (E1M1)
  // Score available at https://musescore.com/pieridot/doom

  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //1
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //5
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //9
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //13
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
  NOTE_FS3, -16, NOTE_D3, -16, NOTE_B2, -16, NOTE_A3, -16, NOTE_FS3, -16, NOTE_B2, -16, NOTE_D3, -16, NOTE_FS3, -16, NOTE_A3, -16, NOTE_FS3, -16, NOTE_D3, -16, NOTE_B2, -16,
  
};


volatile int flagR = 0;
volatile int flagG = 0;
volatile int flagY = 0;
volatile int flagB = 0;
volatile int flagN = 0;


void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {
    if (gpio == BTNR_PIN) {
      flagR = 1;
    } else if (gpio == BTNG_PIN) {
        flagG = 1;
    } else if (gpio == BTNY_PIN) {
        flagY = 1;
    } else if (gpio == BTNB_PIN) {
        flagB = 1;
    } else if (gpio == BTNN_PIN) {
        flagN = 1;
    }
  } 
}

int getRandomNumber() {
    srand((unsigned)time(NULL));
    return rand() % 4;
}

void addNewColor() {
    int l = getRandomNumber();
    v[n] = l;
    n++;
}

void soundCreator(int freq, int duration) {
    double period_ms = 1000.0 / freq;
    double half_period_ms = (period_ms / 2.0);
    int half_period_us = (int)(half_period_ms*1000);
    int total_cycles = freq * duration / 1000;
    
    for (int i = 0; i < total_cycles; i++) {
        gpio_put(BUZ_PIN, 1);
        sleep_us(half_period_us);
        gpio_put(BUZ_PIN, 0);
        sleep_us(half_period_us);
    }
}

void piscaLED(int PIN, int freq, int duration) {
    gpio_put(PIN, 1);
    soundCreator(freq, duration);
    gpio_put(PIN, 0);
    sleep_ms(80);
}

void piscaSEQ() {
    for (int i = 0; i < n+1; i++) {
        if (v[i] == 0) {
            piscaLED(LEDR_PIN, NOTE_C4, (1000-(20*roundn)));
        } else if (v[i] == 1) {
            piscaLED(LEDG_PIN, NOTE_E4, (1000-(20*roundn)));
        } else if (v[i] == 2) {
            piscaLED(LEDY_PIN, NOTE_G4, (1000-(20*roundn)));
        } else if (v[i] == 3) {
            piscaLED(LEDR_PIN, NOTE_C4, (1000-(20*roundn)));
        }
    }
}

void waitInputs() {
    int i = 0;
    flagR = 0;
    flagG = 0;
    flagY = 0;
    flagB = 0;
    printf("Entrei Wait Inputs\n");
    while ((i < n) && (gameState == 1)) {
        printf("Entrei while\n");
        if (flagR == 1) {
            piscaLED(LEDR_PIN, 264, 400);
            printf("Entrou R\n");
            sleep_ms(200);
            if (v[i] != 0) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagR = 0; 
        } else if (flagG == 1) {
            piscaLED(LEDG_PIN, 264, 400);
            printf("Entrou G\n");
            sleep_ms(200);
            if (v[i] != 1) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagG = 0;
        } else if (flagY == 1) {
            piscaLED(LEDY_PIN, 264, 400);
            printf("Entrou Y\n");
            sleep_ms(200);
            if (v[i] != 2) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagY = 0;
        } else if (flagB == 1) {
            piscaLED(LEDB_PIN, 264, 400);
            printf("Entrou B\n");
            sleep_ms(200);
            if (v[i] != 3) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagB = 0;
        }
        sleep_ms(100);
        printf("Valor de I: %d\n", i);
    }
    return;
}

void emptyArray() {
    for (int i = 0; i <= n; i++) {
        v[i] = 4;
    }
    if (n > Highscore) {
        Highscore = n;
    }
    n = 0;
}

void endingSong() {
    soundCreator(264, 500);
    sleep_ms(100);
    soundCreator(198, 500);
    sleep_ms(100);
    soundCreator(165, 500);
    sleep_ms(100);
    soundCreator(132, 2000);
    printf("Acabei de Tocar");
}

void intro() {
    int tempo = 225;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote += 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = wholenote / divider;
        } else if (divider < 0) {
            noteDuration = wholenote / abs(divider);
            noteDuration *= 1.5; 
        }

        int playDuration = noteDuration * 0.9;
        soundCreator(melody[thisNote], (int)playDuration);
        sleep_ms(noteDuration - (int)playDuration);
    }
}



void score() {
    if (roundn == 1) {
        return;
    }
    for (int i = 0; i <= roundn-3; i++) {
        if ((i+4) % 4 == 0) {
            piscaLED(LEDY_PIN, 100, 500);
        } else if ((i+4) % 4 == 1) {
            piscaLED(LEDR_PIN, 100, 500);
        } else if ((i+4) % 4 == 2) {
            piscaLED(LEDB_PIN, 100, 500);
        } else if ((i+4) % 4 == 3) {
            piscaLED(LEDG_PIN, 100, 500);
        }
    }
}



 int main() {
    stdio_init_all();

    gpio_init(BTNR_PIN);
    gpio_set_dir(BTNR_PIN, GPIO_IN);
    gpio_pull_up(BTNR_PIN);

    gpio_init(BTNG_PIN);
    gpio_set_dir(BTNG_PIN, GPIO_IN);
    gpio_pull_up(BTNG_PIN);

    gpio_init(BTNY_PIN);
    gpio_set_dir(BTNY_PIN, GPIO_IN);
    gpio_pull_up(BTNY_PIN);

    gpio_init(BTNB_PIN);
    gpio_set_dir(BTNB_PIN, GPIO_IN);
    gpio_pull_up(BTNB_PIN);

    gpio_init(BTNN_PIN);
    gpio_set_dir(BTNN_PIN, GPIO_IN);
    gpio_pull_up(BTNN_PIN);

    gpio_init(LEDR_PIN);
    gpio_set_dir(LEDR_PIN, GPIO_OUT);

    gpio_init(LEDG_PIN);
    gpio_set_dir(LEDG_PIN, GPIO_OUT);

    gpio_init(LEDY_PIN);
    gpio_set_dir(LEDY_PIN, GPIO_OUT);

    gpio_init(LEDB_PIN);
    gpio_set_dir(LEDB_PIN, GPIO_OUT);

    gpio_init(BUZ_PIN);
    gpio_set_dir(BUZ_PIN, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(BTNR_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTNG_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTNY_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTNB_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTNN_PIN, GPIO_IRQ_EDGE_FALL, true);

    printf("Setei Geral\n");

    int v[] = {};
    int n = 0;
    int Highscore = 0;
    int gameState = 0;
    int roundn = 1;

    while (true) {
        intro();
        if (flagN == 1) {
            gameState = 1; 
            flagN = 0;
            printf("Toquei!\n");   
        }
        while (gameState == 1) {
            printf("Começou a rodada\n");
            addNewColor();
            piscaSEQ();
            sleep_ms(100);
            waitInputs();
            sleep_ms(200);
            roundn++;
        } 
        if (gameState == 2) {
            printf("Perdeu\n");
            endingSong();
            score();
            printf("%d\n", roundn-1);
            gameState = 0;
            emptyArray();
            roundn = 1;
            flagG = 0;
            flagR = 0;
            flagB = 0;
            flagY = 0;
        }
        sleep_ms(1000);
        printf("GameState: %d\n", gameState);
    }
}
