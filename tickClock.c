/*
 * Filename: tickClock
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function will increment the clock by one second using
 * incrementBCDValue(). You should start by incrementing the two digits in
 * seconds, then check if you need to increment the digits in minutes, then
 * check if you need to increment the digits in hours. Finally, check whether
 * you need to toggle am/pm
 * Date: Oct, 28, 2018
 * Source of help: tutor, discussiion 3 worksheets, slides
 */
#include <stdio.h>
#include <stdlib.h>

#define ZERO 0
#define ONE 1
#define threshold 0x60
#define twelve 0x12
#define thirteen 0x13
#define am 'a'
#define pm 'p'
#define eight 8
#define sixthteen 16
#define twentyfour 24
#define bit 0xFF
void tickClock( unsigned long * clock )
{
    //extract each byte from the clock
    unsigned long myclock = *clock;
    unsigned long myampm;
    unsigned long mysecond;
    unsigned long myminute;
    unsigned long myhour;
   
    //extract first byte
    myampm=(myclock&bit);
    mysecond=((myclock>>eight)&bit);
    myminute=((myclock>>sixthteen)&bit);
    myhour=((myclock>>twentyfour)&bit);
    //check return for second
    unsigned long secondCheck = incrementBCDValue(&mysecond, threshold,ZERO);
    if(secondCheck == ONE) 
    {
        unsigned long minuteCheck = incrementBCDValue(&myminute, threshold, ZERO);
        if(minuteCheck == ONE)
        {
            unsigned long hourCheck = incrementBCDValue(&myhour,twelve,twelve);
            if(hourCheck == ONE){
                if(myampm == am)
                {
                    myampm = pm;
                }
                else
                {
                    if(myampm == pm){ 
                        myampm = am;
                    }
                }
            }
            //if it is 1 pm
            if(myhour == thirteen){
                myhour = ONE;
            }
        }
    }
    //put the 4 bytes back into *clock
    mysecond = mysecond<<eight;
    myminute = myminute<<sixthteen;
    myhour = myhour<<twentyfour;
    myclock = (myampm)|(mysecond)|(myminute)|(myhour);
    *clock = myclock;
}






