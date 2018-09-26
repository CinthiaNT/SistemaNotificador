/*
  Sistema que simula una alarma con luz y sonido cuando una puerta se abre.
   La puerta se abre cuando un iman esta cerca
*/

#define pin_Sensor 2   // Pin digital que alimenta al Sensor 
#define pin_LED 4      // Pin digital que alimenta el LED que simula la alarma al abrir la puerta 
#define pin_Buzzer 9   // Pin digital que alimenta el Buzzer que emite sonido cuando se abre la puerta

// Arreglo que contiene las distintas frecuencias que se aproximan a las distintas notas musicales
const int notas[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
// Contador para controlar el ciclo for que recorre el arreglo de notas
const int contador_Notas = 10;

void setup() {
  //Se configura pin como entrada con resistencia pull-up interna para sensor magnetico
  pinMode(pin_Sensor, INPUT_PULLUP);
  // Se  configuran los pines de Led y Buzzer como pines de salida
  pinMode(pin_LED, OUTPUT);
  pinMode(pin_Buzzer, OUTPUT);
}

void loop() {
  //Se guarda en una variable llamada valor lo que nos regrese el pin que alimenta al Sensor magnetico
  int valor = digitalRead(pin_Sensor);
  //Se usa un condicional para activar la alarma
  //Si el sensor magnetico detecta el iman cerca regresa como valor LOW y se procede a encender el LED
  //y Buzzer 
  if (valor == LOW) {
    digitalWrite(pin_LED, HIGH);
    //Ciclo for que recorre el arreglo de notas
    for (int iTono = 0; iTono < contador_Notas; iTono++)
    {
      tone(pin_Buzzer, notas[iTono]);
      delay(1000);
    }
    noTone(pin_Buzzer);
  } else {
    //Cuando el sensor magnetico no detecta un iman entonces el LED y Buzzer permanecen apagados
    digitalWrite(pin_LED, LOW);
    digitalWrite(pin_Buzzer, LOW);
  }
  //Con DelayMicroseconds gastamos consumimos menos energia que al usar delay
  delayMicroseconds(500);
}
