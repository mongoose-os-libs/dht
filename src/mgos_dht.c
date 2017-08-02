/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

/*
 * View this file on GitHub:
 * [mgos_dht.c](https://github.com/mongoose-os-libs/dht/blob/master/src/mgos_dht.c)
 */

#include "mgos_dht.h"
#include "fw/src/mgos_gpio.h"
#include "fw/src/mgos_hal.h"
#include "mongoose/mongoose.h"

#ifndef IRAM
#define IRAM
#endif

#define MGOS_DHT_READ_DELAY 2.0

struct mgos_dht {
  int pin;
  enum dht_type type;
  unsigned char data[5];
  bool last_result;
  double last_read_time;
};

IRAM static bool dht_wait(int pin, int lvl, int ticks) {
  while (mgos_gpio_read(pin) != lvl) {
    if (--ticks <= 0) return false;
  }
  return true;
}

IRAM static bool dht_read(struct mgos_dht *dht) {
  if (dht == NULL) return false;
  bool err = true;
  int t = 100 * (mgos_get_cpu_freq() / 1000000L);
  double now = mg_time();
  if ((now - dht->last_read_time) < MGOS_DHT_READ_DELAY) {
    return dht->last_result;
  }
  dht->last_read_time = now;
  dht->last_result = false;
  memset(dht->data, 0, 5);

  mgos_gpio_set_mode(dht->pin, MGOS_GPIO_MODE_INPUT);
  mgos_gpio_set_pull(dht->pin, MGOS_GPIO_PULL_UP);
  mgos_msleep(250);

  mgos_gpio_set_mode(dht->pin, MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_write(dht->pin, 0);
  mgos_msleep(20);

  mgos_ints_disable();

  mgos_gpio_write(dht->pin, 1);
  mgos_usleep(40);

  mgos_gpio_set_mode(dht->pin, MGOS_GPIO_MODE_INPUT);
  mgos_gpio_set_pull(dht->pin, MGOS_GPIO_PULL_UP);
  mgos_usleep(10);

  if (!dht_wait(dht->pin, 1, t) || !dht_wait(dht->pin, 0, t)) goto end;

  for (int i = 0; i < 40; i++) {
    if (!dht_wait(dht->pin, 1, t)) goto end;
    dht->data[i / 8] <<= 1;
    mgos_usleep(50);
    if (mgos_gpio_read(dht->pin) == 1) {
      dht->data[i / 8] |= 1;
      mgos_usleep(50);
    }
  }
  err = false;
end:
  mgos_ints_enable();
  if (!err &&
      (dht->data[4] ==
       ((dht->data[0] + dht->data[1] + dht->data[2] + dht->data[3]) & 0xFF)))
    dht->last_result = true;
  return dht->last_result;
}

struct mgos_dht *mgos_dht_create(int pin, enum dht_type type) {
  struct mgos_dht *dht = calloc(1, sizeof(*dht));
  if (dht == NULL) return NULL;
  dht->pin = pin;
  dht->type = type;
  if (!mgos_gpio_set_mode(dht->pin, MGOS_GPIO_MODE_INPUT) ||
      !mgos_gpio_set_pull(dht->pin, MGOS_GPIO_PULL_UP)) {
    mgos_dht_close(dht);
    return NULL;
  }
  return dht;
}

void mgos_dht_close(struct mgos_dht *dht) {
  free(dht);
  dht = NULL;
}

float mgos_dht_get_temp(struct mgos_dht *dht) {
  float res = NAN;

  if (dht_read(dht)) {
    switch (dht->type) {
      case DHT11:
        res = dht->data[2];
        break;
      case DHT22:
      case DHT21:
        res = dht->data[2] & 0x7F;
        res *= 256;
        res += dht->data[3];
        res *= 0.1;
        if (dht->data[2] & 0x80) res *= -1;
        break;
    }
  }
  return res;
}

float mgos_dht_get_humidity(struct mgos_dht *dht) {
  float res = NAN;

  if (dht_read(dht)) {
    switch (dht->type) {
      case DHT11:
        res = dht->data[0];
        break;
      case DHT22:
      case DHT21:
        res = dht->data[0];
        res *= 256;
        res += dht->data[1];
        res *= 0.1;
        break;
    }
  }
  return res;
}

bool mgos_dht_init(void) {
  return true;
}
