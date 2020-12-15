/* 
 * File:   color.h
 * Author: Tatjana
 *
 * Created on December 8, 2020, 12:52 PM
 */

#ifndef COLOR_H
#define	COLOR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "mcc_generated_files/clock.h"

enum Colors{Red, Blue, Clear, Green};
enum Scaling{Scl0, Scl2, Scl20, Scl100};

extern char Rvalue[10];
extern char Bvalue[10];
extern char Gvalue[10];
 
 
extern char BlueValue;
extern char GreenValue;

//void __attribute__ ( ( interrupt, no_auto_psv ) ) _T2Interrupt (  );
void __attribute__((__interrupt__, no_auto_psv)) _CNInterrupt(void);
void config_iocb();
void enable_cn();
void disable_cn();

void TCS3200_Config(void);

unsigned long Frequency_Count();

unsigned int Map_RGB(unsigned int,unsigned int,unsigned int);

void TMR2_init(void);

void Set_Filter (uint8_t mode);

void Set_Scaling (uint8_t mode);

unsigned char Take_Reading(void);

void Measure_Red(char* valueR);
void Measure_Blue(char* valueB);
void Measure_Green(char* valueG);    




#ifdef	__cplusplus
}
#endif

#endif	/* COLOR_H */

