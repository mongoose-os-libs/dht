// Mongoose OS DHT library API. Source C API is defined at:
// [mgos_dht.h](https://github.com/mongoose-os-libs/dht/tree/master/src/mgos_dht.h)

let DHT = {
  _crt: ffi('void *mgos_dht_create(int, int)'),
  _cls: ffi('void mgos_dht_close(void *)'),
  _gt: ffi('int mgos_dht_get_temp_int(void *)'),
  _gh: ffi('int mgos_dht_get_humidity_int(void *)'),

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
    // or -127.0 if operation failed
    getTemp: function() {
      // C-functions output value of “1234” equals 12.34 Deg.
      return DHT._gt(this.dht) / 100.0;
    },

    // Returns temperature in RH% or -127.0 if operation failed.
    getHumidity: function() {
      // C-functions output value of “4321” equals 43.21 %.
      return DHT._gh(this.dht) / 100.0;
    },
  },

  // Create a DHT object.
  create: function(pin, type) {
    let obj = Object.create(DHT._proto);
    // Initialize DHT library.
    // Return value: DHT handle opaque pointer.
    obj.dht = DHT._crt(pin, type);
    return obj;
  },
};
