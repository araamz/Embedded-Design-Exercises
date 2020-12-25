/*
 * Author: Written By Araam Zaremehrjardi
 * Title: Lab 6 - CPE 301 (10/19/2000)
 * Revision: 1
 * Description: A program to read data from the AVR via Serial Communication.
 */
 
#define RDA 0x80
#define TBE 0x20

volatile unsigned char * myUCSR0A = (unsigned char * ) 0x00C0;
volatile unsigned char * myUCSR0B = (unsigned char * ) 0x00C1;
volatile unsigned char * myUCSR0C = (unsigned char * ) 0x00C2;
volatile unsigned int * myUBRR0 = (unsigned int * ) 0x00C4;
volatile unsigned char * myUDR0 = (unsigned char * ) 0x00C6;

unsigned char hexadecimal_alphabet[16] = {
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'A',
  'B',
  'C',
  'D',
  'E'
};

/*
 * setup() initializes the baud rate with the function U0init() at 9600 baud.
 * 
 */

void setup() {
  
  U0init(9600);
  
}

/*
 * loop() reads input from the user via U0getchar() and stores it within cs1. 
 * loop() recasts user input from unsigned char to a unsigned input for later decoding.
 * loop() proceeds to decode cs1 with a while loop that divides down the value and 
 * with each character decodes via comparing the value to hexadecimal_alphabet array.
 * loop() finally echos the hexadecimal value via a user defined echo_character() function.
 * 
 */

void loop() {
  
  unsigned char cs1;
  unsigned char character_container[2] = {
    '\0',
    '\0'
  };
  unsigned char * character_container_ptr = character_container;

  while (U0kbhit() == 0) {}; 
  cs1 = (unsigned int) U0getchar(); 

  while (cs1 > 0) {

    unsigned int character = cs1 % 16;

    switch (character) {

    case 0:

      *
      character_container_ptr = hexadecimal_alphabet[0];

    case 1:

      *
      character_container_ptr = hexadecimal_alphabet[1];

      break;

    case 2:

      *
      character_container_ptr = hexadecimal_alphabet[2];

      break;

    case 3:

      *
      character_container_ptr = hexadecimal_alphabet[3];

      break;

    case 4:

      *
      character_container_ptr = hexadecimal_alphabet[4];

      break;

    case 5:

      *
      character_container_ptr = hexadecimal_alphabet[5];

      break;

    case 6:

      *
      character_container_ptr = hexadecimal_alphabet[6];

      break;

    case 7:

      *
      character_container_ptr = hexadecimal_alphabet[7];

      break;

    case 8:

      *
      character_container_ptr = hexadecimal_alphabet[8];

      break;

    case 9:

      *
      character_container_ptr = hexadecimal_alphabet[9];

      break;

    case 10:

      *
      character_container_ptr = hexadecimal_alphabet[10];

      break;

    case 11:

      *
      character_container_ptr = hexadecimal_alphabet[11];

      break;

    case 12:

      *
      character_container_ptr = hexadecimal_alphabet[12];

      break;

    case 13:

      *
      character_container_ptr = hexadecimal_alphabet[13];

      break;

    case 14:

      *
      character_container_ptr = hexadecimal_alphabet[14];

      break;

    case 15:

      *
      character_container_ptr = hexadecimal_alphabet[15];

      break;

    }

    character_container_ptr++;
    cs1 /= 16;

  }

  echo_character(character_container[1], character_container[0]);

}

//
// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. Assume FCPU = 16MHz.
//
void U0init(unsigned long U0baud) {
  //  Students are responsible for understanding
  //  this initialization code for the ATmega2560 USART0
  //  and will be expected to be able to intialize
  //  the USART in differrent modes.
  //
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  // Same as (FCPU / (16 * U0baud)) - 1;
  * myUCSR0A = 0x20; // 
  * myUCSR0B = 0x18; //
  * myUCSR0C = 0x06; // Sets Character size to 8-bit
  * myUBRR0 = tbaud;
}

/*
 * Reads USART0 RDA status bit and returns if status bit is set or not.
 */
unsigned char U0kbhit() {
  return ( * myUCSR0A & RDA) >> 7;
}

/*
 * Read input character from USART0 input buffer.
 */
unsigned char U0getchar() {

  return *myUDR0;

}

/*
 * Waits for USART0 TBE to be set to write the character to transmit buffer. 
 * 
 */
void U0putchar(unsigned char U0pdata) {

  while ((( * myUCSR0A & TBE) >> 5) == 0);
  if ((( * myUCSR0A & TBE) >> 5) == 1) {

    * myUDR0 = U0pdata;

  }

}

void echo_character(unsigned char first_value, unsigned char second_value) {

  U0putchar('0');
  U0putchar('x');
  U0putchar(first_value);
  U0putchar(second_value);
  U0putchar('\n');

}
