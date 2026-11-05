// Muhammed Salman
//
// serial_command.ino
//
// A small line-based serial command parser with a fixed-size buffer
// (no String class, so no heap fragmentation). Useful as the control
// channel for larger projects.
//
// Commands (terminated by \n or \r, case-insensitive):
//   LED ON / LED OFF / LED TOGGLE   control the built-in LED
//   STATUS                          print LED state and uptime
//   HELP                            list the commands
//
// Serial: 9600 baud.

const byte LED_PIN = LED_BUILTIN;
const size_t LINE_CAP = 32;

char lineBuf[LINE_CAP];
size_t lineLen = 0;

bool ledOn = false;

void printHelp() {
    Serial.println(F("commands: LED ON | LED OFF | LED TOGGLE | STATUS | HELP"));
}

void printStatus() {
    Serial.print(F("led="));
    Serial.print(ledOn ? F("ON") : F("OFF"));
    Serial.print(F(" uptime_ms="));
    Serial.println(millis());
}

bool equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        char ca = *a, cb = *b;
        if (ca >= 'a' && ca <= 'z') ca -= 'a' - 'A';
        if (cb >= 'a' && cb <= 'z') cb -= 'a' - 'A';
        if (ca != cb) return false;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

void handleLine(const char *line) {
    if (equalsIgnoreCase(line, "LED ON")) {
        ledOn = true;
        digitalWrite(LED_PIN, HIGH);
        Serial.println(F("ok"));
    } else if (equalsIgnoreCase(line, "LED OFF")) {
        ledOn = false;
        digitalWrite(LED_PIN, LOW);
        Serial.println(F("ok"));
    } else if (equalsIgnoreCase(line, "LED TOGGLE")) {
        ledOn = !ledOn;
        digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
        Serial.println(F("ok"));
    } else if (equalsIgnoreCase(line, "STATUS")) {
        printStatus();
    } else if (equalsIgnoreCase(line, "HELP")) {
        printHelp();
    } else if (line[0] != '\0') {
        Serial.print(F("unknown command: "));
        Serial.println(line);
    }
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    Serial.println(F("serial_command: ready, type HELP"));
}

void loop() {
    while (Serial.available() > 0) {
        char c = (char)Serial.read();
        if (c == '\n' || c == '\r') {
            if (lineLen > 0) {
                lineBuf[lineLen] = '\0';
                handleLine(lineBuf);
                lineLen = 0;
            }
        } else if (lineLen < LINE_CAP - 1) {
            lineBuf[lineLen++] = c;
        } else {
            // Overflow: drop the line instead of corrupting memory.
            lineLen = 0;
            Serial.println(F("error: line too long, discarded"));
        }
    }
}
