#include <xc.h>
#define _XTAL_FREQ 4000000 
#define E       LATCbits.LATC2
#define RS      LATCbits.LATC0
#define cola      0  // posicion del caracter de la cola
#define lleno     1  // posicion del caracter de la bateria llena
#define vacio     2  // posicion del caracter de la bateria vacio
#define cabeza    3  // posicion del caracter de la cabeza
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_XT     // Oscillator Selection bits (XT oscillator (XT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 0         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
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
void CONF_PUERTOS(void);
void config_LCD(void);
void setlcd(char,char);
void pulso(void);
void configRAM(void);

void main(void) {
  
  CONF_PUERTOS();
  config_LCD(); 
  configRAM();
  
  // INICIO PARTE 2
  setlcd(0,0b10000000);//cursor pos
  setlcd(1,'B');
  setlcd(1,'a');
  setlcd(1,'t');
  setlcd(1,':');
  setlcd(1,' ');
  
  int bandera=0;
  /*setlcd(1,1);
  setlcd(1,1);
  setlcd(1,2);
  setlcd(1,2);
  setlcd(1,3);
  //poner un asterisco
  */ 
  while(1){
    __delay_ms(600);
    unsigned char puertobat=PORTA&0b00011111;
    unsigned char ciclo=0;
    unsigned char aux=0;
    unsigned char var1=0;
    for(unsigned int i=0;i<5;i++){
        ciclo=0b00000001<<i;
        aux=ciclo&puertobat;
        
	if(var1==0){
	   setlcd(0,0b10000101);//cursor pos 5
	   switch(aux){
	       case 0b00000001: // 0%
               if(bandera!=1){
		  setlcd(1,cola);
		  setlcd(1,vacio);
                  setlcd(1,vacio);
                  setlcd(1,vacio);
	          setlcd(1,vacio);
                  setlcd(1,cabeza);
	          var1=1;
              bandera=1;
               }
	       break;
	       case 0b00000010: // 25%
               if(bandera!=2){
		  setlcd(1,cola);
		  setlcd(1,lleno);
                  setlcd(1,vacio);
                  setlcd(1,vacio);
	          setlcd(1,vacio);
                  setlcd(1,cabeza);
	          var1=1;
              bandera=2;
               }
	       break;
	       case 0b00000100: // 50%
               if(bandera!=3){
		  setlcd(1,cola);
		  setlcd(1,lleno);
                  setlcd(1,lleno);
                  setlcd(1,vacio);
	          setlcd(1,vacio);
                  setlcd(1,cabeza);
	          var1=1;
              bandera=3;
               }
	       break;
	       case 0b00001000: // 75%
               if(bandera!=4){
		  setlcd(1,cola);
		  setlcd(1,lleno);
                  setlcd(1,lleno);
                  setlcd(1,lleno);
	          setlcd(1,vacio);
                  setlcd(1,cabeza);
	          var1=1;
              bandera=4;
               }
	       break;
	       case 0b00010000: // 100%
               if(bandera!=5){
		  setlcd(1,cola);
		  setlcd(1,lleno);
                  setlcd(1,lleno);
                  setlcd(1,lleno);
	          setlcd(1,lleno);
                  setlcd(1,cabeza);
	          var1=1;
              bandera=5;
               }
	       break;
	       default:
               if(bandera!=6){
		  setlcd(1,'-');
		  setlcd(1,'-');
                  setlcd(1,'-');
                  setlcd(1,'-');
	          setlcd(1,'-');
                  setlcd(1,'-');
                  bandera=6;
               }
	       break;
	   }
	}
       
    }
  }//FINAL PARTE 2
  
  
   
  /* 
  //INICIO PARTE 1
  
    setlcd(0,0b10000010);//cursor pos
    setlcd(1,'H');
    setlcd(1,'o');
    setlcd(1,'l');
    setlcd(1,'a');
    setlcd(1,' ');
    
    setlcd(1,'M');
    setlcd(1,'u');
    setlcd(1,'n');
    setlcd(1,'d');
    setlcd(1,'o');
    
    setlcd(0,0b11000010);//cursor to second line
   
    setlcd(1,0b11101110);//letra ñ
    setlcd(1,'a');
    setlcd(1,'m');
    setlcd(1,'e');
    setlcd(1,'-');
    
    setlcd(1,'2');
    setlcd(1,'0');
    setlcd(1,'1');
    setlcd(1,'7');
    while(1){}
    //FINAL PARTE 1
    
    
*/
}//final del main

void configRAM(){
   setlcd(0,0b01000000);//posicion 0 CGRAM
    // primer caracter cola de el medidor
   setlcd(1,0b00000011);
   setlcd(1,0b00000110);
   setlcd(1,0b00000110);
   setlcd(1,0b00000110);
   setlcd(1,0b00000110);
   setlcd(1,0b00000110);
   setlcd(1,0b00000011);
   setlcd(1,0b00000000);
   
   // segundo caracter bateria llena
   setlcd(1,0b00011111);
   setlcd(1,0b00000000);
   setlcd(1,0b00011110);
   setlcd(1,0b00011110);
   setlcd(1,0b00011110);
   setlcd(1,0b00000000);
   setlcd(1,0b00011111);
   setlcd(1,0b00000000);
   
   //tercer caracter bateria vacia
   setlcd(1,0b00011111);
   setlcd(1,0b00000000);
   setlcd(1,0b00000000);
   setlcd(1,0b00000000);
   setlcd(1,0b00000000);
   setlcd(1,0b00000000);
   setlcd(1,0b00011111);
   setlcd(1,0b00000000);
   
   // cuarto caracter cabeza de la bateria
   setlcd(1,0b00010000);
   setlcd(1,0b00011100);
   setlcd(1,0b00010010);
   setlcd(1,0b00010010);
   setlcd(1,0b00010010);
   setlcd(1,0b00011100);
   setlcd(1,0b00010000);
   setlcd(1,0b00000000);
   setlcd(0,0b10000000);
   
   
   
}

void setlcd(unsigned char tipo,unsigned char coman){
  if(tipo==0){
    RS=0;
  }else{
    RS=1;
  }
  __delay_us(20);
  LATB=coman;
  pulso();
 
}

void pulso(void){//retardo del enable
    E=1;
    __delay_us(4);
    E=0;
}
void CONF_PUERTOS(void)
{
			 
   OSCCON=0b01100110;//Convierte los 8Mhz a 4MHz
   TRISB=0;//data
   TRISC=0;//rs y e
   TRISA=0b11111111;//pulsadores
   ADCON1bits.PCFG0 = 1;//TODO COMO DIGITAL
   ADCON1bits.PCFG1 = 1;
   ADCON1bits.PCFG2 = 1;
   ADCON1bits.PCFG3 = 1;
   
    
}


void config_LCD(void){
  E=0;
  __delay_ms(20);
  setlcd(0,0b00111000);//Comando  de  bus  de  8  bits,matriz  5x8
                       //y  2  lineas  habilitadas
  setlcd(0,0b00000110);//Se  incrementa  la  ram  y  se  mueve cursor
  setlcd(0,0b00001100);//display  on,  cursor  off  y  cursor  estatico
  setlcd(0,0b00000001);//Borrar  display
  __delay_ms(20);
  setlcd(0,0b10000000);//Cursor  a  la  posicion  0,  linea 1
  __delay_ms(20);
  
}



