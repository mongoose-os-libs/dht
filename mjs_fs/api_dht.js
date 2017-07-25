// Mongoose OS DHT library API. Source C API is defined at:
// [mgos_dht.h](https://github.com/mongoose-os-libs/dht/tree/master/src/mgos_dht.h)

let DHT = {
  _crt: ffi('void *mgos_dht_create(int, int)'),
  _cls: ffi('void mgos_dht_close(void *)'),
  _gt: ffi('float mgos_dht_get_temp(void *)'),
  _gh: ffi('float mgos_dht_get_humidity(void *)'),

  // Define type of sensors.
  DHT11: 11,
  DHT21: 21,
  AM2301: 21,
  DHT22: 22,
  AM2302: 22,

  _proto: {
    // Close DHT handle. Return value: none.
    close: function() {
      return DHT._cls(this.dht);
    },

    // Returns temperature in DegC
    // or 'NaN' if operation failed
    getTemp: function() {
      return DHT._gt(this.dht);
    },

    // Returns temperature in RH%
    // or 'NaN' if operation failed.
    getHumidity: function() {
      return DHT._gh(this.dht);
    },
  },

  // Create a DHT object.
  create: function(pin, type) {
    let obj = Object.create(DHT._proto);
    // Initialize DHT library.
    // Return value: DHT handle opaque pointer
    // or 'null' if operation failed.
    obj.dht = DHT._crt(pin, type);
    return obj;
  },
};
