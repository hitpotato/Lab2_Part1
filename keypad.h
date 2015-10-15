#ifndef KEYPAD_H
#define KEYPAD_H

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

void scanKeypad();
void initKeypad();
unsigned char getKey();


#endif