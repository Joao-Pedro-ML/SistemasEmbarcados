// These define's must be placed at the beginning before #include "TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         2
#define _TIMERINTERRUPT_LOGLEVEL_     0

#define USE_TIMER_1     true

#if ( defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)  || \
        defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) ||    defined(ARDUINO_AVR_ETHERNET) || \
        defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_BT)   || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO)      || \
        defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FEATHER328P) || \
        defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) || defined(ARDUINO_AVR_PROTRINKET3) || defined(ARDUINO_AVR_PROTRINKET5FTDI) || \
        defined(ARDUINO_AVR_PROTRINKET3FTDI) )
#define USE_TIMER_2     true
#warning Using Timer1, Timer2
#else
#define USE_TIMER_3     true
#warning Using Timer1, Timer3
#endif

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TimerInterrupt.h"
#include "timer.h"

#if !defined(LED_BUILTIN)
#define LED_BUILTIN     13
#endif

//Comu zerial(3, 4);
timer Base_tempo;

#if USE_TIMER_1

void TimerHandler1(unsigned int outputPin = LED_BUILTIN)
{
  //static bool toggle1 = false;

  //timer interrupt toggles pin LED_BUILTIN
  //digitalWrite(outputPin, toggle1);
  //toggle1 = !toggle1;
  //zerial.processa_recebimento();
  
  Base_tempo.decrement_timers();


}

#endif



#if (USE_TIMER_2 || USE_TIMER_3)

void TimerHandler(unsigned int outputPin = LED_BUILTIN)
{

  //zerial.processa_envio();


}

#endif

unsigned int outputPin1 = LED_BUILTIN;
unsigned int outputPin  = A0;

#define USING_LOOP_TEST       false

#define TIMER1_INTERVAL_MS    1
#define TIMER1_FREQUENCY      (float) (1000.0f / TIMER1_INTERVAL_MS)

#define TIMER_INTERVAL_MS     100
#define TIMER_FREQUENCY       (float) (1000.0f / TIMER_INTERVAL_MS)


#if USING_LOOP_TEST
#define TIMER1_DURATION_MS    (10UL * TIMER1_INTERVAL_MS)
#define TIMER_DURATION_MS     (20UL * TIMER_INTERVAL_MS)
#else
#define TIMER1_DURATION_MS    0
#define TIMER_DURATION_MS     0
#endif

void setup()
{

  Base_tempo.timer_pool_init();
  
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin,  OUTPUT);

  Serial.begin(115200);
  //while (!Serial);

  Serial.print(F("\nStarting TimerInterruptTest on "));
  Serial.println(BOARD_TYPE);
  Serial.println(TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

#if USE_TIMER_1

  // Timer0 is used for micros(), millis(), delay(), etc and can't be used
  // Select Timer 1-2 for UNO, 0-5 for MEGA
  // Timer 2 is 8-bit timer, only for higher frequency

  ITimer1.init();

  // Using ATmega328 used in UNO => 16MHz CPU clock ,

  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1, outputPin1, TIMER1_DURATION_MS))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

#endif

#if USE_TIMER_2

  ITimer2.init();

  if (ITimer2.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler, outputPin, TIMER_DURATION_MS))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer2. Select another freq. or timer"));

#elif USE_TIMER_3

  ITimer3.init();

  if (ITimer3.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler, outputPin, TIMER_DURATION_MS))
  {
    Serial.print(F("Starting  ITimer3 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer3. Select another freq. or timer"));

#endif
}
//byte flag_recebe;
byte tempo;
int estado_pisca = 0;

void loop()
{
  switch(estado_pisca){
    case 0:
      tempo = Base_tempo.get_timer();
      Serial.println(tempo);
      Base_tempo.init_timer(tempo, 1000); //1 segundo
      estado_pisca = 1;
      break;
    case 1:
    //Serial.println("fora");
      if(!Base_tempo.check_timer(tempo)){
        //Serial.println("dentro");
        digitalWrite(LED_BUILTIN, HIGH);
        Base_tempo.init_timer(tempo, 1000); //1 segundo
        Serial.println("LED Ligado");
        estado_pisca = 2;
      }
      break;
    case 2: 
      if(!Base_tempo.check_timer(tempo)){
        digitalWrite(LED_BUILTIN, LOW);
        Base_tempo.init_timer(tempo, 1000); //1 segundo
        Serial.println("LED Desligado");
        estado_pisca = 1;
      }
      break;
  }
}
