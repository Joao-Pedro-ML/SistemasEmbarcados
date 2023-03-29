#include "sirene.h"

Sirene::Sirene(int porta){
  
  _porta=porta;
  pinMode(porta, OUTPUT);
  timer_sirene.timer_pool_init();
  
}

void Sirene::base_tempo(void){
  timer_sirene.decrement_timers();
}

void Sirene::liga(void){

}

void Sirene::desliga(void){

}

void Sirene::tick(void){

  switch(estado_sirene){
    case 0:
      tempo=timer_sirene.get_timer();
      timer_sirene.init_timer(tempo,1000);
      //Serial.println(tempo);
      estado_sirene = 1;
      break;
    case 1:
      if(!timer_sirene.check_timer(tempo)){
        digitalWrite(_porta, HIGH);
        timer_sirene.init_timer(tempo,1000);
        Serial.println("led ligado");
        estado_sirene = 2;
      }
      break;
    case 2:
      if(!timer_sirene.check_timer(tempo)){
        digitalWrite(_porta, LOW);
        timer_sirene.init_timer(tempo,1000);
        Serial.println("led desligado");
        estado_sirene = 1;
      }
      break;
  }

}