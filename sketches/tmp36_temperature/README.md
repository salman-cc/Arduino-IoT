# tmp36_temperature

TMP36 analog temperature sensor with 16x averaged sampling.

## Wiring

| TMP36 pin | Arduino pin |
| --------- | ----------- |
| Vs | 5 V (set `VREF_MV` to 3300 on 3.3 V boards) |
| Vout | A0 |
| GND | GND |

## Serial output (9600 baud)

```text
temp_c=24.7
```

## Notes

The TMP36 outputs 10 mV/degC with a 500 mV offset, so
`temp_c = (voltage_mv - 500) / 10`. The sketch computes tenths of a
degree in integer math, avoiding floating point on AVR. Accuracy is
limited by the ADC reference; for better absolute accuracy measure the
real 5 V rail and adjust `VREF_MV`, or use an external reference.
