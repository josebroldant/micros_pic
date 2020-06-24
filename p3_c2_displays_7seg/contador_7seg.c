// PIC18F2550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_XT // Oscillator Selection bits (Internal oscillator, XT used by USB (INTXT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 4.3V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

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
#define disp1  LATAbits.LATA2
#define disp2  LATAbits.LATA3
#define leds   LATB
#define pul_a   PORTAbits.RA0
#define pul_d   PORTAbits.RA1
//ANODO COMUN LOGICA INVERTIDA, 0 ENCIENDE 1 APAGA
 //0,1,2,3,4,5,6,7,8,9
unsigned char datos[10]={0b10000001,0b11001111,0b10010010,0b10000110,0b11001100,0b10100100,0b10100000,0b10001111,0b10000000,0b10000100};
void main(void) {
   OSCCON = 0b01100110;  //CONVIERTE DE 8 A 4 MHz
   TRISB=0;//PUERTOS B SALIDAS
   //PULSADORES
   TRISAbits.RA0=1;//RA0 ENTRADA
   TRISAbits.RA1=1;//RA1 ENTRADA
   //ENABLES
   TRISAbits.RA2=0;//RA2 SALIDA
   TRISAbits.RA3=0;//RA3 SALIDA
   //RA0 AUMENTA, RA1 DISMINUYE
   //RA2 ENABLE DECENAS, RA3 ENABLE UNIDADES
   ADCON1bits.PCFG0 = 1; //TODO DIGITAL
   ADCON1bits.PCFG1 = 1;
   ADCON1bits.PCFG2 = 1;
   ADCON1bits.PCFG3 = 1;
   int actual=0; // actualizacion de los displays
   int displayx=0; // define que display actualizar
   unsigned int decena,unidad;
   int estado,conteo,segundo;
   estado=0;//verificacio de los pulsadores
   conteo=0; 
   segundo=0;//variable que ,aneja el segundo de pulsado
   decena=0;
   unidad=0;
   // se inicia con los dos display deshabilitados
   disp1=1; 
   disp2=1;
   while(1){
   //VISULAIZACION DINAMICA
     __delay_ms(5);
     actual++;
     if(actual>=3){  // 15ms
        actual=0;
        if(displayx==0){ // actualizar el segundo display
           displayx=1;
           disp1=1; 
           disp2=0;
           leds=datos[unidad];
        }else{  // actualizar el primer dislpay
            displayx=0;
            disp2=1;
            disp1=0; 
            leds=datos[decena];
        }
     }
     /////////////////////////////////777
     //VERIFICACION DE PULSOS E INCREMWNTO 0 DECREMENTO DEL CONTEO
     switch(estado){
         case 0://SI ALGUN PULSADOR SE OPRIMIO
             if(pul_a==1){
                estado=1;
                segundo=0;
             }else{
                if(pul_d==1){
                  estado=3;
                  segundo=0;
                }
             }
         break;
         
         //////////////////////////////////////////////////////////////////////
         //// conteo ascendente  //////////////////////////////////
         case 1: // se verifica que el pulsador arriba esta oprimido
           if(pul_a==1){
             segundo++;
             if(segundo>=4){ // se verifica su ya paso el segundo manteniendo el pulsador oprimido
               segundo=0;
               estado=2; // se pasa a esperar a que se deje de oprimir el pulsador de incremento
               if(conteo>=99){
                  conteo=0;
               }else{
                  conteo++; 
               }
               decena=conteo/10;
               unidad=conteo%10;
             }
           }else{
             estado=0;
             segundo=0;
           }
         break;
         case 2:
            if(pul_a==0){
                estado=0;
            }
         break;
         
         ///////////////////////////////////////////////////////////////////////////////
         ///// conteo descendente
         case 3: // se verifica que el pulsador arriba esta oprimido
           if(pul_d==1){
             segundo++;
             if(segundo>=4){ // se verifica su ya paso el segundo manteniendo el pulsador oprimido
               segundo=0;
               estado=4; // se pasa a esperar a que se deje de oprimir el pulsador de incremento
               if(conteo<=0){
                  conteo=99;
               }else{
                  conteo--; 
               }
               decena=conteo/10;
               unidad=conteo%10;
             }
           }else{
             estado=0;
             segundo=0;
           }
         break;
         case 4:
            if(pul_d==0){
                estado=0;
            }
         break;
     }
     /*for(int i=0;i<10;i++){
      LATB=datos[i];
      RA2=1;
      __delay_ms(15);
      RA3=0;
      __delay_ms(15);
      RA2=0;
      __delay_ms(15);
      RA3=1;
      __delay_ms(15);
      }
      */
      /*int cont_aum=0;
      int cont_dec=9;
      //AUMENTO///////////////////////////////////////
      if(RA0==1){//SE PRODUCE EL PULSO
                __delay_ms(20);//ANTIREBOTE
                while(RA0==1){
                    
                  }
                __delay_ms(20);
		if(RA0==0){//CUANDO LO SUELTE QUE CUENTE
                cont_aum++;   
            }
       		
      LATB=datos[cont_aum];
      RA2=1;
      __delay_us(800);
      RA3=0;
      __delay_us(800);
      RA2=0;
      __delay_us(800);
      RA3=1;
      __delay_us(800);
		
      }
      ////////////////////////////////////////////////
       
      //DECREMENTO///////////////////////////////////
      if(RA1==1){//SE PRODUCE EL PULSO
                __delay_ms(20);//ANTIREBOTE
                while(RA1==1){
                    
                  }
                __delay_ms(20);
		if(RA1==0){//CUANDO LO SUELTE QUE CUENTE
                cont_dec--;    
            }
       		
      LATB=datos[cont_dec];
      RA2=1;
      __delay_ms(4.1);
      RA3=0;
      __delay_ms(4.1);
      RA2=0;
      __delay_ms(4.1);
      RA3=1;
      __delay_ms(4.1);
		
      }
      ////////////////////////////////////////////////
    */   
    }
    
    
    return;
}


