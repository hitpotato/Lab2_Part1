
/* 
 * File:   main.c
 * Author: Charles Hoskins
 * Comments:
 * Revision history: 
 */
#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "lcd.h"
#include "keypad.h"


typedef enum stateTypeEnum {
    scanKeys, debouncePress, debounceRelease, wait, checkPass, storePass, addKey,
} stateType;


unsigned int dummy;
volatile stateType state;

unsigned char key;
unsigned char password[5];
unsigned char storedPasswords[5][4];



int numberStored = 0;
int set = 1;
int locked = 0;
 

int main(void) {
    
    enableInterrupts();
    initTMR();
    initLCD();
    initKeypad();
    
    int password_i = 0;
    unsigned char message[] = "Enter";
    while (1) {
        clearLCD();
        printStringLCD(message);
        moveCursorLCD(2,1);
        printStringLCD(password);
        moveCursorLCD(2,1);
        switch(state) {
            case scanKeys: //Scans through Keypad waiting for button press
                strcpy(message, "Enter");
                scanKeypad();
                break;
            case addKey: //Determines what happens after a key has been pressed
                if(password_i <= 3){                 
                    password[password_i] = key;
                    if(password_i < 3) { //Sends PW to be checked against saved ones
                        state = scanKeys;
                        password_i++;
                    }
                    else { //Sends PW to be saved
                        password_i = 0;
                        if(set == 1) state = storePass;
                        else state = checkPass;
                    }
                    
                }
                if(password_i == 2 && password[0] == '*' && password[1] == '*' && locked == 0) { //Puts device into programmable mode
                    password[0] = '\0';
                    set = 1;
                    password_i = 0;
                    state = scanKeys;
                    strcpy(message, "Set Mode");
                } 
                break;
            case checkPass: // Determines if PW is correct
                if(checkValid() == 1) { //Checks if PW is even Valid
                    if(checkPassword() == 1) { //Checks PW against those already saved
                        locked = 0;
                        printStringLCD("Good");
                    }
                    else {
                        printStringLCD("Bad");
                        locked = 1;
                    }
                }
                else printStringLCD("Bad");
                state = scanKeys;
                delaySec();
                delaySec();
                break;
            case storePass: //Saves PW
                if(checkValid() == 1) {
                    printStringLCD("Valid");
                    writeToStorage();
                }
                else printStringLCD("Invalid");
                delaySec();
                delaySec();
                set = 0;
                break;
            case debouncePress: //Debounce
                delayUs(5000);
                state = wait;
                break;
            case debounceRelease: //Debounce
                delayUs(5000);
                state = addKey;
                break;
            case wait: //Determines which key has been pressed
                 key = getKey();
                break;
                
                
        }
    }
        
}
 
int checkPassword() {
    int l;
    int k;
    for(l = 0; l < 4; l++) {
        int v = 1;
        for(k = 0; k < 4; k++) {
            if(storedPasswords[l][k] != password[k]) v = 0;
        }
        if(v == 1) return v;
    }
    return 0;
}
int checkValid() {
    int valid = 1;
    int i;
    for(i=0;i<5;i++) {
        if(password[i] == '#' || password[i] == '*') valid = 0;
    }
    return valid;
}
void writeToStorage() {
    int i;
    if(numberStored < 3) {
        for(i = 0; i < 4; i++) {
            storedPasswords[numberStored][i] = password[i];
        }
        numberStored++;
    }
    locked = 1;
}
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) __CNInterrupt(void){
    if(state == scanKeys) state = debouncePress;
    else if(state == wait) state = debounceRelease;
}
