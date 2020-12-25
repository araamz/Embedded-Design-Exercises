  // INITIALZING PK2
  volatile unsigned char* PORT_K = (unsigned char*) 0x108; 
  volatile unsigned char* DDR_K  = (unsigned char*) 0x107; 
  volatile unsigned char* PIN_K  = (unsigned char*) 0x106; 
  // INITIALZING PD0
  volatile unsigned char* PORT_D = (unsigned char*) 0x2B; 
  volatile unsigned char* DDR_D = (unsigned char*) 0x2A;
   // INITIALZING PE3
  volatile unsigned char* PORT_E = (unsigned char*) 0x2E;
  volatile unsigned char* DDR_E = (unsigned char*) 0x2D;
void setup() {
  // ENABLE AS INPUT
  // ENABLE AS PULLUP RESISTOR CONFIG
  *DDR_K |=  0xFB;
  *PORT_K |= 0x04;
  // ENABLE AS OUTPUT
  *DDR_D |= 0x01;
  // ENABLE AS OUTPUT
  *DDR_E |= 0x08;
}
void loop() {
  if (*PIN_K & 0x04) {
    *PORT_D |= 0x01; // 0000 0001
    *PORT_E &= 0xF7;   
  }
  else {
    *PORT_D &= 0xFE;
    *PORT_E |= 0x08; // 0000 1000 
  }
}
