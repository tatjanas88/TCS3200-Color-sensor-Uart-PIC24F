



/**
  Section: Included Files
*/
#include <xc.h>
#include "uart2.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "../color.h"

/**
  Section: UART2 APIs
*/

void UART2_Initialize(void)
{
/**    
     Set the UART2 module to the options selected in the user interface.
     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
*/
    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; RXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    /*U2MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U2STA = 0x00;
    // BaudRate = 9600; Frequency = 8000000 Hz; BRG 207; 
    U2BRG = 0xCF;
    
    U2MODEbits.UARTEN = 1;   // enabling UART ON bit
    U2STAbits.UTXEN = 1;
    //PORTCbits.RC14 = 0;
     */
    IEC0bits.U1TXIE = 0;
    IEC0bits.U1RXIE = 0;

    U1MODEbits.ABAUD = 0;
    U1MODEbits.BRGH = 0;
    U1MODEbits.IREN = 0;
    U1MODEbits.LPBACK = 0;
    U1MODEbits.PDSEL = 0;
    U1MODEbits.PDSEL0 = 0;
    U1MODEbits.PDSEL1 = 0;
    U1MODEbits.RTSMD = 1; //simpplex mode
    U1MODEbits.RXINV = 0;
    U1MODEbits.STSEL = 0;
    U1MODEbits.USIDL = 0;
    U1MODEbits.WAKE = 0;
    U1MODEbits.UEN = 0;
    U1MODEbits.UEN0 = 0;
    U1MODEbits.UEN1 = 0;
    U1BRG = (FCY/((double)16 * BaudRateU1))-1;   //9600 na 16MHz
    
    //STATUS AND CONTROL REGISTAR
    U1STAbits.ADDEN = 0;
    U1STAbits.UTXISEL1=0;   //bit15 interrupt when char is transfered
    U1STAbits.UTXISEL0=0;   //bit13
    U1STAbits.UTXINV=0;     //bit14 no ir encoder transmit polarity inversion
    U1STAbits.UTXBRK=0;     //bit11 no transmit break bit
    U1STAbits.UTXEN=1;      //bit10 TX pin controled by peripheral
    U1STAbits.UTXBF=0;      //bit9 transmit buffer is not full,at least one more characte can be written
    U1STAbits.TRMT=0;       //bit8 transmit register is not empty,transmission is in progress
    U1STAbits.URXISEL1=0;   //bit7 receive interrupt mode selection bits
    U1STAbits.URXISEL0=0;   //bit6
    U1STAbits.ADDEN=0;      //bit5 address detect mode disabled
    U1STAbits.RIDLE=0;      //bit4 receiver is active idle bit read only
    U1STAbits.PERR=0;       //bit3 parity error status bit has not been detected
    U1STAbits.FERR=0;       //bit2 framing error has not been detected
    U1STAbits.OERR=0;       //bit1 receive buffer has not overflowed
    U1STAbits.URXDA=0;
    
    //INTERRUPT PRIORITY
    IPC2bits.U1RXIP = 1; //rx je na IPC2
    IPC3bits.U1TXIP = 0; //tx na IPC3
    //CLEAR FLAGS
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
    
    U1MODEbits.UARTEN = 1;   // enabling UART ON bit
    U1STAbits.UTXEN = 1;
    
     __builtin_write_OSCCONL(OSCCON & 0xbf);
    //za ulaz se koristi RPIN, a izlaz RPOR (SAMO SE NADJE UART1)   
      //RPINR18bits.U1RXR=26;//PIN 43=RG7 RP26 RX za zelenu UART1 //bilo koji od 5:0
      RPOR9bits.RP19R = 3;//PIN 44=RG8=RP19 TX za zelenu UART1 //a koji tacno RP def se u .RPxR.. mora 3, tako pise u tabeli za izlaze
     //lock register 
    __builtin_write_OSCCONL(OSCCON | 0x40); //START OSC.
    

//-----------UART1------------------------        
      //TRISGbits.TRISG7 = 1; //RX UART *(GSM) ovo je ulazni pin rx
      TRISGbits.TRISG8 = 1; //TX UART   izlazni pin tx
}

void Send_One_Char(unsigned char data)
{
    while (!U1STAbits.TRMT); //wait for TXreg to become empty
    U1TXREG=data;
    
}
void Send_String_UART2(char *str)
{
    while(*str)
    {
        Send_One_Char(*str);
		str++;
    }
     
}





/*******************************************************************************

  !!! Deprecated API !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/


