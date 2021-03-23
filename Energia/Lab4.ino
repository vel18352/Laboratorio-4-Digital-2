bool Inicio = false;
byte Jugador1 = 0x01;
byte Jugador2 = 0x01; //Se declaran variabes a usar, contadores del juegador y bandera de inicio

void setup() {
/////////////////////////////////////////////////////////////////
Serial.begin(9600);
/////////////////////////////////////////////////////////////////  
  pinMode(PF_0, INPUT_PULLUP);
  pinMode(PF_4, INPUT_PULLUP);
  pinMode(PA_3, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);      //Se configuran los botones y la led rgb de la tiva C
/////////////////////////////////////////////////////////////////
  pinMode(PD_0, OUTPUT);
  pinMode(PD_1, OUTPUT);
  pinMode(PD_2, OUTPUT);
  pinMode(PD_3, OUTPUT);
  pinMode(PE_1, OUTPUT);
  pinMode(PE_2, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PA_7, OUTPUT);          //Se configuran las salidas donde se mostraran las vueltas del primer jugador
/////////////////////////////////////////////////////////////////
  pinMode(PB_5, OUTPUT);
  pinMode(PB_0, OUTPUT);
  pinMode(PB_1, OUTPUT);
  pinMode(PE_4, OUTPUT);
  pinMode(PE_5, OUTPUT);
  pinMode(PB_4, OUTPUT);
  pinMode(PA_5, OUTPUT);  
  pinMode(PA_6, OUTPUT);        //Se configuran las salidas donde se mostraran las vueltas del segundo jugador
/////////////////////////////////////////////////////////////////
}

void loop() {
  if(digitalRead(PA_3) == LOW)  //Debido a que los botones se encuentran en  pullup cambiaran al ser 0 
  {
    Semaforo();                //Ejecutamos funcion de semaforo de arranque
    Jugador1 = 0x01;
    Jugador2 = 0x01;          //Establecemos valor para primera vuelta
  }
/////////////////////////////////////////////////////////////////  
  if (Inicio == true){        //Al cambiar la bandera de inicio en la funcion de semaforo iniciaran las vueltas
/////////////////////////////////////////////////////////////////
      if (Jugador1 == 0x00)
      {
          Jugador1 = 0x01;
      }
      if (Jugador2 == 0x00)
      {
          Jugador2 = 0x01;
      }                     //Iniciamos a la primera vuelta 
/////////////////////////////////////////////////////////////////      
      if (digitalRead(PF_4) == LOW)   // Cada vez que se presiona un boton de la tiva 
      {
      Jugador1 = Jugador1 << 1;       //Hara un corrimiento de bits hacia la izquierda para indicar la vuelta en la que se encuentra
      }
      if (digitalRead(PF_0) == LOW)
      {
      Jugador2 = Jugador2 << 1;
      }
/////////////////////////////////////////////////////////////////
      if (Jugador1 == 0x80)           //una vez alcanze el ultimo bit 0x80 
      {
        Inicio = false;               //cambia la bandera a false haciendo que finalize la carrera
        digitalWrite(RED_LED, 153);
        digitalWrite(BLUE_LED, 196); //Coloca la led rgb en morado 
      }
      if (Jugador2 == 0x80)
      {
        Inicio = false;
        digitalWrite(BLUE_LED, 255);  //coloca la led rgb en azul
      }
/////////////////////////////////////////////////////////////////      
      Player_1(Jugador1); 
      Player_2(Jugador2);             //Funcion donde se envia los bits corridos para mostrar en las leds
/////////////////////////////////////////////////////////////////
  }
  delay(200);
}

void Semaforo(){                      //Funcion de semaforo
  Inicio = false;                     //Resetea bandera de inicio
  digitalWrite(RED_LED, HIGH);        //Led rgb en rojo
  delay(1000);                        //espera 1 segundo
  digitalWrite(GREEN_LED, HIGH);      //Led rgb en amarillo
  delay(1000);                        //espera 1 segundo
  digitalWrite(RED_LED, LOW);         //apaga la led amarilla y se queda en verde
  delay(1000);                        //espera 1 segundo
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);       //apaga ambas leds
  Inicio = true;                      //Cambia la bandera de inicio y empieza 
}

void Player_1(byte player1){                  //Funcion que mostrara las leds, hay dos funciones para cada jugador
  digitalWrite(PD_0, bitRead(player1,0));     //Enciende la led en el pin seleccionado, y lee del byte enviado
  digitalWrite(PD_1, bitRead(player1,1));     //y se encarga de escribirlo en el pin seleccionado 
  digitalWrite(PD_2, bitRead(player1,2));
  digitalWrite(PD_3, bitRead(player1,3));
  digitalWrite(PE_1, bitRead(player1,4));
  digitalWrite(PE_2, bitRead(player1,5));
  digitalWrite(PE_3, bitRead(player1,6));
  digitalWrite(PA_7, bitRead(player1,7));   
}

void Player_2(byte player2){
  digitalWrite(PB_5, bitRead(player2,0));
  digitalWrite(PB_0, bitRead(player2,1));
  digitalWrite(PB_1, bitRead(player2,2));
  digitalWrite(PE_4, bitRead(player2,3));
  digitalWrite(PE_5, bitRead(player2,4));
  digitalWrite(PB_4, bitRead(player2,5));
  digitalWrite(PA_5, bitRead(player2,6));
  digitalWrite(PA_6, bitRead(player2,7));
}
