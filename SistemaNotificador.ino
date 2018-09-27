
/* INSTITUTO TECNOLOGICO DE LEON
 * INGENIERIA EN SISTEMAS COMPUTACIONALES 
 * SISTEMAS PROGRAMABLES MARTES Y JUEVES 7:00- 8:40
 * SEMESTRE AGOSTO - DICIEMBRE 2018
 * Fecha entrega: 27 DE SEPTIEMBRE DEL 2018
 * NAVA TORRES JUANA CINTHIA LIZBETH
 * 
  Sistema que simula una alarma con luz y sonido cuando una puerta se abre.
   La puerta se abre cuando un iman esta cerca
*/
#include "LowPower.h"  // Se incluye la libreria LowPower que nos sera de ayuda para el bajo consumo de la placa arduino
#define pin_Sensor 2   // Pin digital que alimenta al Sensor 
#define pin_LED    4   // Pin digital que alimenta el LED que simula la alarma al abrir la puerta 
#define pin_Boton  7   // Pin digital que alimenta al Boton que servira para apagar la alarma 
#define pin_Buzzer 9   // Pin digital que alimenta el Buzzer que emite sonido cuando se abre la puerta


  int valor_Sensor = 0; // Creamos una variable donde se guarda el valor que vaya tomando sensor
  int length = 15; // Tamaño del arreglo de beats
  char notes[] = "ccggaagffeeddc "; // Arreglo de caracteres que nos servira para el sonido de la alarma
  int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }; 
  int tempo = 300;

void setup() {
  pinMode(pin_Sensor, INPUT_PULLUP);//Se configura pin como entrada con resistencia pull-up interna para sensor magnetico
  pinMode(pin_Boton, INPUT); // Se configura pin de entrada el pin correspondiente al Boton
  pinMode(pin_LED, OUTPUT);  // Se  configura pin de salida el pin corresponidnete al LED
  pinMode(pin_Buzzer, OUTPUT); // Se  configura pin de salida el pin corresponidnete al Buzzer
  
  attachInterrupt(0, valorSensor, FALLING); // Interrupcion por default el puerto es el 2. En este codigo es el pin
                                            // correspondiente al reed switch y nos dirige al metodo valorSensor
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); // Se hace uso de la libreria de bajo consumo para que arduino entre
                                                       // en modo sleep()
  detachInterrupt(0); // Se rompe con la interrupcion
}

void loop() {
  // Se entra a un ciclo for cuando el valor del sensor es LOW esto significa que un iman activo nuestro sensor
  // y se activa alarma que emite Luz y sonido
  while (valor_Sensor == LOW) {
    //Con el ciclo for generamos una serie de tonos que seran nuestra alarma
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo);
      } else {
        playNote(notes[i], beats[i] * tempo);
      }

      // pausa entre notas
      delay(tempo / 4);
    }
    // Condicion que verifica si el boton para desactivar la alarma este presionado
    // De ser asi, el valor de sensor ccambiara a HIGH lo que nos hara romper con el ciclo
    // Aun cuando el iman siga en nuestro sensor magnetico. De lo contrario el ciclo se rompera 
    // siempre y cuando el iman este lejos. 
    if (digitalRead(pin_Boton) == HIGH) {
      valor_Sensor = HIGH;
    } else {
      valor_Sensor = digitalRead(pin_Sensor);
    }
  }
  // Al salir del ciclo while ponemos nuevamente la placa de arduino en modo sleep para que consuma el minimo
  // de energia
  attachInterrupt(0, valorSensor, FALLING);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}


void valorSensor() {
  // Con este metodo leemos el valor del sensor
  valor_Sensor = digitalRead(pin_Sensor);
}

// Metodo para generar la serie de tonos para alarma 
void playTone(int tone, int duration) {
  //metodo para calcular los tonos de la melodia de la bocina
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(pin_LED, HIGH);//apaga el led
    digitalWrite(pin_Buzzer, HIGH);
    delayMicroseconds(tone);
    digitalWrite(pin_LED, LOW);//enciende el led
    digitalWrite(pin_Buzzer, LOW);
    delayMicroseconds(tone);
  }
}
// Metodo para generar la serie de tonos para alarma 
void playNote(char note, int duration) {
  //metodo para la secuencia de las notas de la melodia
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // toca el tono correspondiente al nombre de la nota
  for (int i = 0; i < 2; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
