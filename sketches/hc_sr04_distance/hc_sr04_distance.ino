// Muhammed Salman
//
// hc_sr04_distance.ino
//
// HC-SR04 ultrasonic distance reader with timeout handling and a
// median-of-5 filter to reject single bad pings.
//
// Wiring: TRIG -> D7, ECHO -> D8 (through a divider if the board is
// not 5 V tolerant), VCC -> 5 V, GND -> GND.
//
// Serial: 9600 baud, prints distance_cm=<value> or distance_cm=timeout.

const byte TRIG_PIN = 7;
const byte ECHO_PIN = 8;

// Longest echo we wait for: about 4 m round trip.
const unsigned long ECHO_TIMEOUT_US = 24000UL;

// Sound speed 343 m/s -> 58.3 us per cm of round trip. Integer math
// keeps this fast on AVR: cm = us / 58.
const unsigned long US_PER_CM = 58;

const unsigned long SAMPLE_INTERVAL_MS = 500;
unsigned long lastSampleMs = 0;

// One ping; returns round-trip time in microseconds, or 0 on timeout.
unsigned long pingUs() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
}

void sort(unsigned long *v, size_t n) {
    for (size_t i = 1; i < n; i++) {
        unsigned long key = v[i];
        size_t j = i;
        while (j > 0 && v[j - 1] > key) {
            v[j] = v[j - 1];
            j--;
        }
        v[j] = key;
    }
}

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.begin(9600);
    Serial.println(F("hc_sr04_distance: started"));
}

void loop() {
    unsigned long nowMs = millis();
    if (nowMs - lastSampleMs < SAMPLE_INTERVAL_MS) return;
    lastSampleMs = nowMs;

    unsigned long samples[5];
    size_t good = 0;
    for (size_t i = 0; i < 5; i++) {
        unsigned long us = pingUs();
        if (us > 0) samples[good++] = us;
        delay(60);  // let echoes die between pings
    }

    Serial.print(F("distance_cm="));
    if (good == 0) {
        Serial.println(F("timeout"));
        return;
    }
    sort(samples, good);
    unsigned long medianUs = samples[good / 2];
    Serial.println(medianUs / US_PER_CM);
}
