// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

//#include <C:\Program Files (x86)\Microchip\xc32\v1.40\pic32-libs\include\xc.h>
//#include <C:\Program Files (x86)\Microchip\xc32\v1.40\pic32-libs\include\sys\attribs.h>
#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"

typedef enum stateTypeEnum {
    findKey, debouncePress, waitRelease, debounceRelease, display
} stateType;

unsigned int dummy; 
volatile stateType state = findKey;
volatile char key = 'x'; 

int main() 
{
    enableInterrupts();
    initTMR2();
    char key = 'x';
    
    while(1);
    {
       clearLCD();
       InitKeyPad();
       
       switch(state)
       {
           case findKey:
               ScanKeys(); //should i update the key value here?
               break;
           case debouncePress:
               delayUs(5000); //Proper Delay?
               break;
           case debounceRelease:
               delayUs(5000);
               break;
           case display:
               printCharLCD(key);
               break;
       }
    }
    
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    dummy = PORTFbits.RF1;
    dummy = PORTGbits.RG13;
    dummy = PORTDbits.RD6;
    
}