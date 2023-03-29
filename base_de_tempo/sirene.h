#include "Arduino.h"
#include "timer.h"

class Sirene {

  int estado_sirene;
  byte tempo;
  int _porta;
  timer timer_sirene;

  public:
    Sirene(int);
    void base_tempo(void);
    void tick(void);
    void liga(void);
    void desliga(void);

};