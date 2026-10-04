const int NTC_PIN = 34;

const float SERIES_RESISTOR = 22.0;
const float NOMINAL_RESISTANCE = 8.5;
const float NOMINAL_TEMPERATURE = 27.0;
const float BETA_COEFFICIENT = 2800.0;

float filteredADC = -1.0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(NTC_PIN, ADC_11db);
  Serial.println("NTC Temperature Monitor Started");
}

void loop() {
  int rawADC = analogRead(NTC_PIN);

  if (filteredADC < 0) {
    filteredADC = rawADC;
  }

  filteredADC = (0.2 * rawADC) + (0.8 * filteredADC);

  if (filteredADC <= 10.0 || filteredADC >= 4080.0) {
    Serial.println("Hardware Alert: Check sensor circuit.");
    delay(1000);
    return;
  }

  float resistance = SERIES_RESISTOR * (filteredADC / (4095.0 - filteredADC));

  if (resistance <= 0.0) {
    Serial.println("Error: Invalid resistance reading.");
    delay(1000);
    return;
  }

  float steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= BETA_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;

  float tempCelsius = steinhart - 273.15;

  Serial.print("Filtered ADC: ");
  Serial.print(filteredADC, 0);
  Serial.print(" | Resistance: ");
  Serial.print(resistance, 2);
  Serial.print(" ohm | Temperature: ");
  Serial.print(tempCelsius, 2);
  Serial.println(" C");

  delay(250);
}
