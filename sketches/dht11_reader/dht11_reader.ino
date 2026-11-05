// Muhammed Salman
//
// dht11_reader.ino
//
// DHT11 temperature/humidity reader written directly against the
// single-wire protocol, with no external library.
//
// Protocol summary (from the DHT11 datasheet):
//   1. Host pulls the data line low for at least 18 ms, then releases
//      it (the pull-up raises the line) for 20-40 us.
//   2. DHT11 answers with ~80 us low then ~80 us high.
//   3. 40 data bits follow. Each bit: ~50 us low, then a high pulse -
//      ~26-28 us means 0, ~70 us means 1.
//   4. Bytes: humidity integer, humidity decimal, temperature
//      integer, temperature decimal, checksum (low 8 bits of the sum
//      of the first four bytes).
//
// Wiring: DATA -> D2 with a 4.7-10 kOhm pull-up to VCC (most modules
// include it), VCC -> 5 V, GND -> GND.
//
// Serial: 9600 baud, prints temp_c=, rh_pct= or an error string.

const byte DATA_PIN = 2;

// The DHT11 needs about 1 s between readings; do not poll faster.
const unsigned long SAMPLE_INTERVAL_MS = 2000;
unsigned long lastSampleMs = 0;

// Busy-wait for a pin level, bounded so a missing sensor cannot hang
// the loop. Returns the pulse length in microseconds, or 0 on timeout.
unsigned long waitPulse(byte level, unsigned long timeoutUs) {
    unsigned long start = micros();
    while (digitalRead(DATA_PIN) == level) {
        if (micros() - start > timeoutUs) return 0;
    }
    return micros() - start;
}

// Returns true and fills tempC/rh on success, false on any protocol
// or checksum error.
bool readDht11(int *tempC, int *rh) {
    byte data[5] = {0, 0, 0, 0, 0};

    // Start signal.
    pinMode(DATA_PIN, OUTPUT);
    digitalWrite(DATA_PIN, LOW);
    delay(18);
    digitalWrite(DATA_PIN, HIGH);
    delayMicroseconds(30);
    pinMode(DATA_PIN, INPUT);

    // Sensor response: low then high, about 80 us each.
    if (waitPulse(LOW, 100) == 0) return false;
    if (waitPulse(HIGH, 100) == 0) return false;

    // 40 bits, most significant bit first.
    for (int i = 0; i < 40; i++) {
        if (waitPulse(LOW, 100) == 0) return false;   // 50 us bit start
        unsigned long highUs = waitPulse(HIGH, 100);  // 26-28 or ~70 us
        if (highUs == 0) return false;
        data[i / 8] <<= 1;
        if (highUs > 40) data[i / 8] |= 1;            // long pulse = 1
    }

    byte sum = (byte)(data[0] + data[1] + data[2] + data[3]);
    if (sum != data[4]) return false;

    *rh = data[0];    // decimal byte is always 0 on the DHT11
    *tempC = data[2];
    return true;
}

void setup() {
    Serial.begin(9600);
    Serial.println(F("dht11_reader: started"));
}

void loop() {
    unsigned long nowMs = millis();
    if (nowMs - lastSampleMs < SAMPLE_INTERVAL_MS) return;
    lastSampleMs = nowMs;

    int tempC, rh;
    if (readDht11(&tempC, &rh)) {
        Serial.print(F("temp_c="));
        Serial.print(tempC);
        Serial.print(F(" rh_pct="));
        Serial.println(rh);
    } else {
        Serial.println(F("dht11_error"));
    }
}
