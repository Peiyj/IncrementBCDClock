/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test to test printClock.c
 * Date: Oct 28, 2018
 * Sources of help: tutor
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/* 
 * Unit test for printClock.c
 *
 * void printClock( const unsigned long * clock );
 * This function displays the BCD clock based on the passed-in clock array. 
 *
 */

void testprintClock(){

    //////////////////test cases////////////////
    //case 1
    const unsigned long clock = 0x08563761;
    printClock(&clock);
    //case 2
    const unsigned long clock2 = 0x00000070;
    printClock(&clock2);

    //case 2
    const unsigned long clock3 = 0x00000061;
    printClock(&clock3);


    
}



int main (void){
    fprintf(stderr, "Running test for printClock...\n");
    testprintClock();
    fprintf(stderr, "Done running tests!\n");
    return 0;
}


