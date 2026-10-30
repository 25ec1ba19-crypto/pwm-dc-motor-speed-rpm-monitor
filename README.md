# PWM Based DC Motor Speed Control and RPM Monitoring System

A system that controls the speed of a DC motor using a PWM signal from an Arduino UNO and shows the live RPM on an I2C LCD. The RPM is measured with an A3144 Hall effect sensor.

## How it works
- A potentiometer sets the desired motor speed.
- The Arduino converts the potentiometer reading into a PWM duty cycle. A higher duty cycle gives the motor more average power, so it spins faster.
- A magnet on the motor shaft passes the A3144 Hall sensor, which gives a pulse each time.
- The Arduino counts the pulses for one second and converts them to RPM.
- The LCD shows the duty cycle (%) and the RPM.

## Components
- Arduino UNO
- DC motor and motor driver
- A3144 Hall effect sensor and magnet
- 16x2 I2C LCD (address 0x27)
- Potentiometer
- External motor power supply

## Pin connections
- Hall sensor (A3144) output: D8
- Potentiometer: A0
- Motor driver PWM input: D11
- LCD SDA / SCL: A4 / A5

## RPM formula
RPM = (pulses in 1 second x 60) / pulses per revolution

## Files
- pwm_motor_rpm.ino: Arduino source code

## Library required
- LiquidCrystal_I2C
