# ESP32-Temperature-Sensing-with-NTC-22D-9-Power-Thermistor
This project uses an ESP32 and an NTC thermistor to measure temperature in real time. The Arduino code reads analog values, applies exponential smoothing to reduce fluctuations, calculates thermistor resistance, and estimates temperature using the Beta equation.

Features
Real-time temperature monitoring in Celsius (°C).
Exponential moving average filtering for smoother ADC readings.
Thermistor resistance calculation.
Beta-based temperature estimation with baseline calibration.
Open-circuit detection for potential sensor or wiring faults.
Fast measurement updates every 250 ms.
Hardware Requirements
ESP32 development board
NTC 22D -9 thermistor
22 Ω series resistor 
Breadboard and jumper wires
ESP32 

Note: The code assumes a specific thermistor divider arrangement. Ensure the physical wiring matches the resistance equation used in the code.

Calibration Parameters
Parameter	Value	Description
NTC_PIN	GPIO 34	Analog input pin
SERIES_RESISTOR	22.0 Ω	Reference resistor used in calculations
NOMINAL_RESISTANCE	8.5 Ω	Calibrated thermistor resistance at the reference temperature
NOMINAL_TEMPERATURE	27.0 °C	Reference temperature for calibration
BETA_COEFFICIENT	2800.0 K	Thermistor Beta coefficient
Filter factor	0.2	Weight assigned to the latest ADC reading
Sampling delay	250 ms	Delay between measurements

Important: These calibration values are specific to the current setup and must be verified against the actual thermistor and circuit. The 8.5 Ω baseline is unusual for a typical NTC thermistor, so confirm that the resistance units and actual sensor specifications are correct before relying on the temperature readings.

How It Works
ADC Reading: Reads the analog voltage from GPIO 34.
Signal Filtering: Applies exponential smoothing to reduce noise while retaining responsiveness to temperature changes.
Fault Detection: Checks for ADC values close to zero or full scale, which may indicate an open circuit or another wiring problem.
Resistance Calculation: Estimates thermistor resistance using the configured voltage-divider equation.
Temperature Estimation: Applies the Beta equation using the reference resistance, reference temperature, and Beta coefficient.
Serial Output: Displays the filtered ADC value, estimated resistance, and calculated temperature.


Setup Instructions
Install the Arduino IDE and configure the ESP32 board package.
Connect the thermistor circuit to GPIO 34 according to the assumed divider layout.
Open the project source code in Arduino IDE.
Select the correct ESP32 board and COM port.
Upload the code to the ESP32.
Open Serial Monitor and set the baud rate to 115200.
Observe the ADC readings, calculated resistance, and estimated temperature.
Sample Serial Output
Self-Heating Compensated Calibration Engine Active.
Filtered ADC: 1850 | True Resistance: 18.0 Ω | Real-Time Temp: 35.2 °C
Filtered ADC: 1865 | True Resistance: 18.3 Ω | Real-Time Temp: 35.6 °C
