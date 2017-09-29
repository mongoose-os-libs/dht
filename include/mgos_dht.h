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

/* Supported sensor types */
enum dht_type {
  DHT11 = 11,
  DHT21 = 21,
  AM2301 = 21,
  DHT22 = 22,

  AM2302 = 22
};

struct mgos_dht;

/*
 * Initializes DHT.
 * Returns the DHT handle opaque pointer
 * or 'NULL' if operation failed.
 */
struct mgos_dht *mgos_dht_create(int pin, enum dht_type type);
/* Closes the DHT handle. */
void mgos_dht_close(struct mgos_dht *dht);
/* Returns temperature in DegC or 'NAN' if operation failed. */
float mgos_dht_get_temp(struct mgos_dht *dht);
/* Returns humidity in % or 'NAN' if operation failed. */
float mgos_dht_get_humidity(struct mgos_dht *dht);

bool mgos_dht_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_DHT_SRC_MGOS_DHT_H_ */
