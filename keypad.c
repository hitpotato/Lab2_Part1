#include <xc.h>
#include "keypad.h"

#define row1 LATGbits.LATG0
#define row2 LATDbits.LATD3
#define row3 LATCbits.LATC13
#define row4 LATDbits.LATD12

#define ODC1 ODCGbits.LATG0
#define ODC2 LATDbits.LATD3
#define ODC3 LATCbits.LATC13
#define ODC4 LATDbits.LATD12

#define col1 PORTFbits.RF1
#define col2 PORTGbits.RG13
#define col3 PORTDbits.RD6

void scanKeypad(){
    //Scans through Keypad
    int key = -1;
    
    row1 = 1;
    row2 = 0;
    row3 = 0;
    row4 = 0;
        
    if(col1 == 0) key = 1;
    if(col2 == 0) key = 2;
    if(col3 == 0) key = 3;

    row1 = 0;
    row2 = 1;
    row3 = 0;
    row4 = 0;
        
        
    if(col1 == 0) key = 4;
    if(col2 == 0) key = 5;
    if(col3 == 0) key = 6;
    
    row1 = 0;
    row2 = 0;
    row3 = 1;
    row4 = 0;
        
        
    if(col1 == 0) key = 7;
    if(col2 == 0) key = 8;
    if(col3 == 0) key = 9;  
    
    row1 = 0;
    row2 = 0;
    row3 = 0;
    row4 = 1;
        
        
    if(col1 == 0) key = '*';
    if(col2 == 0) key = 0;
    if(col3 == 0) key = '#';
    
}
void initKeypad() {
    //Keypad Initialization
    TRISGbits.TRISG0 = 0;
    TRISDbits.TRISD3 = 0;
    TRISCbits.TRISC13 = 0;
    TRISDbits.TRISD12 = 0;
    TRISFbits.TRISF1 = 1;
    TRISGbits.TRISG13 = 1;
    TRISDbits.TRISD6 = 1;
    
    ODC1 = 1;
    ODC2 = 1;
    ODC3 = 1;
    ODC4 = 1;
    
    
}
unsigned char getKey() {
    //Returns key that is being pressed
    
    
}
