/*
 * Copyright (c) 2014-2018 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * DHT sensor API.
 *
 * See https://learn.adafruit.com/dht/overview for more information.
 */

#ifndef CS_MOS_LIBS_DHT_INCLUDE_MGOS_DHT_H_
#define CS_MOS_LIBS_DHT_INCLUDE_MGOS_DHT_H_

#include <math.h>
#include <stdbool.h>

#include "mgos_dht.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Supported sensor types */
enum dht_type { DHT11 = 11, DHT21 = 21, AM2301 = 21, DHT22 = 22, AM2302 = 22 };

struct mgos_dht;

/* Initialise DHT sensor. Return an opaque DHT handle, or `NULL` on error. */
struct mgos_dht *mgos_dht_create(int pin, enum dht_type type);

/* Close DHT handle. */
void mgos_dht_close(struct mgos_dht *dht);

/* Return temperature in DegC or 'NAN' on failure. */
float mgos_dht_get_temp(struct mgos_dht *dht);

/* Return humidity in % or 'NAN' on failure. */
float mgos_dht_get_humidity(struct mgos_dht *dht);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_DHT_INCLUDE_MGOS_DHT_H_ */
