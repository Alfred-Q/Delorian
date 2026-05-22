#include <Arduino.h>

// Pines sensor ultrasónico
const int triggerPin = 5;
const int echoPin = 18;

// Pines motores -  verifica que coincidan con tu cableado
const int leftmotor_A1  = 32;
const int leftmotor_A2  = 33;
const int rightmotor_B1 = 25;
const int rightmotor_B2 = 26;

// Canales PWM
#define CH_LA1  0
#define CH_LA2  1
#define CH_RB1  2
#define CH_RB2  3

int motorSpeedMax = 255;

void setupPWM() {
    ledcAttachPin(leftmotor_A1,  CH_LA1);
    ledcAttachPin(leftmotor_A2,  CH_LA2);
    ledcAttachPin(rightmotor_B1, CH_RB1);
    ledcAttachPin(rightmotor_B2, CH_RB2);
}

void setMotors(int la1, int la2, int rb1, int rb2) {
    ledcWrite(CH_LA1, la1);
    ledcWrite(CH_LA2, la2);
    ledcWrite(CH_RB1, rb1);
    ledcWrite(CH_RB2, rb2);
}

void stopMotors() {
    setMotors(0, 0, 0, 0);
}

long medirDistancia() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    long t = pulseIn(echoPin, HIGH, 30000);
    return t / 59;
}

void setup() {
    Serial.begin(9600);

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);

    setupPWM();
    stopMotors();
}

void loop() {
    long d = medirDistancia();

    Serial.print("Distancia: ");
    Serial.print(d);
    Serial.println(" cm");

    int spd = motorSpeedMax;

    if (d < 5) {
        // Retroceder
        setMotors(0, spd/2, 0, spd/2);
        delay(1000);
        stopMotors();

    } else if (d < 10) {
        // Girar izquierda
        setMotors(0, spd/2, spd/2, 0);
        delay(600);

    } else if (d < 20) {
        // Girar derecha
        setMotors(spd, 0, 0, spd);
        delay(600);

    } else if (d < 45) {
        // Avanzar despacio
        int spdLento = map(d, 20, 45, 80, spd);
        setMotors(spdLento, 0, spdLento, 0);

    } else {
        // Avanzar velocidad máxima
        setMotors(spd, 0, spd, 0);
    }

    delay(200);
}