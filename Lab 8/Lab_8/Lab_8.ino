/*
 * Author: Written By Araam Zaremehrjardi
 * Title: Lab 8 - CPE 301 (11/08/2000)
 * Revision: 1
 * Description: A program to read from a analogue soruce (Photocell) and converts to a 
 * digital signal to be displayed with a serial monitor and 
 * internal LED.
 * Additional Notes: A photo of the circuit can be seen with the file "Lab_8_circuit.jpg."
 */

/*
 * M_LIGHT_THRESHOLD is a macro defined to be used to 
 * set the light threshold to turn on the internel LED.
 * 
 * M_SELECTED_CHANNEL is a macro defined to be used for
 * selecting the specific ADC channel to read from.
 */ 

#define M_LIGHT_THRESHOLD 300
#define M_SELECTED_CHANNEL 2

volatile unsigned char * user_UCSR0A = (unsigned char *) 0x00C0;
volatile unsigned char * user_UCSR0B = (unsigned char *) 0x00C1;
volatile unsigned char * user_UCSR0C = (unsigned char *) 0x00C2;
volatile unsigned int * user_UBRR0 = (unsigned int *) 0x00C4;
volatile unsigned char * user_UDR0 = (unsigned char *) 0x00C6;

volatile unsigned char * user_ADMUX = (unsigned char *) 0x7C;
volatile unsigned char * user_ADCSRA = (unsigned char *) 0x7A;
volatile unsigned char * user_ADCSRB = (unsigned char *) 0x7B;
volatile unsigned int * user_ADCL = (unsigned int *) 0x78;

volatile unsigned char * user_PORTB = (unsigned char *) 0x25;
volatile unsigned char * user_DDRB = (unsigned char *) 0x24;

unsigned char number_array[10] = {'0','1','2','3','4','5','6','7','8','9'};

/*
 * setup() prepares the internel LED to be used as a output 
 * for the program when the light threshold has been 
 * surpassed M_LIGHT_THRESHOLD value.
 * 
 * setup() prepares UART 0 to send values from the microcontroller's
 * ADC to the host device.
 * 
 * setup() prepares the ADC to be in right-adjustment mode, 
 * free-polling mode, and AVCC mode.
 */

void setup() {

  *user_DDRB |= 0b10000000;
  U0_init(9600);
  adc_init();
    
}

/*
 * loop() continuously transmit photocell values to the host device
 * through the use of print_int().
 * -> print_int() prints through parting the value from the selected
 * channel of adc_read() and then prints each character individually.
 * 
 * loop() continuously polling adc_read() to turn on or off the 
 * internel LED when above a set threshold.
 * 
 */

void loop() {

  print_int(adc_read(M_SELECTED_CHANNEL));
  
  if (adc_read(M_SELECTED_CHANNEL) > M_LIGHT_THRESHOLD) {

    *user_PORTB |= 0b10000000;
    
  }
  else {

    *user_PORTB &= 0b01111111;
    
  }
  
}

void adc_init() {

  *user_ADCSRA |= 0b10000000;
  *user_ADCSRA &= 0b11011111;
  *user_ADCSRA &= 0b11110111;
  *user_ADCSRA &= 0b11111000;

  *user_ADCSRB &= 0b11110111;
  *user_ADCSRB &= 0b11111000;

  *user_ADMUX &= 0b01111111;
  *user_ADMUX |= 0b01000000;
  *user_ADMUX &= 0b11011111;
  *user_ADMUX &= 0b11100000;

}

unsigned int adc_read(unsigned char adc_channel) {

  switch (adc_channel) {

    case 0:

      *user_ADMUX &= 0b11100000;
      *user_ADCSRB &= 0b11110111;

    break;

    case 1:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000001;
      *user_ADCSRB &= 0b11110111;

    break;

    case 2:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000010;
      *user_ADCSRB &= 0b11110111;

    break;

    case 3:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000011;
      *user_ADCSRB &= 0b11110111;

    break;

    case 4:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000100;
      *user_ADCSRB &= 0b11110111;


    break;

    case 5:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000101;
      *user_ADCSRB &= 0b11110111;


    break;

    case 6: 

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000110;
      *user_ADCSRB &= 0b11110111;


    break;

    case 7:
    
      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000111;
      *user_ADCSRB &= 0b11110111;

    break;

    case 8:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000000;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;


    break;

    case 9:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000001;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    case 10:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000010;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    case 11:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000011;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    case 12:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000100;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    case 13:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000101;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    case 14:

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000110;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    case 15: 

      *user_ADMUX &= 0b11100000;
      *user_ADMUX |= 0b00000111;
      *user_ADCSRB &= 0b11110111;
      *user_ADCSRB |= 0b00001000;

    break;

    default:

      *user_ADMUX &= 0b11100000;
      *user_ADCSRB &= 0b11110111;

    break;
 
  }

  *user_ADCSRA |= 0b01000000;

  while ((*user_ADCSRA & 0b01000000) != 0);
    
  return *user_ADCL;

}

void print_int(unsigned int value) {

  unsigned char print_value[1023];
  unsigned char * print_value_ptr = print_value;

  unsigned int value_length = 0;

  while (value > 0) {

    unsigned int digit = value % 10;

    *print_value_ptr = number_array[digit];
    
    print_value_ptr++;
    value_length++;
    
    value /= 10;
    
  }
  
  print_value_ptr--;
  
  while (value_length > 0) {

    U0_transmit_data(*print_value_ptr);
    print_value_ptr--;
    value_length--;
     
  }

  U0_transmit_data('\n');
  
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
