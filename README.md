# Arduino-IoT

> Repository maintained by Muhammed Salman CC

A growing collection of original, dependency-light Arduino sketches for
IoT and embedded work. Each sketch is a self-contained project with its
own README covering wiring, serial output and limitations.

## Sketches

| Sketch | What it does | External libraries |
| ------ | ------------ | ------------------ |
| [`blink_nonblocking`](sketches/blink_nonblocking/) | Cooperative `millis()` blink pattern, no `delay()` | none |
| [`serial_command`](sketches/serial_command/) | Fixed-buffer serial command parser (no `String`) | none |
| [`hc_sr04_distance`](sketches/hc_sr04_distance/) | Ultrasonic distance with timeout and median filter | none |
| [`tmp36_temperature`](sketches/tmp36_temperature/) | Averaged analog temperature, integer math | none |
| [`dht11_reader`](sketches/dht11_reader/) | DHT11 read via the raw single-wire protocol | none |

## Building

With [arduino-cli](https://arduino.github.io/arduino-cli/):

```sh
arduino-cli compile --fqbn arduino:avr:uno sketches/blink_nonblocking
```

Replace `arduino:avr:uno` with your board's FQBN. The sketches avoid
board-specific features; pins are constants at the top of each file.

## Verification status

All five sketches compile cleanly for `arduino:avr:uno` with
arduino-cli 1.5.2 and platform arduino:avr 1.8.8 (verified
5 November 2026). They have **not** been run on hardware yet; expected
serial output in the per-sketch READMEs is from code inspection, not
measurement.

## Status

🚧 Active Development

## License

MIT
