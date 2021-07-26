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

//ONEWIRE setup
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Variaveis
int luz = 0, ph = 0;
float temp = 0.0;

//Pinos de entrada e saida

//Pinos LCD
const int RS=8, EN=9, D4=4, D5=5, D6=6, D7=7;
const int buttons=A0;

//Chaves
const int EN_LED=13, EN_BOMBA=1;

//Sensores
const int CONDUCT_PIN=A2, LIGHT_PIN=A4;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int read_buttons(const int buttons_pin){

    /*
    | Botao   | Analog value | Return |
    |---------|--------------|--------|
    | DIREITA |     0-60     |    0   |
    |---------|--------------|--------|
    | CIMA    |    60-200    |    1   |
    |---------|--------------|--------|
    | BAIXO   |   200-400    |    2   |
    |---------|--------------|--------|
    | ESQUERDA|   400-600    |    3   |
    |---------|--------------|--------|
    | SELECT  |   600-800    |    4   |
    |---------|--------------|--------|
    */

    int botao = 0;
    int pressed = analogRead(buttons_pin);

    if (pressed <= 60){

        botao = 0;
    }
    else if (pressed <= 200){

        botao = 1;
    }
    else if (pressed <= 400){

        botao = 2;
    }
    else if (pressed <= 600){

        botao = 3;
    }
    else if (pressed <= 800){
        
        botao = 4;
    }

    return botao;
}

void setup(){

    //LCD config
    lcd.begin(16,2);

    pinMode(EN_LED, OUTPUT);
    pinMode(EN_BOMBA, OUTPUT);

    sensors.begin();
}



void loop(){

    //temperatura
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    delay(1000);

    //luz

}
