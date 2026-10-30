
const byte POT_PIN       = A0;
const byte MOTOR_PWM_PIN = 9;
const byte HALL_PIN      = 2;

const byte MAGNETS = 1;                 
const unsigned long SAMPLE_MS = 1000;   

volatile unsigned long pulseCount = 0;
unsigned long lastSample = 0;

void countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(HALL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), countPulse, FALLING);
  Serial.println("PWM Motor Control & RPM Monitor");
  Serial.println("Duty(%)\tRPM");
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(MOTOR_PWM_PIN, pwmValue);

  unsigned long now = millis();
  if (now - lastSample >= SAMPLE_MS) {
    noInterrupts();
    unsigned long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    float elapsedSec = (now - lastSample) / 1000.0;
    float rpm = (pulses / (float)MAGNETS) / elapsedSec * 60.0;
    lastSample = now;

    int dutyPercent = map(pwmValue, 0, 255, 0, 100);

    Serial.print(dutyPercent);
    Serial.print("\t");
    Serial.println(rpm, 0);
  }
}
