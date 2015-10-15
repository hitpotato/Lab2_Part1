
/* 
 * File:   main.c
 * Author: Charles Hoskins
 * Comments:
 * Revision history: 
 */
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "lcd.h"

#define startStop PORTAbits.RA7 
#define resetSwitch PORTDbits.RD6 

typedef enum stateTypeEnum {
    
} stateType;


unsigned int dummy;
volatile stateType state = reset;
volatile stateType nextState;
volatile unsigned int cs = 0;
 

int main(void) {
    
    
    //SYSTEMConfigPerformance(8000000);
    enableInterrupts();
    initTMR();
    initLCD();
    
    while (1) {
    }
        
}
 
