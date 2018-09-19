A#include <Servo.h>
//Define the water pump contorl pins
const int pumpAnodePin =  6;      //pin 6 connect to the anode of the pump
const int pumpCathodePin =  7;   //pin 7 connect to the cathode of the pump

Servo servoH;  // create servo object to control a servo
Servo servoV;  // create servo object to control a servo
int pinHumed1 = 0;  // pin análogo para sensor de humedad 1
int pinHumed2 = 1;  // pin análogo para sensor de humedad 2
int pinHumed3 = 2;  // pin análogo para sensor de humedad 3
int humed1;    // variable para leer el valor del sensor 1
int humed2;    // variable para leer el valor del sensor 2
int humed3;    // variable para leer el valor del sensor 3
int servo_humed1;
int sensor_list[] = {pinHumed1, pinHumed2, pinHumed3};

int umbralInf_1 = 50; // cota inferior de humedad en porcentaje sensor 1
int umbralInf_2 = 50; // cota inferior de humedad en porcentaje sensor 2
int umbralInf_3 = 50; // cota inferior de humedad en porcentaje sensor 

int umbralSup_1 = 70; // cota superior de humedad en porcentaje sensor 1
int umbralSup_2 = 80; // cota superior de humedad en porcentaje sensor 2
int umbralSup_3 = 80; // cota superior de humedad en porcentaje sensor 3
int umbral_humed1;

int angulo_inicial = 0;
int angulo_1 = 30;
int angulo_2 = 90;
int angulo_3 = 150;
int angulo_list[] = {angulo_1, angulo_2, angulo_3};

void setup() 
{  
Serial.begin(9600);
servoH.attach(9);  // relaciona el pin 9 al objeto servo horizontal
servoV.attach(10);  // relaciona el pin 10 al objeto servo vertical 
pinMode(pumpAnodePin, OUTPUT);
pinMode(pumpCathodePin, OUTPUT);
servoH.write(angulo_inicial);
}

void loop() {  
regar(0);
}


void regar(int j){
  while(j < (sizeof(sensor_list)/sizeof(int))){   
    int i=j;
    humed1 = analogRead(sensor_list[i]);            // reads the value of the potentiometer  
    umbral_humed1 = map(humed1, 0, 1023, 100, 0);
    Serial.print("Humedad: ");
    Serial.print(umbral_humed1);
    Serial.print("%");
    delay(1000);
  
    if((umbral_humed1 >= umbralInf_1 && umbral_humed1 <= umbralSup_1) || (umbral_humed1 > umbralSup_1)){
      Serial.print("  (bomba off)");
      i++;
      regar(i);  
      }  
    if(umbral_humed1 < umbralInf_1){
      servoH.write(angulo_list[i]); 
      delay(1000);
      digitalWrite(pumpAnodePin, HIGH);    
      delay(5000); 
      digitalWrite(pumpAnodePin, LOW);
      delay(1000);   
      regar(i);  
    }
  
    servoH.write(angulo_inicial); 
  }
}
