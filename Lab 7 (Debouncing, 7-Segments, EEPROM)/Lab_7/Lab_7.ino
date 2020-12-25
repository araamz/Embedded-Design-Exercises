/*
 * Author: Written By Araam Zaremehrjardi
 * Title: Lab 7 - CPE 301 (10/24/2000)
 * Revision: 1
 * Description: A program to count data from a EEPROM and display on a 7 Segment Display
 */

/*
 * M_EEPROM_MEMORY_ADDRESS is a macro defined to be used to 
 * only store the "counter" variable data at the specific 
 * memory address of 0x0001
 */
#define M_EEPROM_MEMORY_ADDRESS 0x0001

/*
 * character_array is used to decode values given from the variable "counter" 
 * and turn on specifc LED lights for the 7 Segment Display on PORT C;
 */
unsigned char character_array[16] = {0x7F, 0x41, 0xB3, 0xB6, 0xD4, 0xE6, 0xE7, 0x34, 0xF7, 0xF4, 0xF5, 0xC7, 0x63, 0x97, 0xE3, 0xE1};

/*
 * Intialize PORTS to their memory addresses in the microcontroller for later use.
 */
volatile unsigned char* DDR_C = (unsigned char*) 0x27;
volatile unsigned char* PORT_C = (unsigned char*) 0x28;

volatile unsigned char* DDR_K = (unsigned char*) 0x107;
volatile unsigned char* PORT_K = (unsigned char*) 0x108;
volatile unsigned char* PIN_K = (unsigned char*) 0x106;

volatile unsigned int* EEPROM_ADDR_REG = (unsigned int*) 0x41;
volatile unsigned char* EEPROM_DATA_REG = (unsigned char*) 0x40;
volatile unsigned char* EEPROM_CNTRL_REG = (unsigned char*) 0x3F;

/* 
 * setup function Iintializes ports to become input or outputs.
 * specifically PORT C is used for outputting binary "1" or "0"
 * to the 7 Segment Display. PORT K is used for operating input
 * that increments the variable "counter." During setup, counter 
 * and the 7 Segment display is updated on intial boot up to display
 * data last saved to the EEPROM.
 */
void setup(void) {

  Serial.begin(9600);

  *DDR_C = 0xF7;
  
  *DDR_K |= 0xFE;
  *PORT_K |= 0x01; 

  unsigned int counter = 0;
  counter = eeprom_read(M_EEPROM_MEMORY_ADDRESS);
  Serial.println(counter);
 
  display_number(counter);
  
}

/*
 * The loop function with two debouncing techniques is used to read
 * input from the push button implemented on PORT K. This button 
 * on push increments the "counter" variable which then is updated on
 * the EEPROM.
 */
void loop(void) {

  unsigned int counter = eeprom_read(M_EEPROM_MEMORY_ADDRESS);

  if (!(*PIN_K & 0x01)) {
    for (volatile unsigned int index = 0; index < 1300; index++);  
    if (!(*PIN_K & 0x01)) {
      
      Serial.println("increment");
      counter++;
      counter %= 16;
      
      Serial.println(counter);
      eeprom_save(M_EEPROM_MEMORY_ADDRESS, counter);

      while (!(*PIN_K & 0x01));
      
    }

  }
  
  display_number(counter);
  
}

void display_number(unsigned char number) {

  *PORT_C = character_array[number];

}

void eeprom_save(unsigned int address, unsigned char data_input) {

  while(*EEPROM_CNTRL_REG & 0x02);

  *EEPROM_ADDR_REG = address;
  *EEPROM_DATA_REG = data_input;

  *EEPROM_CNTRL_REG |= 0x04;
  *EEPROM_CNTRL_REG &= ~(0x02);
  *EEPROM_CNTRL_REG |= 0x02;

}

unsigned char eeprom_read(unsigned int address) {

  while(*EEPROM_CNTRL_REG & 0x02);

  *EEPROM_ADDR_REG = address;

  *EEPROM_CNTRL_REG |= 0x01;

  return *EEPROM_DATA_REG;

}
