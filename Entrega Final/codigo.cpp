// Tiempo que se le da al sensor para calibrarse (10-60 segundos)
int calibrationTime = 30;        

// Momento en el que el sensor envía una señal baja (LOW)
long unsigned int lowIn;         

// Cantidad de milisegundos que el sensor debe permanecer en LOW
// antes de asumir que el movimiento terminó
long unsigned int pause = 5000;  

//controla el estado de deteccion
boolean lockLow = true;
//registra el momento en el que el sensor pasa a LOW
boolean takeLowTime;  

int pirPin = 7;    //pin conectado al sensor PIR
int ledPin = 5;    //pin conectado al LED
int Buzzer = 6;    //pin conectado al BUZZER

/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(pirPin, LOW);

  //da el tiempo al sensor de calibrarse
  Serial.print("calibrando sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" calibración finalizada ");
    Serial.println("SENSOR ACTIVO");
    delay(50);
  }

////////////////////////////
//LOOP
void loop(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //El LED visualiza el estado del pin de salida del sensor.
       tone(Buzzer,500);
       if(lockLow){  
         //Se asegura de que esperemos una transición a BAJO antes de que se produzca cualquier otra salida:
         lockLow = false;            
         Serial.println("---");
         Serial.print("movimiento detectado en ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeLowTime = true;
       }
      
      //si el sensor no detecta movimiento
     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  //El LED visualiza el estado del pin de salida del sensor.
       noTone(Buzzer);
       if(takeLowTime){
        lowIn = millis();          //guarda el tiempo de la transición de alto a bajo
        takeLowTime = false;       //evita guardar el tiempo varias veces
        }
       // Si el sensor permanece en LOW más tiempo del definido,
       // se asume que el movimiento terminó
       if(!lockLow && millis() - lowIn > pause){  
           //permite detectar un nuevo movimiento
           lockLow = true;                        
           Serial.print("movimiento termino en ");    
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }