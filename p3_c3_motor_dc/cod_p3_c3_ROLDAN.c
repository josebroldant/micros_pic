
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
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 0         // Brown-out Reset Voltage bits (Maximum setting 4.59V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
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
#define adelante 1
#define atras 0
#define ent1 LATBbits.LATB0
#define ent2 LATBbits.LATB1 
#define C20 200
#define C40 400
#define C60 600
#define C80 800
#define C100 1000

int estado;
int giro;
int ciclo;
void cicloutil(int,int);

void cicloutil(int estadox,int sentido){
    if(sentido==adelante){ // movimiento hacia adelante
        ent2=0;
        switch(estadox){
            case 0: // freno del motor
                ent1=0;
                if(ciclo==0){
                    __delay_us(C100);
                    ciclo=1;
                }else{
                    ciclo=0;
                }
            break;
            case 1: // ciclo 20%
                if(ciclo==0){
                    ent1=1;
                    __delay_us(C20);
                    ciclo=1;
                }else{
                    ent1=0;
                    ciclo=0;
                    __delay_us(C80);
                }
            break;
            case 2: // ciclo 40%
                if(ciclo==0){
                     ent1=1;
                    __delay_us(C40);
                   
                    ciclo=1;
                }else{
                    ciclo=0;
                    ent1=0;
                    __delay_us(C60);
                }
            break;
            case 3: // ciclo 60%
                if(ciclo==0){
                    ent1=1;
                    __delay_us(C60);
                    ciclo=1;
                }else{
                    ciclo=0;
                    ent1=0;
                    __delay_us(C40);
                }
            break;
            case 4: // ciclo 80%
                if(ciclo==0){
                    ent1=1;
                    __delay_us(C80);
                    ciclo=1;
                }else{
                    ciclo=0;
                    ent1=0;
                    __delay_us(C20);
                    
                }
            break;
            case 5: // ciclo 100%
                ent1=1;
                if(ciclo==0){
                    __delay_us(C100);
                    ciclo=1;
                }else{
                    ciclo=0;
                }
            break;
        }
    }else{ // movimiento hacia atras
        ent1=0;
        switch(estadox){
            case 0: // freno del motor
                ent2=0;
                if(ciclo==0){
                    __delay_us(C100);
                    ciclo=1;
                }else{
                    ciclo=0;
                }
            break;
            case 1: // ciclo 20%
                if(ciclo==0){
                     ent2=1;
                    __delay_us(C20);
                   
                    ciclo=1;
                }else{
                    ciclo=0;
                     ent2=0;
                    __delay_us(C80);
                   
                }
            break;
            case 2: // ciclo 40%
                if(ciclo==0){
                    ent2=1;
                    __delay_us(C40);
                    
                    ciclo=1;
                }else{
                    ciclo=0;
                    ent2=0;
                    __delay_us(C60);
                    
                }
            break;
            case 3: // ciclo 60%
                if(ciclo==0){
                    ent2=1;
                    __delay_us(C60);
                 
                    ciclo=1;
                }else{
                    ciclo=0;
                    ent2=0;
                    __delay_us(C40);
                    
                }
            break;
            case 4: // ciclo 80%
                if(ciclo==0){
                    ent2=1;
                    __delay_us(C80);
                    ciclo=1;
                }else{
                    ciclo=0;
                    ent2=0;
                    __delay_us(C20);
                    
                }
            break;
            case 5: // ciclo 100%
                ent2=1;
                if(ciclo==0){
                    __delay_us(C100);
                    ciclo=1;
                }else{
                    ciclo=0;
                }
            break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////


void main(void) {
    OSCCON = 0b01100110;  //CONVIERTE DE 8 A 4 MHz
    TRISA=255;
    TRISB=0;
    ADCON1bits.PCFG0 = 1; //TODO DIGITAL
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;
    estado=0;
    giro=adelante;
    ent1=0;
    ent2=0;
    ciclo=0;
    //while(1){}
    while(1){
        if(PORTAbits.RA6==giro){
            if(giro==adelante){
                cicloutil(estado,0);
            }else{
                cicloutil(estado,1);
            }
        }else{
          giro=PORTAbits.RA6;
          ent1=0;
          ent2=0;
          __delay_ms(20);
          if(giro==adelante){
                cicloutil(estado,0);
          }else{
                cicloutil(estado,1);
          }
        }
    unsigned char caso=PORTA&0b01111111;
    unsigned char var1=0;
    unsigned char varciclo=0;
    unsigned char aux=0;
    for(unsigned int i=0;i<6;i++){
        varciclo=0b00000001<<i;
        aux=varciclo&caso;
        if(var1==0){
	       switch(aux){
	          case 0b00000001: // freno
                  estado=0;
                  var1=1;
	          break;
	          case 0b00000010: // 20%
                 estado=1;
                 var1=1;
	          break;
	          case 0b00000100: // 40%
                 estado=2;
                 var1=1;
	          break;
	          case 0b00001000: // 60%
                 estado=3;
                 var1=1;
	          break;
	          case 0b00010000: // 80%
                 estado=4;
                 var1=1;
	          break;
	          case 0b00100000: // 100%
                 estado=5;
                 var1=1;
	          break;
              default:
                estado=0;
	          break;
	   }
	}
   }
    
 }
 return;
}