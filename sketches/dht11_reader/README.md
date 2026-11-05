# dht11_reader

DHT11 temperature and humidity reader written directly against the
single-wire protocol - no external library.

## Wiring

| DHT11 pin | Arduino pin |
| --------- | ----------- |
| VCC | 5 V |
| DATA | D2, with a 4.7-10 kOhm pull-up (modules usually include it) |
| GND | GND |

## Serial output (9600 baud)

```text
temp_c=25 rh_pct=60
```

or `dht11_error` on a missing sensor, timeout or checksum mismatch.

## Notes

- The DHT11 needs about one second between readings; the sketch polls
  every two seconds.
- All protocol waits are bounded, so a disconnected sensor cannot hang
  the main loop.
- Resolution is 1 degC / 1% RH (the DHT11's decimal bytes are always
  zero); for better resolution use a DHT22 with adjusted decoding.
