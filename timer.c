/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void initTMR2(){
    TMR2 = 0;// clear TMR2
    T2CONbits.TCKPS = 0; // Initialize pre-scalar to 1
    T2CONbits.TCS = 0; // Use internal peripheral clock
    IPC2bits.T2IP = 7;
    IPC2bits.T2IS = 3;
}

void delayUs(unsigned int delay){

    TMR2 = 0; // clear TMR2
    PR2 = delay*6; // PR2 so that delay equals 1us * delay
    IFS0bits.T2IF = 0; // Lower interrupt flag
    T2CONbits.TON = 1; // Turns on timer
    while(IFS0bits.T2IF == 0); //Delays until TMR1 hits PR
    T2CONbits.TON = 0; // Turns off timer
    
}