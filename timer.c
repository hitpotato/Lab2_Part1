/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "lcd.h"


void initTMR() {
    //Initialize Timer 1 for debounce delay
    TMR1 = 0;// clear TMR1
    PR1 = 6;// Initialize PR1 to 6 (corresponds to 1us)
    T1CONbits.TCKPS = 0; // Initialize pre-scalar to 1
    T1CONbits.TCS = 0; // Use internal peripheral clock
    IFS0bits.T1IF = 0; //lower interrupt flag
   }
void delayUs(unsigned int delay){
    TMR1 = 0; //clear timer 1
    PR1 = 6*delay - 1; // set PR equal to a 1us * delay
    IFS0bits.T1IF = 0; //lower interrupt flag
    T1CONbits.TON =  1;
    while(IFS0bits.T1IF == 0); 
    T1CONbits.TON = 0; //disable timer 1
}
