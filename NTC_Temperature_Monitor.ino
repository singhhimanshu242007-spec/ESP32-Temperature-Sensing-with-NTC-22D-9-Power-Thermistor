#include <Arduino.h>
#include <math.h>

// ESP32 NTC Thermistor Temperature Monitor
const int NTC_PIN = 34;

// Calibration parameters
const float SERIES_RESISTOR = 22.0;       // Reference resistor in ohms
const float NOMINAL_RESISTANCE = 8.5;     // Thermistor resistance at reference temperature (ohms)
const float NOMINAL_TEMPERATURE = 27.0;   // Reference temperature in Celsius
const float BETA_COEFFICIENT = 2800.0;    // Thermistor Beta coefficient in Kelvin

// ADC filtering
float filteredADC = -1.0;
const float FILTER_ALPHA = 0.2;

void setup() {
Serial.begin(115200);
analogReadResolution(12);
analogSetPinAttenuation(NTC_PIN, ADC_11db);

Serial.println("ESP32 NTC Temperature Monitor Started");
}

void loop() {
int rawADC = analogRead(NTC_PIN);

// Apply exponential moving average filter
if (filteredADC < 0) {
filteredADC = rawADC;
}

filteredADC = (FILTER_ALPHA * rawADC) +
((1.0 - FILTER_ALPHA) * filteredADC);

// Check for readings near ADC limits
if (filteredADC <= 10.0 || filteredADC >= 4080.0) {
Serial.println("Hardware Alert: Check sensor circuit.");
delay(1000);
return;
}

// Calculate thermistor resistance
// Assumes the thermistor is connected to GND and
// the reference resistor is connected to 3.3V.
float resistance = SERIES_RESISTOR *
(filteredADC / (4095.0 - filteredADC));

if (resistance <= 0.0) {
Serial.println("Error: Invalid resistance reading.");
delay(1000);
return;
}

// Calculate temperature using the Beta equation
float steinhart = resistance / NOMINAL_RESISTANCE;
steinhart = log(steinhart);
steinhart /= BETA_COEFFICIENT;
steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
steinhart = 1.0 / steinhart;

float tempCelsius = steinhart - 273.15;

// Print results
Serial.print("Raw ADC: ");
Serial.print(rawADC);

Serial.print(" | Filtered ADC: ");
Serial.print(filteredADC, 0);

Serial.print(" | Resistance: ");
Serial.print(resistance, 2);
Serial.print(" ohm");

Serial.print(" | Temperature: ");
Serial.print(tempCelsius, 2);
Serial.println(" °C");

delay(250);
}
