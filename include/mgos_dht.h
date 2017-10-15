/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

/*
 * DHT sensor API.
 *
 * See https://learn.adafruit.com/dht/overview for more information.
 */

#ifndef CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_
#define CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_

#include <math.h>
#include <stdbool.h>

#include "mgos_dht.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Supported sensor types */
enum dht_type {
  DHT11 = 11,
  DHT21 = 21,
  AM2301 = 21,
  DHT22 = 22,
  AM2302 = 22
};

struct mgos_dht;

/* Initialise DHT sensor. Return an opaque DHT handle, or `NULL` on error. */
struct mgos_dht *mgos_dht_create(int pin, enum dht_type type);

/* Close DHT handle. */
void mgos_dht_close(struct mgos_dht *dht);

/* Return temperature in DegC or 'NAN' on failure. */
float mgos_dht_get_temp(struct mgos_dht *dht);

/* Return humidity in % or 'NAN' on failure. */
float mgos_dht_get_humidity(struct mgos_dht *dht);

bool mgos_dht_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_ */
