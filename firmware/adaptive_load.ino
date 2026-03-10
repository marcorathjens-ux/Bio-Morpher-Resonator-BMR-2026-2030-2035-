/*
 * Project: Bio-Morpher Resonator (BMR) - Adaptive Load Governance
 * Vector: 2026-2030 (Mechanical Resonance Control)
 * Methodology: Symbiotic Architect (DOI: 10.5281/zenodo.18877077)
 * 
 * Logic: This firmware implements "Self-Sensing Damping". 
 * It measures the induced voltage from the linear generator 
 * and adjusts the electromagnetic resistance (Load) to:
 * 1. Maximize energy harvest at low wind (Low Impedance)
 * 2. Stiffen the structure during storms (High Impedance/Braking)
 */

const int SENSOR_PIN = 34;    // Input from Voltage Divider (Generator Output)
const int PWM_LOAD_PIN = 25;  // Output to MOSFET/IGBT (Load Control)

// Constants for Structural Safety
const float VOLTAGE_THRESHOLD_STORM = 48.0; // Voltage level indicating high-wind stress
const int MAX_DAMPING = 255;                // Full electromagnetic braking

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(PWM_LOAD_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("BMR Adaptive Load Governance System Initialized.");
}

void loop() {
  // 1. Read induced voltage (Self-Sensing)
  int rawValue = analogRead(SENSOR_PIN);
  float currentVoltage = map(rawValue, 0, 4095, 0, 60); // Mapping to 60V Range

  // 2. Adaptive Impedance Logic (Axiom T2.2)
  int targetDamping = 0;

  if (currentVoltage < 5.0) {
    // Low Wind: Minimum resistance to allow easy oscillation start
    targetDamping = 10; 
  } 
  else if (currentVoltage >= 5.0 && currentVoltage < VOLTAGE_THRESHOLD_STORM) {
    // Optimal Harvesting: Linear scaling of load to wind intensity
    targetDamping = map(currentVoltage, 5, VOLTAGE_THRESHOLD_STORM, 50, 150);
  } 
  else {
    // Storm Protection: Maximum damping to "stiffen" the flexure joint
    // This acts as an electromagnetic brake to prevent over-deflection.
    targetDamping = MAX_DAMPING;
    Serial.println("WARNING: Storm Vector Detected. Stiffening Structure.");
  }

  // 3. Apply PWM to the Load Controller
  analogWrite(PWM_LOAD_PIN, targetDamping);

  // 4. Telemetry for AI-Council Audit
  delay(100); // 10Hz Sampling Rate for structural stability
