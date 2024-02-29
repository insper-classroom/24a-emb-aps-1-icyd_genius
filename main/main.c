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
const int LEDR_PIN = 21;
const int LEDG_PIN = 22;
const int LEDY_PIN = 23;
const int LEDB_PIN = 24;


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
        flagG = 2;
    } else if (gpio == BTNY_PIN) {
        flagG = 3;
    } else if (gpio == BTNB_PIN) {
        flagG = 4;
    } else if (gpio == BTNN_PIN) {
        flagG = 5;
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


    while (true) {
        sleep_ms(1000);
    }
}
