#include <xc.h>
#define _XTAL_FREQ 4000000 
#define E       LATAbits.LATA2
#define RS      LATAbits.LATA0

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
int tecla,ciclo;
int clave[4]={1,2,3,4};
int claveinc[4];
int posicion;
void main(void) {
  
  CONF_PUERTOS();
  config_LCD(); 
  ciclo=0;
  /*while(1){}
    */ 
    setlcd(0,0b10000101);//cursor pos
    setlcd(1,'A');
    setlcd(1,'c');
    setlcd(1,'c');
    setlcd(1,'e');
    setlcd(1,'s');
    setlcd(1,'o');
    setlcd(0,0b11000010);//cursor pos
    setlcd(1,'R');
    setlcd(1,'e');
    setlcd(1,'s');
    setlcd(1,'t');
    setlcd(1,'r');
    setlcd(1,'i');
    setlcd(1,'n');
    setlcd(1,'g');
    setlcd(1,'i');
    setlcd(1,'d');
    setlcd(1,'o');
     
    
    
    
    
    
  /*} // final while 1
  
  */
    while(1){
        setlcd(0,0b10000101);//cursor pos
    setlcd(1,'A');
    setlcd(1,'c');
    setlcd(1,'c');
    setlcd(1,'e');
    setlcd(1,'s');
    setlcd(1,'o');
    setlcd(0,0b11000010);//cursor pos
    setlcd(1,'R');
    setlcd(1,'e');
    setlcd(1,'s');
    setlcd(1,'t');
    setlcd(1,'r');
    setlcd(1,'i');
    setlcd(1,'n');
    setlcd(1,'g');
    setlcd(1,'i');
    setlcd(1,'d');
    setlcd(1,'o');
        ciclo=0;
    while(ciclo==0){ // verificacion de pulsacion de *
       tecla=-1;
       while(tecla==-1){}
       if(tecla=='*'){
          ciclo=1;
       }
    }
    
    setlcd(0,0b00000001);//Borrar  display
    __delay_ms(20);
    setlcd(0,0b10000010);//cursor pos
    setlcd(1,'I');
    setlcd(1,'n');
    setlcd(1,'g');
    setlcd(1,'r');
    setlcd(1,'e');
    setlcd(1,'s');
    setlcd(1,'e');
    setlcd(1,' ');
    setlcd(1,'c');
    setlcd(1,'l');
    setlcd(1,'a');
    setlcd(1,'v');
    setlcd(1,'e');
    setlcd(0,0b11000110);//cursor pos
    for(int i=0;i<4;i++){
       claveinc[i]=0;
    }
    posicion=0;
    ciclo=0;
    while(ciclo==0){ // verificacion del ingreso de los 4 digitos
       tecla=-1;
       while(tecla==-1){};
       if(tecla<10){
	  claveinc[posicion]=tecla;
	  posicion++;
	  setlcd(1,tecla+0b00110000); // conversion binario a ASCII
	  if(posicion>=4){
	    ciclo=1;
	  }
	  
       }
    }
   
    
     __delay_ms(800);
    int validar=0; // validacion de la clave de 4 digitos
    for(int i=0;i<4;i++){
       if(claveinc[i]!=clave[i]){
	  validar=1;
	  
       }
    }
    if(validar==1){ // clave incorrecta
      setlcd(0,0b00000001);//Borrar  display
      __delay_ms(20);
       setlcd(0,0b10000101);//cursor pos
      setlcd(1,'A');
      setlcd(1,'c');
      setlcd(1,'c');
      setlcd(1,'e');
      setlcd(1,'s');
      setlcd(1,'o');
      setlcd(0,0b11000100);//cursor pos
      setlcd(1,'D');
      setlcd(1,'e');
      setlcd(1,'n');
      setlcd(1,'e');
      setlcd(1,'g');
      setlcd(1,'a');
      setlcd(1,'d');
      setlcd(1,'o');
      __delay_ms(2000);
      setlcd(0,0b00000001);//Borrar  display
      __delay_ms(20);
    }else{ // clave correcta
      setlcd(0,0b00000001);//Borrar  display
      __delay_ms(20);
       setlcd(0,0b10000101);//cursor pos
      setlcd(1,'C');
      setlcd(1,'l');
      setlcd(1,'a');
      setlcd(1,'v');
      setlcd(1,'e');
      setlcd(0,0b11000100);//cursor pos
      setlcd(1,'C');
      setlcd(1,'o');
      setlcd(1,'r');
      setlcd(1,'r');
      setlcd(1,'e');
      setlcd(1,'c');
      setlcd(1,'t');
      setlcd(1,'a');
      LATCbits.LATC6=1;
      __delay_ms(500);
      setlcd(0,0b00000001);//Borrar  display
      __delay_ms(20);
      LATCbits.LATC6=0; 
    }
   }
    

}//final del main

void setlcd(unsigned char tipo,unsigned char coman){
  unsigned char auxlcd=0;
  if(tipo==0){
    RS=0;
  }else{
    RS=1;
    auxlcd=1;
  }
  __delay_us(20);
  LATB=coman>>4;
  LATA=(coman<<3)|(auxlcd);
  pulso();
}

void pulso(void){//retardo del enable
    E=1;
    __delay_us(4);
    E=0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void interrupt high_priority teclado(){

   if(INTCONbits.RBIF==1){
       // identificacion de la interrupcion de cambio de estado
       INTCONbits.RBIE=0;
      unsigned char puertox=PORTB;
      __delay_us(20);
      puertox=puertox&0b11110000; // usar de RB7 a RB4
      if((puertox&0b00010000)==0){  // verficar fila 1
        LATCbits.LATC0=0;
        LATCbits.LATC1=1;
        LATCbits.LATC2=1;
	 if(PORTBbits.RB4==0){ // se presiona tecla 1
         while(PORTBbits.RB4==0){}
	    tecla=1;
	 }else{
         LATCbits.LATC0=1;
        LATCbits.LATC1=0;
        LATCbits.LATC2=1;
	   if(PORTBbits.RB4==0){ // se presiona tecla 2
           while(PORTBbits.RB4==0){}
	      tecla=2;
	   }else{ // tecla 3
           LATCbits.LATC0=1;
        LATCbits.LATC1=1;
        LATCbits.LATC2=0;
           if(PORTBbits.RB4==0){
               while(PORTBbits.RB4==0){}
	      tecla=3;
           }
	   }  
	 }

      }else{
	 if((puertox&0b00100000)==0){  // verficar fila 2
	    LATCbits.LATC0=1;
	   if(PORTBbits.RB5==1){ // se presiona tecla 4
	      tecla=4;
	   }else{
             LATCbits.LATC1=1;	    
	     if(PORTBbits.RB5==1){ // se presiona tecla 5
	        tecla=5;
	     }else{ // tecla 6
	        LATCbits.LATC2=1;
           if(PORTBbits.RB5==1){
	      tecla=6;
           }
	     }  
	   }
	    
	 }else{
	     
	    if((puertox&0b01000000)==0){  // verficar fila 3
	        LATCbits.LATC0=1;
	        if(PORTBbits.RB6==1){ // se presiona tecla 7
	           tecla=7;
	        }else{
                   LATCbits.LATC1=1;	    
	           if(PORTBbits.RB6==1){ // se presiona tecla 8
	              tecla=8;
	           }else{ // tecla 9
	              LATCbits.LATC2=1;
                    if(PORTBbits.RB6==1){
                        tecla=9;
                    }
	           }  
	       }
	    
	    }else{
	       
	       if((puertox&0b10000000)==0){  // verficar fila 4
	         LATCbits.LATC0=0;
            LATCbits.LATC1=1;
            LATCbits.LATC2=1;
		 if(PORTBbits.RB7==0){ // se presiona tecla *
             while(PORTBbits.RB7==0){}
	             tecla='*';
	         }else{
                   LATCbits.LATC0=1;
                LATCbits.LATC1=0;
                LATCbits.LATC2=1;	    
	           if(PORTBbits.RB7==0){ // se presiona tecla 0
	              tecla=0;
	           }else{ // tecla #
	              LATCbits.LATC0=1;
                LATCbits.LATC1=1;
                LATCbits.LATC2=0;
                    if(PORTBbits.RB7==0){
                        tecla='#';
                    }
	           }  
	         }
		  
	        }
	    
	    
	    }
	    
	    
	    
	 }
      }
      LATCbits.LATC0=0;
      LATCbits.LATC1=0;
      LATCbits.LATC2=0;
      INTCONbits.RBIF=0;
      INTCONbits.RBIE=1;
      
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CONF_PUERTOS(void)
{
			 
   OSCCON=0b01100110;//Convierte los 8Mhz a 4MHz
   TRISB=0b11110000;// filas y D(7..4) LCD 
   TRISC=0;// led y columnas
   TRISA=0;// E, RS, D(3..0) LCD
   ADCON1bits.PCFG0 = 1;//TODO COMO DIGITAL
   ADCON1bits.PCFG1 = 1;
   ADCON1bits.PCFG2 = 1;
   ADCON1bits.PCFG3 = 1;
   
   INTCONbits.GIE=1; // se habilitan interrupciones
   INTCONbits.PEIE=1; //
   RCONbits.IPEN=1;
   INTCONbits.RBIE=1; // interrupciones del puerto B por cambio de estado
   INTCONbits.RBIF=0;
   LATCbits.LATC0=0;
   LATCbits.LATC1=0;
   LATCbits.LATC2=0;
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