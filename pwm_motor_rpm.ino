#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int hallPin = 8;
const int volume_pin = A0;
const int pwm_pin = 11;

const unsigned long sampleTime = 1000;
const int pulsesPerRev = 2;  

int read_ADC;
int duty_cycle;
int duty_cycle_lcd;

unsigned long lastSample = 0;
unsigned long pulseCount = 0;
int rpm = 0;
bool previousHall = HIGH;

void setup() {
  pinMode(hallPin, INPUT_PULLUP);
  pinMode(volume_pin, INPUT);
  pinMode(pwm_pin, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("PWM Motor Speed");
  lcd.setCursor(0, 1);
  lcd.print("RPM Monitoring");
  delay(2000);
  lcd.clear();

  lastSample = millis();
}

void loop() {
  
  bool currentHall = digitalRead(hallPin);

  if (previousHall == HIGH && currentHall == LOW) {
    pulseCount++;
  }
  previousHall = currentHall;

  read_ADC = analogRead(volume_pin);

  duty_cycle = map(read_ADC, 0, 1023, 50, 255);
  duty_cycle_lcd = map(read_ADC, 0, 1023, 0, 100);

  if (duty_cycle_lcd > 0) {
    analogWrite(pwm_pin, duty_cycle);
  } else {
    analogWrite(pwm_pin, 0);
  }

  unsigned long now = millis();

  if (now - lastSample >= sampleTime) {
    rpm = (pulseCount * 60000UL) /
          (sampleTime * pulsesPerRev);

    pulseCount = 0;
    lastSample = now;

    lcd.setCursor(0, 0);
    lcd.print("Duty Cycle: ");
    lcd.print(duty_cycle_lcd);
    lcd.print("%   ");

    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print(rpm);
    lcd.print("        ");
  }
}
