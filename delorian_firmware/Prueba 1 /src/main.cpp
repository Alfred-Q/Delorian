#include <Arduino.h>  //Elementos -> sensor ultrasonico, 2 motores DC, puente H.

const int triggerPin = 17; //Pin del sensor ultrasonico
const int echoPin = 5; //Pin del sensor ultrasonico
const int leftmotor_A1 = 34; //Pin del motor izquierdo 
const int leftmotor_A2 = 35; //Pin del motor izquierdo

const int rightmotor_B1 = 32; //Pin del motor izquierdo 
const int rightmotor_B2 = 33; //Pin del motor izquierdo

int motorSpeed = 255; //Velocidad máxima de los motores (0-255) = valor max PWM

void setup() {
    Serial.begin(9600);

    pinMode(triggerPin, OUTPUT); //Pin del sensor ultrasonico como salida
    pinMode(echoPin, INPUT); //Pin del sensor ultrasonico como entrada

    pinMode(leftmotor_A1, OUTPUT);
    pinMode(leftmotor_A2, OUTPUT);
    pinMode(rightmotor_B1, OUTPUT);
    pinMode(rightmotor_B2, OUTPUT); //estos se pueden en PWM??

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

    if(d < 5) { //Si la distancia es menor a 5 cm, el robot retrocede completamente
      motorSpeed /=2;
      //se hace esto para girar derecha hacia atras:
      digitalWrite(rightmotor_B1, 0); //Segun esquema puente H - este va en 0
      digitalWrite(rightmotor_B2, motorSpeed); //Segun esquema puente H - este va en 1

      //se hace esto para girar izquierda hacia atras:
      digitalWrite(leftmotor_A1, 0); //Segun esquema puente H - este va en 0
      digitalWrite(leftmotor_A2, motorSpeed); //Segun esquema puente H - este va en 1
      delay(1000);
      }
    else if (d < 10) { //Si la distancia es menor a 10 cm, el robot gira a la izquierda

      motorSpeed /=2;
      //se hace esto para girar derecha hacia adelanta:
      digitalWrite(rightmotor_B1, motorSpeed); //Segun esquema puente H - este va en 1
      digitalWrite(rightmotor_B2, 0); //Segun esquema puente H - este va en 0

      //se hace esto para girar izquierda hacia atras:
      digitalWrite(leftmotor_A1, 0); //Segun esquema puente H - este va en 0
      digitalWrite(leftmotor_A2, motorSpeed); //Segun esquema puente H - este va en 1
         
        }

    else if(d < 20) { //Si la distancia es menor a 20 cm, el robot gira a la derecha
      //Para girar: una rueda hacia atras y otra hacia adelante

      //se hace esto para girar derecha hacia atras:
      digitalWrite(rightmotor_B1, 0); //Segun esquema puente H - este va en 0
      digitalWrite(rightmotor_B2, motorSpeed); //Segun esquema puente H - este va en 1

      //se hace esto para girar izquierda hacia adelante:
      digitalWrite(leftmotor_A1, motorSpeed); //Segun esquema puente H - este va en 0
      digitalWrite(leftmotor_A2, 0); //Segun esquema puente H - este va en 1
        
      delay(1000); //Esperamos un segundo para que el robot gire

        }
  
     if(d <45) { //Si la distancia es menor a 45 cm, el robot baja su velocidad a 1/5 de la velocidad máxima

        for(int motorSpeed = 255 ; motorSpeed>= 51; motorSpeed -= 5) { //Reducimos la velocidad gradualmente
            if(d<25)
              break;
              
            analogWrite(leftmotor_A1, motorSpeed); //Bajamos la velocidad del motor derecho
            analogWrite(leftmotor_A2, motorSpeed); //Bajamos la velocidad del motor izquierdo
            analogWrite(rightmotor_B1, motorSpeed); //Bajamos la velocidad del motor derecho
            analogWrite(rightmotor_B2, motorSpeed); //Bajamos la velocidad del motor izquierdo
            delay(100); //Esperamos un poco antes de reducir más la velocidad
        }
    }

    else  { //Si la distancia es mayor o igual a 45 cm, el robot avanza
            analogWrite(leftmotor_A1, motorSpeed); //subimos la velocidad del motor derecho
            analogWrite(leftmotor_A2, motorSpeed); //subimos la velocidad del motor izquierdo
            analogWrite(rightmotor_B1, motorSpeed); //subimos la velocidad del motor derecho
            analogWrite(rightmotor_B2, motorSpeed); //subimos la velocidad del motor izquierdo
    }

    delay(1000); //Esperamos un segundo antes de la siguiente medición 

}
