# serial_command

Line-based serial command parser with a fixed 32-byte buffer and no
`String` class (no heap fragmentation). Useful as the control channel
for larger projects.

## Wiring

None: uses `LED_BUILTIN` and USB serial.

## Commands (9600 baud, newline-terminated, case-insensitive)

| Command | Effect |
| ------- | ------ |
| `LED ON` / `LED OFF` / `LED TOGGLE` | Control the built-in LED |
| `STATUS` | Print LED state and uptime |
| `HELP` | List commands |

Overlong lines are discarded safely instead of corrupting memory.

## Example session

```text
serial_command: ready, type HELP
LED ON
ok
STATUS
led=ON uptime_ms=42130
```
