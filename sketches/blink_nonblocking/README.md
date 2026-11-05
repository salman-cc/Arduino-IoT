# blink_nonblocking

Blinks the built-in LED every 500 ms **without `delay()`**, so the main
loop stays free for sensors, serial and network work. This cooperative
`millis()` pattern is the base most IoT firmware here builds on.

## Wiring

None: uses `LED_BUILTIN`.

## Serial output (9600 baud)

```text
uptime_ms=500 led=ON
uptime_ms=1000 led=OFF
```

## Notes

The interval check uses subtraction (`nowMs - lastToggleMs`), which
stays correct across the 49.7-day `millis()` overflow.
