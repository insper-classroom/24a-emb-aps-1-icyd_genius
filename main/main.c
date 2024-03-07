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


volatile int flagR = 0;
volatile int flagG = 0;
volatile int flagY = 0;
volatile int flagB = 0;
volatile int flagN = 0;

volatile int v[] = {};
volatile int n = 0;
volatile int Highscore = 0;
volatile int gameState = 0;
volatile int roundn = 1;


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
    float period_ms = 1000.0 / freq;
    int half_period_ms = (int)(period_ms / 2.0);
    int total_cycles = freq * duration / 1000;
    
    for (int i = 0; i < total_cycles; i++) {
        gpio_put(BUZ_PIN, 1);
        sleep_ms(half_period_ms);
        gpio_put(BUZ_PIN, 0);
        sleep_ms(half_period_ms);
    }
}

void piscaLED(int PIN, int freq, int duration) {
    gpio_put(PIN, 1);
    soundCreator(freq, duration);
    gpio_put(PIN, 0);
    sleep_ms(150);
}

void piscaSEQ() {
    for (int i = 0; i < n+1; i++) {
        if (v[i] == 0) {
            piscaLED(LEDR_PIN, 264, 1000);
        } else if (v[i] == 1) {
            piscaLED(LEDG_PIN, 330, 1000);
        } else if (v[i] == 2) {
            piscaLED(LEDY_PIN, 440, 1000);
        } else if (v[i] == 3) {
            piscaLED(LEDB_PIN, 528, 1000);
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
            printf("Entrou R\n");
            sleep_ms(200);
            if (v[i] != 0) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagR = 0; 
        } else if (flagG == 1) {
            printf("Entrou G\n");
            sleep_ms(200);
            if (v[i] != 1) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagG = 0;
        } else if (flagY == 1) {
            printf("Entrou Y\n");
            sleep_ms(200);
            if (v[i] != 2) {
                gameState = 2;
                printf("BASOU\n");
            }
            i++;
            flagY = 0;
        } else if (flagB == 1) {
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
    soundCreator(264, 0.5);
    soundCreator(198, 0.5);
    soundCreator(165, 0.5);
    soundCreator(132, 2);
}

void Homecoming() {
    // Assuming A4 = 440 Hz, and other frequencies are adjusted accordingly
    int B4 = 494; // Closest to 493.88 Hz
    int D5 = 587; // D5
    int C5 = 523; // C5
    int G4 = 392; // G4
    int F4 = 349; // F4
    int E4 = 329; // E4
    int A4 = 440; // A4
    int FSharp4 = 370; // F#4/Gb4
    int E5 = E4*2;
    int D4 = 294;

    // Rewriting the function with more accurate pauses and note frequencies
    soundCreator(B4, 120);
    sleep_ms(130); // Adjusted pause
    soundCreator(B4, 120);
    sleep_ms(130);
    soundCreator(B4, 120);
    sleep_ms(130);
    soundCreator(B4, 120);
    sleep_ms(130);
    soundCreator(B4, 120);
    sleep_ms(130);
    soundCreator(B4, 180);
    soundCreator(D5, 400);
    sleep_ms(100); // Pause before changing notes
    soundCreator(C5, 200);
    sleep_ms(100); // Pause before changing notes
    soundCreator(B4, 1000);
    sleep_ms(500); // Longer pause
    soundCreator(B4, 180);
    sleep_ms(220); // Adjusted pause
    soundCreator(B4, 180);
    sleep_ms(220);
    soundCreator(B4, 180);
    sleep_ms(220);
    soundCreator(B4, 180);
    sleep_ms(220);
    soundCreator(B4, 180);
    sleep_ms(220);
    soundCreator(B4, 180);
    soundCreator(D5, 400);
    sleep_ms(100); // Pause before changing notes
    soundCreator(E5, 200);
    sleep_ms(100); // Pause before changing notes
    soundCreator(B4, 600);
    sleep_ms(200); // Pause before changing notes
    soundCreator(A4, 200);
    sleep_ms(100); // Pause before changing notes
    soundCreator(G4, 1000);
    sleep_ms(600); // Longer pause
    soundCreator(G4, 200);
    soundCreator(FSharp4, 380);
    sleep_ms(120); // Adjusted pause
    soundCreator(FSharp4, 200);
    soundCreator(G4, 200);
    sleep_ms(100); // Pause before changing notes
    soundCreator(FSharp4, 400);
    sleep_ms(200); // Pause before changing notes
    soundCreator(D4, 200);
    sleep_ms(100); // Pause before changing notes
    soundCreator(E4, 1000);
    sleep_ms(400); // Pause before next part
    soundCreator(D5, 800);
    sleep_ms(200); // Pause before changing notes
    soundCreator(B4, 800);
    sleep_ms(200); // Pause before changing notes
    soundCreator(G4, 400);
    sleep_ms(200); // Pause before changing notes
    soundCreator(E4, 400);
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

    while (true) {
        Homecoming();
        if (flagN == 1) {
            gameState = 1; 
            flagN = 0;   
        }
        while (gameState == 1) {
            printf("Começou a rodada\n");
            addNewColor();
            piscaSEQ();
            sleep_ms(200);
            waitInputs();
            sleep_ms(500);
            roundn++;
        } 
        if (gameState == 2) {
            printf("Perdeu\n");
            endingSong();
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
