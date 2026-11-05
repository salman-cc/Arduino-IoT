# hc_sr04_distance

HC-SR04 ultrasonic distance reader with echo timeout and a median-of-5
filter that rejects single bad pings.

## Wiring

| HC-SR04 pin | Arduino pin |
| ----------- | ----------- |
| VCC | 5 V |
| TRIG | D7 |
| ECHO | D8 (through a divider on non-5 V-tolerant boards) |
| GND | GND |

## Serial output (9600 baud)

```text
distance_cm=24
distance_cm=timeout
```

## Notes

- Pings are spaced 60 ms apart so echoes die out between measurements.
- Conversion uses the integer approximation `cm = us / 58` (sound
  speed 343 m/s); expect about +-1 cm accuracy from the sensor itself,
  worse on soft or angled surfaces.
