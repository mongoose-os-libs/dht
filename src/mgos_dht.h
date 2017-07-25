/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

/*
 * View this file on GitHub:
 * [mgos_dht.h](https://github.com/mongoose-os-libs/dht/blob/master/src/mgos_dht.h)
 */

#ifndef CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_
#define CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_

#include <math.h>
#include <stdbool.h>

#include "mgos_dht.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21
#define AM2302 22

struct mgos_dht {
  int pin;
  int type;
  unsigned char data[5];
  bool last_result;
  unsigned int last_read_time;
};

struct mgos_dht *mgos_dht_create(int pin, int type);
void mgos_dht_close(struct mgos_dht *dht);

float mgos_dht_get_temp(struct mgos_dht *dht);
float mgos_dht_get_humidity(struct mgos_dht *dht);

/* mJS wrappers */
int mgos_dht_get_temp_int(struct mgos_dht *dht);
int mgos_dht_get_humidity_int(struct mgos_dht *dht);

bool mgos_dht_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_ */
