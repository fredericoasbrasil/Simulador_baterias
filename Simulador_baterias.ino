// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int relay = 9;
float tempLimite = 28.0;
int powerSecundario = 8;
int tempSensor = A3;
float voltage = 0.0;
float tensaoMedia = 0.0;
float temp1=0.0,tempSoma=0.0;
int j=0;
int tensaoBateria = A0;
int tensaoBateria_vlr = 0;
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (16,2);
 pinMode(relay,OUTPUT);
 pinMode(powerSecundario,OUTPUT);
 digitalWrite(powerSecundario,HIGH);
}
 
void loop()
{
  while(j<8){
    temp1 = analogRead(tempSensor);
    temp1 = ((5.0*temp1*100.0)/1024.0);
    tempSoma += temp1;  
    tensaoBateria_vlr = analogRead(tensaoBateria);
    voltage = tensaoBateria_vlr * (5.0 / 1023.0);
    tensaoMedia += voltage;
    j++;
  }
  lcd.clear();
  //digitalWrite(relay,HIGH);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(tempSoma/8.0);
  lcd.setCursor(12,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Tensao: ");
  lcd.setCursor(8,1);
  lcd.print(tensaoMedia/8.0);
  lcd.setCursor(13,1);
  lcd.print("V");
  
  if (tempSoma/8.0 > tempLimite){
      digitalWrite(relay, HIGH);
      lcd.setCursor(14,0);
      lcd.print("ON");
  } else { 
      digitalWrite(relay, LOW);
      lcd.setCursor(14,0);
      lcd.print("--");
  }
  
  delay(500);
  tensaoBateria_vlr = 0;
  tensaoMedia = 0.0;
  voltage = 0.0;
  tempSoma = 0.0;
  j=0;
}

