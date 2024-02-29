/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BUZ_PIN = 10;
const int BTNR_PIN = 15;
const int BTNG_PIN = 14;
const int BTNY_PIN = 13;
const int BTNB_PIN = 12;
const int BTNN_PIN = 11;
const int LEDR_PIN = 2;
const int LEDG_PIN = 3;
const int LEDY_PIN = 4;
const int LEDB_PIN = 5;


volatile int flagR = 0;
volatile int flagG = 0;
volatile int flagY = 0;
volatile int flagB = 0;
volatile int flagN = 0;

volatile int v[] = {};
volatile int n = 0;
volatile int Highscore = 0;
volatile int gameState = 0;
volatile int round = 1;


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
  return rand() % 4;
}

void addNewColor() {
    int l = getRandomNumber();
    v[n] = l;
    n++;
}

void piscaLED(int PIN, int freq, int duration) {
    gpio_put(PIN, 1);
    soundCreator(freq, duration);
    gpio_put(PIN, 0);
    sleep_ms(20);
}

void piscaSEQ() {
    for (int i = 0; i < n+1; i++) {
        if (v[i] == 0) {
            piscaLED(LEDR_PIN, 264, 0.4);
        } else if (v[i] == 1) {
            piscaLED(LEDG_PIN, 330, 0.4);
        } else if (v[i] == 2) {
            piscaLED(LEDY_PIN, 440, 0.4);
        } else if (v[i] == 3) {
            piscaLED(LEDB_PIN, 528, 0.4);
        }
    }
}

void waitInputs() {
    int i;
    while ((i < n+1) && (gameState == 1)) {
        if (flagR == 1) {
            if (v[i] != 0) {
                gameState = 2;
            }
            i++;
            flagR = 0; 
        } else if (flagG == 1) {
            if (v[i] != 1) {
                gameState = 2;
            }
            i++;
            flagG = 0;
        } else if (flagY == 1) {
            if (v[i] != 2) {
                gameState = 2;
            }
            i++;
            flagY = 0;
        } else if (flagB == 1) {
            if (v[i] != 3) {
                gameState = 2;
            }
            i++;
            flagB = 0;
        }
        sleep_ms(30);
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

void soundCreator(int freq, int duration) {
    for (int i = 0; i <= freq*duration; i++) {
        gpio_put(BUZ_PIN, 1);
        sleep_ms((1/freq)/2);
        gpio_put(BUZ_PIN, 0);
        sleep_ms((1/freq)/2);
    }
}

void endingSong() {
    soundCreator(264, 0.5);
    soundCreator(198, 0.5);
    soundCreator(165, 0.5);
    soundCreator(132, 2);
}

void Homecoming() {
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    soundCreator(587, 0.4);
    soundCreator(523, 0.2);
    soundCreator(493, 1);
    sleep_ms(400);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    sleep_ms(20);
    soundCreator(493, 0.18);
    soundCreator(587, 0.4);
    soundCreator(659, 0.2);
    soundCreator(493, 0.6);
    soundCreator(440, 0.2);
    soundCreator(392, 1);
    sleep_ms(600);
    soundCreator(392, 0.2);
    soundCreator(369, 0.38);
    sleep_ms(20);
    soundCreator(369, 0.2);
    soundCreator(392, 0.2);
    soundCreator(369, 0.4);
    soundCreator(293, 0.2);
    soundCreator(329, 1);
    soundCreator(587, 0.8);
    soundCreator(493, 0.8);
    soundCreator(392, 0.4);
    soundCreator(329, 0.4);
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


    while (true) {
        Homecoming();
        if (flagN == 1) {
            gameState = 1; 
            flagN = 0;       
        }
        while (gameState == 1) {
            addNewColor();
            piscaSEQ();
            sleep_ms(500);
            waitInputs();
            round++;
        } 
        if (gameState == 2) {
            endingSong();
            printf("%d\n", round);
            gameState == 0;
            emptyArray();
            round = 1;
        }
    }
}
