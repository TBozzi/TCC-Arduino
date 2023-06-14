#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C


const int echoPin = 3; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 2; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
 
Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
 
int distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING

int ledgaveta = 3;
int ledmetal = 2;
int ledporta = 12;
int lednivel = 5;
int sensorgaveta = 13;
int sensormetal = 10;
int sensornivel = 11;
int infravermelho = 4;
int helice = 9;
int alcapao = 8;
int sensorporta = 7;
int retornoalcapao = 6;
unsigned long tempoultimodisparo;

void setup() {
 
  Serial.begin(9600);
  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); // Serve para limpar a tela do display
  pinMode(sensorgaveta, INPUT);
  pinMode(sensormetal, INPUT);
  pinMode(sensornivel, INPUT);
  pinMode(infravermelho, INPUT);
  pinMode(retornoalcapao, OUTPUT);
  pinMode(helice, OUTPUT);
  pinMode(alcapao, OUTPUT);
  pinMode(sensorporta, INPUT);
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  pinMode(ledgaveta, OUTPUT);
  pinMode(ledmetal, OUTPUT);
  pinMode(lednivel, OUTPUT);
  pinMode(ledporta, OUTPUT);
  tempoultimodisparo = millis();
}
void loop() {
 
   hcsr04();
  digitalWrite(sensormetal, LOW);
  Serial.println(result);
 digitalWrite(helice, HIGH);
 digitalWrite(alcapao, HIGH);
digitalWrite(lednivel, HIGH);
digitalWrite(ledgaveta, HIGH);
digitalWrite(ledmetal, HIGH);
 digitalWrite(alcapao, HIGH);
digitalWrite(retornoalcapao, HIGH);
   
    if(digitalRead(sensormetal) == HIGH){
 
    lcd.setCursor(0,1);
    lcd.print("Metal detectado");
    digitalWrite(ledmetal, LOW);
    delay(500);
    lcd.clear();
  }
 
    if(digitalRead(sensorgaveta) == HIGH){
   
    lcd.setCursor(0,0);
    lcd.print("Gaveta aberta");
    digitalWrite(ledgaveta, LOW);
    delay(500);
    lcd.clear();
    }
     
        if(distancia <= 40){
   digitalWrite(lednivel, LOW);
    lcd.setCursor(0,0);
    lcd.print("Reservatorio");
    lcd.setCursor(0,1);
    lcd.print("Cheio");
    delay(500);
    lcd.clear();
        }

 if(digitalRead(infravermelho) == HIGH && digitalRead(sensorgaveta) == LOW && distancia >= 40) {
 
    digitalWrite(helice, LOW);
    delay(1500);
    if(digitalRead(sensormetal) == LOW){
      digitalWrite(alcapao, LOW);
      delay(1000);
      digitalWrite(alcapao, HIGH);
      delay(800);      
      digitalWrite(retornoalcapao, LOW);
      delay(1000);
      digitalWrite(retornoalcapao, HIGH);
      delay(3000);
      digitalWrite(helice, HIGH);
     
    }}
}
   
   

void hcsr04(){
  if((millis()-tempoultimodisparo)>3000){
     digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
     delayMicroseconds(10);
       digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
       delayMicroseconds(10);
         digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
       distancia = (ultrasonic.read(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    tempoultimodisparo=millis();
    }
}
