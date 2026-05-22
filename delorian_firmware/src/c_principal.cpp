#include <Arduino.h>

//Elementos -> sensor ultrasonico, 2 motores DC, puente H.

const int triggerPin = 0; //Pin del sensor ultrasonico
const int echoPin = 1; //Pin del sensor ultrasonico

const int rightMotorPin = 7; //Pin del motor derecho
const int leftMotorPin = 6; //Pin del motor izquierdo

int motorSpeed = 255; //Velocidad máxima de los motores (0-255) = valor max PWM

void setup() {
    Serial.begin(9600);
    pinMode(triggerPin, OUTPUT); //Pin del sensor ultrasonico como salida
    pinMode(echoPin, INPUT); //Pin del sensor ultrasonico como entrada

    pinMode(rightMotorPin, OUTPUT);
    pinMode(leftMotorPin, OUTPUT);
    pinMode(motorSpeed, OUTPUT); //Pin de velocidad del motor como salida

    digitalWrite(triggerPin, LOW); //Inicializamos el pin del sensor ultrasonico en bajo
    analogWrite(motorSpeed, 0); //Inicializamos la velocidad de los motores en cero
}

void loop() {

    long t; //Variable para almacenar el tiempo medido por el sensor ultrasonico
    long d; //Variable para almacenar la distancia calculada a partir del tiempo


    digitalWrite(triggerPin, HIGH); //Enviamos un pulso al sensor ultrasonico
    delay(10); //Duración del pulso
    digitalWrite(triggerPin, LOW); //Terminamos el pulso

    t = pulseIn(echoPin, HIGH); //Medimos el tiempo que tarda en recibir el eco
    d = t / 59 ; //Calculamos la distancia en centímetros

    Serial.print("Distancia: ");
    Serial.print(d);
    Serial.println(" cm"); 


    if(d < 20) { //Si la distancia es menor a 20 cm, el robot gira a la derecha

        digitalWrite(rightMotorPin, 0); //Detenemos el motor derecho
        digitalWrite(leftMotorPin, motorSpeed); //Activamos el motor izquierdo

        delay(1000); //Esperamos un segundo para que el robot gire

        if (d < 10) { //Si la distancia sigue siendo menor a 10 cm, el robot gira a la izquierda
             digitalWrite(rightMotorPin, HIGH); //Activamos el motor derecho
             digitalWrite(leftMotorPin, LOW); //Detenemos el motor izquierdo

             delay(1000);
        }
        else if(d < 5) { //Si la distancia sigue siendo menor a 5 cm, el robot para completamente
            //No se si el robot puede dar reversa, pero si se puede lo agregariamos aqui->
            digitalWrite(rightMotorPin, LOW); //Detenemos el motor derecho
            digitalWrite(leftMotorPin, LOW); //Detenemos el motor izquierdo

            delay(1000);
        }

        motorSpeed--;
    }
    
    else if(d <30) { //Si la distancia es menor a 30 cm, el robot baja su velocidad a 1/5 de la velocidad máxima

        for(int i = motorSpeed; i>= 51; i -= 5) { //Reducimos la velocidad gradualmente
            analogWrite(rightMotorPin, i); //Bajamos la velocidad del motor derecho
            analogWrite(leftMotorPin, i); //Bajamos la velocidad del motor izquierdo
            delay(100); //Esperamos un poco antes de reducir más la velocidad
        }
    }
    else { //Si la distancia es mayor o igual a 30 cm, el robot avanza
        analogWrite(rightMotorPin, 255); //Activamos el motor derecho
        analogWrite(leftMotorPin, 255); //Activamos el motor izquierdo
    }

    delay(1000); //Esperamos un segundo antes de la siguiente medición 
}