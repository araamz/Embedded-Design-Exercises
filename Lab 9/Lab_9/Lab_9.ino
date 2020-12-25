/*
 * Author: Written By Araam Zaremehrjardi
 * Title: Lab 9 - CPE 301 (11/18/2000)
 * Revision: 1
 * Description: A program to read from serial and control the output of a passive buzzer
 * to make a musical piano like program. This uses a timer interrupt to save CPU resources
 * and remove busy-waiting from the program.
 * Additional Notes: A photo of the circuit can be seen within the file "Lab 9.docx."
 */

/*
 * TIMER1_init() is used to set the interrupt register and initialize the status and
 * control registers to begin timing.
 * 
 * U0_init(9600) is used to initialize the USART registers to begin reading from computer
 * input that is used to control the selected frequency of the passive buzzer at 9600 baud.
 */ 

volatile unsigned char * user_TCCR1A = (unsigned char *) 0x80;
volatile unsigned char * user_TCCR1B = (unsigned char *) 0x81;
volatile unsigned char * user_TCCR1C = (unsigned char *) 0x82;
volatile unsigned char * user_TIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  * user_TCNT1 = (unsigned int *) 0x84;

volatile unsigned char * user_UCSR0A = (unsigned char *) 0x00C0;
volatile unsigned char * user_UCSR0B = (unsigned char *) 0x00C1;
volatile unsigned char * user_UCSR0C = (unsigned char *) 0x00C2;
volatile unsigned int * user_UBRR0 = (unsigned int *) 0x00C4;
volatile unsigned char * user_UDR0 = (unsigned char *) 0x00C6;

volatile unsigned char * user_PORTB = (unsigned char *) 0x25;
volatile unsigned char * user_DDRB = (unsigned char *) 0x24;

unsigned char character_array[12] = {'A','a','B','C','c','D','d','E','F','G','g','q'};
unsigned int tick_array[12] = {18181,17167,16194,15296,14440,13628,12820,12139,10680,10204,9626,0};
unsigned int tick_value = 0;

void setup() {
  
  U0_init(9600);
  TIMER1_init();
  *user_DDRB |= 0x40;
  
}

void loop() {
  
  if (U0_receive_complete()) {

    for (unsigned int i = 0; i < 12; i++) {

      if (U0_received_data() == character_array[i]) {

        tick_value = tick_array[i];
        U0_transmit_data(character_array[i]);
        
      } 
      
    }
    
  }

}

ISR(TIMER1_OVF_vect) {
    
    *user_TCCR1B &= 0xF8;
    *user_TCNT1 = (unsigned int) (65536 - tick_value);
    *user_PORTB = tick_value ? ~(*user_PORTB) : 0xBF;
    *user_TCCR1B |= 0x01;
  
}

void TIMER1_init() {

  *user_TIMSK1 |= 0x01;
  *user_TCCR1A &= 0x00;
  *user_TCCR1B |= 0xF9;
  
}

void U0_init(unsigned long U0baud) {

  unsigned long cpu_frequency = 16000000;
  unsigned int transmission_baud = (cpu_frequency / 16 / U0baud - 1);
  
  *user_UCSR0A = 0x20;  
  *user_UCSR0B = 0x18; 
  *user_UCSR0C = 0x06; 
  *user_UBRR0 = transmission_baud;
  
}

unsigned char U0_receive_complete() {
  
  return (*user_UCSR0A & 0x80) >> 7;
  
}

unsigned char U0_received_data() {

  return *user_UDR0;

}

void U0_transmit_data(unsigned char data) {

  while (((*user_UCSR0A & 0x20) >> 5) == 0);
  
  if (((*user_UCSR0A & 0x20) >> 5) == 1) {

    *user_UDR0 = data;

  }

}
