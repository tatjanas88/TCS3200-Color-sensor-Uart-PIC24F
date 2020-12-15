/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC24FJ256GA106
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "xc.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart2.h"
#include "mcc_generated_files/clock.h"
#include "color.h"


/*
                         Main application
 */
int main(void)
{
    char valueR[10];
    char valueB[10];
    char valueG[10];
    
    int redV, blueV, greenV;
    unsigned int redMin = 300;
    unsigned int redMax = 400;
    unsigned int greenMin = 410;
    unsigned int greenMax = 500;
    unsigned int blueMin = 730;
    unsigned int blueMax = 900;
    int sumB, sumR, sumG;
    
    SYSTEM_Initialize();
     TCS3200_Config();
    //__delay_ms(1000);
    TMR2_init();
    Set_Scaling(Scl100); //postavi se na 2%
    
   


    while (1)
    {
        //LATCbits.LATC13 = PORTBbits.RB12;
        
        //value = Frequency_Count();
        //Send_One_Char('R');
        Measure_Red(valueR);
        __delay_ms(300);
        //treba staviti mali delay za stabilizaciju senora __delayms(200), podesavati preskaler, izmeriti najmanje za bijelu
        //i najvece za crnu, za kalibraciju //min 255, max 0 *(reverse)
        
        ///Send_String_UART2(valueR);
        //Send_One_Char('\n');
       // __delay_ms(300);
        
        //Send_One_Char('G');
        Measure_Green(valueG);
        __delay_ms(300);
        //Send_String_UART2(valueG);
        //Send_One_Char('\n');
        //__delay_ms(300);
        
        //Send_One_Char('B');
        Measure_Blue(valueB);
        __delay_ms(300);
       
        sumB = atoi(valueB);
         if((sumB >= 410) && (sumB <= 600))       
        {
            Send_String_UART2("Green");
            Send_One_Char('\n');
        }
        if((sumB >= 720) && (sumB <= 950))       
        {
            Send_String_UART2("Blue");
            Send_One_Char('\n');
        }
         if((sumB >= 300) && (sumB <= 400))       
        {
            Send_String_UART2("Red");
            Send_One_Char('\n');
        }
        if((sumB<300)|| (sumB>1000))
        {
            Send_String_UART2("Not detectable");
            Send_One_Char('\n');
        }
        
        
        
        Send_One_Char('R');
        Send_String_UART2(valueR);
        Send_One_Char(' ');
        Send_One_Char('G');
        Send_String_UART2(valueG);
        Send_One_Char(' ');
        Send_One_Char('B');
        Send_String_UART2(valueB);
        Send_One_Char('\n');
         
        
       
        
        
    }

  
}
/**
 End of File
*/

