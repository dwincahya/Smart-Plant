#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD(0x27,16,2);  //lcd board

int led =2;   //pin 2 pada nodemcupin 4
int pump=0;   //pin 0 pada nodemcupin 3

char auth[] = "oWh2ddICZo0HkKoKB45sAHJ7hEDDV50F"; //ISI TOKEN PADA APLIKASI BLYNX ANDROID
char ssid[] = "OPPO";                                   //NAMA HOTSPOT 
char pass[] = "misbah54321";                            //PASSWORD HOTSPOT

SimpleTimer timer;
WidgetLCD lcd(V1); //lcd android

void sendSensor()
{                         //lcd to android && LCD to board lcd 
  int POT = analogRead(A0); 
  Serial.print(POT);
  lcd.print(0,0,"KEADAAN");   LCD.setCursor(0,0);LCD.print("ADC");LCD.setCursor(4,0);LCD.print(POT);LCD.print(" ");
  lcd.print(0,1,"PUMP");      LCD.setCursor(0,1);LCD.print("PUMP");
  Blynk.virtualWrite(V0, POT);
  
  if (POT>500){
  Serial.println("KERING");//ke serial monitor
  lcd.print(8,0,"KERING");      LCD.setCursor(9,0);LCD.print("KERING");
  lcd.print(5,1,"ON ");         LCD.setCursor(5,1);LCD.print("ON ");
  digitalWrite(pump,LOW);
  for(int x=0; x<=10; x++){     LCD.setCursor(9,1);LCD.print(x);
  lcd.print(9,1,x);delay(500);}
  lcd.clear();                  LCD.clear();
  digitalWrite(pump,HIGH);
  lcd.print(0,0,"AIR MERESAP"); LCD.setCursor(0,0);LCD.print("AIR MERESAP");
  lcd.print(0,1,"    WAIT");    LCD.setCursor(0,1);LCD.print("    WAIT");
  for(int x=9; x>0; x--){       LCD.setCursor(9,1);LCD.print(x);
  lcd.print(9,1,x);delay(500);}
  lcd.clear();                  LCD.clear();
  }
  
  else if (POT>400&&POT<500){
  Serial.println("NORMAL");
  lcd.print(8,0,"NORMAL");      LCD.setCursor(9,0);LCD.print("NORMAL");
  lcd.print(5,1,"OFF");         LCD.setCursor(5,1);LCD.print("OFF");
  digitalWrite(pump,HIGH);
  }
  
  else if (POT<400){
  Serial.println("BASAH");
  lcd.print(8,0,"BASAH ");      LCD.setCursor(9,0);LCD.print("BASAH ");
  lcd.print(5,1,"OFF");         LCD.setCursor(5,1);LCD.print("OFF");
  digitalWrite(pump,HIGH);
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  pinMode(pump,OUTPUT);
  lcd.clear();
  LCD.init();       
  LCD.backlight();
}

void loop()
{
  Blynk.run();
  timer.run();
  delay(100);
}
