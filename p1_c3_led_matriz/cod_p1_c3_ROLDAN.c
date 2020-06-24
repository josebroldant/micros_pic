


// PIC18F2550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSCIO_EC// Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 0         // Brown-out Reset Voltage bits (Maximum setting 4.59V)
#pragma config VREGEN = ON      // USB Voltage Regulator Enable bit (USB voltage regulator enabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = ON     // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for low-power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
#define filas LATA      
#define columnas LATB
#define fila8 LATCbits.LATC0
#define evento1 PORTCbits.RC1
#define evento2 PORTCbits.RC2
void actualizar(unsigned char);
//logica normal
//unsigned char letraA[8]={0b00000000,0b11111100,0b00010010,0b00010001,0b00010001,0b00010010,0b11111100,0b00000000};
//unsigned char letraB[8]={0b00000000,0b11111111,0b10011001,0b10011001,0b10011001,0b10011001,0b01100110,0b00000000};
//logica invertida
unsigned char letraA[8]={0b11111111,0b00000011,0b11101101,0b11101110,0b11101110,0b11101101,0b00000011,0b11111111};
unsigned char letraB[8]={0b11111111,0b00000000,0b01100110,0b01100110,0b01100110,0b01100110,0b10011001,0b11111111};
int conteo,condesp,desp;//desp para cada cuanto desplazar el dato
int arreglo[8]={0b00000001,0b00000010,0b00000100,0b0000000,0b00001000,0b00010000,0b00100000,0b01000000};
unsigned char puertox;
void main(void)
 {
   ADCON1bits.PCFG0 = 1; //TODO DIGITAL
   ADCON1bits.PCFG1 = 1;
   ADCON1bits.PCFG2 = 1;
   ADCON1bits.PCFG3 = 1;
   OSCCON = 0b01100110;  //CONVIERTE DE 8 A 4 MHz
   TRISA=0; // filas
   TRISB=0; // columnas
   TRISCbits.RC0=0;  // fila8 SALIDA
   TRISCbits.RC1=1; // pulsador 1
   TRISCbits.RC2=1;  // pulsador 2
   conteo=0;
    // inicializacion de la matriz
   filas=0;
   columnas=0;
   fila8=0;
   condesp=0;
   desp=0;
   while(1){  
     __delay_ms(1);
     if(conteo==7){
        conteo=0;
     }else{
        conteo++;
     }
     puertox=PORTC&0b00000110;//pulsos en rc1 y rc2
     switch(puertox){
         case 0: // no se presiona ningun pulsador
            columnas=0;
            filas=0;
            fila8=0; 
         break;
         case 0b00000010: // pulsador evento 1
            actualizar(letraA[conteo]);
         break;
         case 0b00000100: // pulsador evento 2
            actualizar(letraB[conteo]); 
         break;
         case 0b00000110: // pulsador evento 1 y evento dos a las vez
            desp++;
            if(desp>=300){ // cada 300ms se desplaza una posicion
              desp=0;
              condesp--;//muestra la columna hacia atras
              if(condesp<-16){
                condesp=-1;
              }     
            }
            int aux=condesp+conteo; // verificacion de la posicion del desplazamiento
            if((aux>=-16)&&(aux<=-9)){
               aux=aux+16; // se hace la correccion para cargar el valor de la letra A
               actualizar(letraA[aux]);
            }else{
              if((aux>=-8)&&(aux<=-1)){
                aux=aux+8; // se hace la correccion para cargar el valor de la letra B
                actualizar(letraB[aux]);
              }else{
                actualizar(letraA[aux]); // se carga el valor de la letra A
              }
            }
             
         break;
     }  
       
       
   }
 }
void actualizar(unsigned char columnax){
    // visualizacion dinamica
   columnas=0;
   filas=0;
   fila8=0;
   if(conteo==3){//verificacion de la fila 8
     filas=0;
     fila8=1;
   }else{
     filas=arreglo[conteo]; // corrimiento a la izquierda para ubicar el uno en la posicion correcta
     
   }
   columnas=columnax; // se carga el valor de la columna
}