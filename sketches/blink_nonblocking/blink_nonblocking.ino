// Muhammed Salman
//
// blink_nonblocking.ino
//
// Blinks the built-in LED without delay(), so the loop stays free for
// other work (sensors, serial, network). This is the base pattern most
// IoT firmware here builds on: a cooperative loop driven by millis().
//
// Board: any Arduino-compatible board with LED_BUILTIN.
// Serial: 9600 baud, prints the uptime at every toggle.

const byte LED_PIN = LED_BUILTIN;
const unsigned long BLINK_INTERVAL_MS = 500;

unsigned long lastToggleMs = 0;
bool ledOn = false;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    Serial.println(F("blink_nonblocking: started"));
}

void loop() {
    unsigned long nowMs = millis();

    // Subtraction is wrap-safe across the 49.7-day millis() overflow.
    if (nowMs - lastToggleMs >= BLINK_INTERVAL_MS) {
        lastToggleMs = nowMs;
        ledOn = !ledOn;
        digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
        Serial.print(F("uptime_ms="));
        Serial.print(nowMs);
        Serial.print(F(" led="));
        Serial.println(ledOn ? F("ON") : F("OFF"));
    }

    // Other non-blocking work goes here.
}
