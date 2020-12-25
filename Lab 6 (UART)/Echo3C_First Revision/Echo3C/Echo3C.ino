//
// Program to echo serial input characters from
// Putty keyboard back to Putty display.
// This version uses proper pointers.
//
//Written by D. Egbert, Version 1.5, 04/03/2017
//
 #define RDA 0x80
 #define TBE 0x20  
 volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
 volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
 volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
 volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
 volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;
//
// main()
//
void setup()
{
 // initialize the serial port on USART0:
 U0init(9600);
}
void loop()
{
  unsigned char cs1;
  
  while (U0kbhit()==0){}; // wait for RDA = true
  cs1 = (unsigned int) U0getchar();    // read character


    unsigned char hex_value[2];
    unsigned char * hex_value_ptr = hex_value; 
    
    while (cs1 > 0) {
        
        unsigned int digit = cs1 % 16;
        
        if (digit > 9) {
            
            if (digit == 10) {
                
                *hex_value_ptr = 'A';
                
            }
            if (digit == 11) {
                
                *hex_value_ptr = 'B';
                
            }
            if (digit == 12) {
                
                *hex_value_ptr = 'C';
                
            }
            if (digit == 13) {
                
                *hex_value_ptr = 'D';
                
            }
            if (digit == 14) {
                
                *hex_value_ptr = 'E';
                
            }
            if (digit == 15) {
                
                *hex_value_ptr = 'F';
                
            }
            
        }
        else {
            
            *hex_value_ptr = digit + '0';
            
        }
        

        *hex_value_ptr++;
        cs1 /= 16;
        
    }
    --hex_value_ptr;
    unsigned char left_value = *hex_value_ptr;
    --hex_value_ptr;
    unsigned char right_value = *hex_value_ptr;
    unsigned char built_hex_value[5] = {'0','x',left_value,right_value,'\n'};
  // echo character

    for (unsigned char i = 0; i < 5; i++) {
        
        U0putchar(built_hex_value[i]);
        
    }
  

  
}
//
// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. Assume FCPU = 16MHz.
//
void U0init(unsigned long U0baud)
{
//  Students are responsible for understanding
//  this initialization code for the ATmega2560 USART0
//  and will be expected to be able to intialize
//  the USART in differrent modes.
//
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 // Same as (FCPU / (16 * U0baud)) - 1;
 *myUCSR0A = 0x20; // 
 *myUCSR0B = 0x18; //
 *myUCSR0C = 0x06; // Sets Character size to 8-bit
 *myUBRR0  = tbaud;
}
//
// Read USART0 RDA status bit and return non-zero true if set
//
unsigned char U0kbhit()
{
  return (*myUCSR0A & RDA) >> 7;
}
//
// Read input character from USART0 input buffer
//
unsigned char U0getchar()
{

  return *myUDR0;
  
}
//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//
void U0putchar(unsigned char U0pdata)
{

  while (((*myUCSR0A & TBE) >> 5) == 0);
  if (((*myUCSR0A & TBE) >> 5) == 1) {

    *myUDR0 = U0pdata;
    
  }
    
}
