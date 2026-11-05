// Muhammed Salman
//
// tmp36_temperature.ino
//
// TMP36 analog temperature sensor with averaged sampling.
//
// TMP36 transfer function: 10 mV per degree C with a 500 mV offset,
// so temp_c = (voltage_mv - 500) / 10.
//
// Wiring: TMP36 Vout -> A0, Vs -> 5 V (or 3.3 V, set VREF_MV to
// match), GND -> GND. A0 must see a low-impedance source, which the
// TMP36 provides.
//
// Serial: 9600 baud, prints temp_c with one decimal.

const byte SENSOR_PIN = A0;

// Analog reference in millivolts. Change to 3300 on 3.3 V boards.
const long VREF_MV = 5000;
const int ADC_MAX = 1023;

const byte NUM_SAMPLES = 16;
const unsigned long SAMPLE_INTERVAL_MS = 1000;
unsigned long lastSampleMs = 0;

void setup() {
    Serial.begin(9600);
    Serial.println(F("tmp36_temperature: started"));
}

void loop() {
    unsigned long nowMs = millis();
    if (nowMs - lastSampleMs < SAMPLE_INTERVAL_MS) return;
    lastSampleMs = nowMs;

    // Average raw counts to smooth supply and quantization noise.
    unsigned long sum = 0;
    for (byte i = 0; i < NUM_SAMPLES; i++) {
        sum += analogRead(SENSOR_PIN);
        delay(2);
    }
    long raw = (long)((sum + NUM_SAMPLES / 2) / NUM_SAMPLES);

    long millivolts = raw * VREF_MV / ADC_MAX;
    // One decimal place without floating point: tenths of a degree.
    long tenthsC = (millivolts - 500) / 10;

    Serial.print(F("temp_c="));
    Serial.print(tenthsC / 10);
    Serial.print('.');
    long frac = tenthsC % 10;
    if (frac < 0) frac = -frac;
    Serial.println(frac);
}
