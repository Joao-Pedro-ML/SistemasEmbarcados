#include "timer.h"

timer::timer(){
  
}

//Distribui os timers (retorna uma valor numérico referente ao timer alocado)
byte timer::get_timer(void){
  for(byte i=0; i < _NumTimers; i++){
    if(timer_pool[i].livre){
      timer_pool[i].livre = false;
      return i;
    }
  }
}

//Libera um timer que não vai mais ser utilizado
void timer::free_timer(byte i){
  timer_pool[i].livre=true;
  
}

//Inicia contagem do timer
void timer::init_timer(byte i, unsigned long valor){
  timer_pool[i].value = valor;
}

//Reseta todos os timers e contadores para o zero.
void timer::timer_pool_init(void){
  for(byte i = 0; i < _NumTimers; i++){
    timer_pool[i].value = 0;
    timer_pool[i].livre = true;
  }
}

//Verifica se o timer finalizou (retorna o tempo que resta no timer).
unsigned long timer::check_timer(byte i){
  return timer_pool[i].value;
}

//Decrementa em função de um timer de precisão, o valor mínimo do timer é zero (não possui valores negativos).
void timer::decrement_timers(void){
  for(byte i = 0; i < _NumTimers; i++){
    if(timer_pool[i].livre = false){
      if(timer_pool[i].value > 0){
        timer_pool[i].value--;
      }
    }
  }
}
