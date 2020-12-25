// Araam Zaremehrjardi
volatile unsigned char *TCC_R1_A = (unsigned char*) 0x80;
volatile unsigned char *TCC_R1_B = (unsigned char*) 0x81;
volatile unsigned char *TCC_R1_C = (unsigned char*) 0x82;
volatile unsigned char *TIMSK_1 = (unsigned char*) 0x6F;
volatile unsigned int  *TCNT_1 = (unsigned int*) 0x84;
volatile unsigned char *TIF_R1 = (unsigned char*) 0x36;

volatile unsigned char *PORT_B = (unsigned char*) 0x25;
volatile unsigned char *PIN_B = (unsigned char*) 0x23;
volatile unsigned char *DDR_B = (unsigned char*) 0x24;

unsigned char character_array[12] = {'A','a','B','C','c','D','d','E','F','G','g','q'};
unsigned int tick_array[12] = {18181,17167,16194,15296,14440,13628,12820,12139,10680,10204,9626,0};
unsigned int tick_value = 0;

void setup() {
  
  Serial.begin(9600);
  *DDR_B |= 0x40;
  
}
void loop() {
  
  unsigned char character_input;
  
  if (Serial.available()) {

    character_input = Serial.read();

    for (unsigned int i = 0; i < 12; i++) {

      if (character_input == character_array[i]) {

        tick_value = tick_array[i];
        Serial.write(character_array[i]);
        
      }
      
    }
    
  }

  *PORT_B |= 0x40;
  custom_delay(tick_value);
  
  *PORT_B &= 0x00;
  custom_delay(tick_value);

}

void custom_delay(unsigned int ticks) {
  
  *TCC_R1_A |= 0x00; 
  *TCC_R1_B &= 0xF8; 
  *TCNT_1 = (unsigned int) (65536 - ticks);
  *TCC_R1_B |= 0xF9;
  while((*TIF_R1 & 0x01)==0); 
  *TCC_R1_B &= 0xF8;            
  *TIF_R1 |= 0x01;

}
