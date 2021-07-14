/*
Este codigo faz parte do projeto da disciplina 0323201 - Laboratório de Projetos em Eletricidade e Eletrônica (2021)
feito pelo grupo:

LUIS HENRIQUE DE ALMEIDA FERNANDES - 11820030
ROGERIO PINHO BORGES DOS SANTOS - 11258190
VINICIUS SCHAEDLER DAMIN - 11258203
*/

#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

//sensor inputs
int pH_in, conduct_in;

//converted values    
float temp = 0, pH = 0, conduct = 0;

//Pinos de entrada e saida

//Pinos LCD
const int RS=12, EN=11, D4=5, D5=4, D6=3, D7=2;

//Chaves
const int EN_LED=6, EN_BOMBA=7;

//Sensores
const int PH_PIN=A1, CONDCUT_PIN=A2;

//Relays
const int RELAY_BOMBA=9, RELAY_LED=8;


LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int led_is_on = 0, bomba_is_on = 0;

void setup(){

    //setup time
    setTime(0, 0, 0, 0, 0, 0);

    //LCD config
    lcd.begin(16,2);

    //configuracao dos pinos
    pinMode(EN_LED, INPUT);
    pinMode(EN_BOMBA, INPUT);

    pinMode(RELAY_BOMBA, OUTPUT);
    pinMode(RELAY_LED, OUTPUT);

    sensors.begin();
}


void loop(){


    led_is_on   = digitalRead(EN_LED);
    bomba_is_on = digitalRead(EN_BOMBA);

    //change light
    if ((hour() >= 6) && (led_is_on)){

        digitalWrite(RELAY_LED, HIGH);
    }
    else{

        digitalWrite(RELAY_LED, LOW);
    }

    //change pump
    if (bomba_is_on){

        digitalWrite(RELAY_BOMBA, HIGH);
    }
    else{

        digitalWrite(RELAY_BOMBA, LOW);
    }


    //read sensor input
    pH_in       = analogRead(PH_PIN);
    conduct_in  = analogRead(CONDCUT_PIN);
    
    //temperatura
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    delay(1000);
   
    //pH
    pH = (float) pH_in/1024.0;

    //update lcd
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print(temp);

    lcd.setCursor(0, 1);
    lcd.print("pH   = ");
    lcd.print(pH);

    delay(5000);
}
