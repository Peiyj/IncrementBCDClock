/*
 * Filename: printClock
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function displays the BCD clock based on the passed-in 
 * clock array. For each entry that represents a number in the array (hours
 * minutes, seconds), the upper nibble (4 bits) represents the tens place
 * and the lower nibble represents the ones place of that value. 
 * 
 * Date: Oct, 28, 2018
 * Source of help: tutor, discussiion 3 worksheets, slides
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"

#define am_low 'a'
#define pm_low 'p'
#define am_cap 'A'
#define pm_cap 'P' 
#define bitmask 0xF
#define byte 0xFF
#define rightshiftfour 4
#define rightshifteight 8
#define rightshiftsixthteen 16
#define rightshifttwentyfour 24
#define borderlimit 12
#define linelimit 4

#define mask 0x8
#define newL '\n'

void printClock( const unsigned long * clock ){
    //extract each byte from the clock
    unsigned long myclock = *clock;
    unsigned long myampm;
    unsigned long mysecond;
    unsigned long myminute;
    unsigned long myhour;
    unsigned long tenth_hour;
    unsigned long tenth_min;
    unsigned long tenth_sec;
    unsigned long oneth_hour;
    unsigned long oneth_min;
    unsigned long oneth_sec;
    int i;
  
    //extract first byte
    myampm=(myclock&byte);
    mysecond=((myclock>>rightshifteight)&byte);
    myminute=((myclock>>rightshiftsixthteen)&byte);
    myhour=((myclock>>rightshifttwentyfour)&byte);

    //extract tenth_byte
    tenth_hour = (myhour>>rightshiftfour) &bitmask;
    tenth_min = (myminute>>rightshiftfour) &bitmask;
    tenth_sec = (mysecond>>rightshiftfour) &bitmask;
 
    //extract oneth_byte
    oneth_hour = (myhour) &bitmask;
    oneth_min = (myminute) &bitmask;
    oneth_sec = (mysecond) &bitmask;
    /////////////////////////////////print first line///////////////////////
    for(i = 0; i < borderlimit; i++){
        if(myampm == am_low || myampm == am_cap){
            printChar(am_cap);
        }
        else{
            if(myampm == pm_low || myampm == pm_cap){
                printChar(pm_cap);
            }
        }
    }
    printChar(newL);

    /////////////////////////////print body line////////////////////////////
    for(i = 0; i < linelimit; i++){
        printChar(CHAR_BORDER);
        printChar(CHAR_SPACER);
        //////////////////print tenth_hour/////////////
        if((tenth_hour & (mask>>i)) == 0){
            printChar(CHAR_BIT_UNSET);
        }
        else{
            printChar(CHAR_BIT_SET);
        }
        //////////////////print oneth_hour/////////////
        if((oneth_hour & (mask>>i)) == 0){
            printChar(CHAR_BIT_UNSET);
        }
        else{
            printChar(CHAR_BIT_SET);
        }
        printChar(CHAR_SPACER);
        //////////////////print tenth_minute/////////////
        if((tenth_min & (mask>>i)) == 0){
            printChar(CHAR_BIT_UNSET);
        }
        else{
            printChar(CHAR_BIT_SET);
        }
        //////////////////print oneth_minute/////////////
        if((oneth_min & (mask>>i)) == 0){
            printChar(CHAR_BIT_UNSET);
        }
        else{
            printChar(CHAR_BIT_SET);
        }
        printChar(CHAR_SPACER);
        //////////////////print tenth_second/////////////
        if((tenth_sec & (mask>>i)) == 0){
            printChar(CHAR_BIT_UNSET);
        }
        else{
            printChar(CHAR_BIT_SET);
        }
        //////////////////print oneth_second/////////////
        if((oneth_sec & (mask>>i)) == 0){
            printChar(CHAR_BIT_UNSET);
        }
        else{
            printChar(CHAR_BIT_SET);
        }
        printChar(CHAR_SPACER);
        printChar(CHAR_BORDER);
        printChar(newL);
    }
    //////////////////////////////print digit////////////////////////////
    printChar(CHAR_BORDER);
    printChar(CHAR_SPACER);
    printf("%lx%lx", tenth_hour, oneth_hour);
    printChar(CHAR_SPACER);
    printf("%lx%lx", tenth_min, oneth_min);
    printChar(CHAR_SPACER);
    printf("%lx%lx", tenth_sec, oneth_sec);
    printChar(CHAR_SPACER);
    printChar(CHAR_BORDER);

    printChar(newL);

    ////////////////////////////print final line//////////////////////
    for(i = 0; i < borderlimit; i++){
        if(myampm == am_low || myampm == am_cap){
            printChar(am_cap);
        }
        else{
            if(myampm == pm_low || myampm == pm_cap){
                printChar(pm_cap);
            }
        }
    }
    ////////////////////////print new line///////////////////////
    printChar(newL);
    printChar(newL);
}




 

 
