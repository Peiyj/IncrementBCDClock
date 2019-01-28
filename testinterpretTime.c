/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function interpretTime.c
 * Date: Oct 28, 2018
 * Sources of Help: worksheet, slides
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for interpretTime.c
 * unsigned long interpretTime( struct timeInfo* timeInfo, const char * time );
 * This function will parse the time string and populate the tm_sec, tm_min, 
 * tm_hour and am_pm members of the struct timeInfo pointed to by timeInfo. 
 * If there are no errors in this process, you should return 0. Otherwise, 
 * the appropriate error flags/bits should be set in the unsigned long bitmap 
 * to be returned (see pa2.h for the error flags). You should not print any 
 * error messages in this function.
 */

void testinterpretTime() {

  // Declare our struct tInfo to hold our times
  struct timeInfo time;
    

  ///////////////////////////////Normal cases/////////////////////////////
  //Case 1:
  char clock[] = "12:34:56a";
  TEST(interpretTime(&time, clock) == 0);
  TEST((time).tm_hour == 12);
  TEST((time).tm_min == 34);
  TEST((time).tm_sec == 56);
  TEST((time).am_pm == 'a');

  //Case 2:
  char clock2[] = "11:11:11p";
  TEST(interpretTime(&time, clock2) == 0);
  TEST((time).tm_hour == 11);
  TEST((time).tm_min == 11);
  TEST((time).tm_sec == 11);
  TEST((time).am_pm == 'p');

  //Case 3:
  char clock3[] = "01:01:01P";
  TEST(interpretTime(&time, clock3) == 0);
  TEST((time).tm_hour == 1);
  TEST((time).tm_min == 1);
  TEST((time).tm_sec == 1);
  TEST((time).am_pm == 'p');

  //case 4:
  
  char clock4[] = "10:10:10A";
  TEST(interpretTime(&time, clock4) == 0);
  TEST((time).tm_hour == 10);
  TEST((time).tm_min == 10);
  TEST((time).tm_sec == 10);
  TEST((time).am_pm == 'a');

  ///////////////////////////////////edge cases//////////////////////////////
  //case 1:
  char clock5[] = "12::10A";
  TEST(interpretTime(&time, clock5) == 0);
  TEST((time).tm_hour == 12);
  TEST((time).tm_min == 0);
  TEST((time).tm_sec == 10);
  TEST((time).am_pm == 'a');
  
  //case 2:
  char clock6[] = "0:12:10P";
  TEST(interpretTime(&time, clock6) == 0);
  TEST((time).tm_hour == 12);
  TEST((time).tm_min == 12);
  TEST((time).tm_sec == 10);
  TEST((time).am_pm == 'p');

   //case 3:
  char clock7[] = "::P";
  TEST(interpretTime(&time, clock7) == 0);
  TEST((time).tm_hour == 12);
  TEST((time).tm_min == 0);
  TEST((time).tm_sec == 0);
  TEST((time).am_pm == 'p');

  ///////////////////////////////error cases/////////////////////////////

  //case 1: 
  char clock8[] = "03:05:aA";
  TEST(interpretTime(&time, clock8) == 0x1);

  //case 2: 
  char clock9[] = "1z0:16y20";
  TEST(interpretTime(&time, clock9) == 0x1);

  //case 3: 
  char clock10[] = "13:03:05p";
  TEST(interpretTime(&time, clock10) == 0x4);

  //case 4: 
  char clock11[] = "12:::aA";
  TEST(interpretTime(&time, clock11) == 0x1);

  //case 5: 
  char clock12[] = "12:03:05";
  TEST(interpretTime(&time, clock12) == 0x1);

  //case 6: 
  char clock13[] = "1g2:03:05";
  TEST(interpretTime(&time, clock13) == 0x3);

  //case 7: 
  char clock14[] = "12a:66:05";
  TEST(interpretTime(&time, clock14) == 0x7);
  
  //case 8:
  char clock15[] = "13:66:05a";
  TEST(interpretTime(&time, clock15) == 0x4);
  
  //case 9:
  char clock16[] = "12:00:5a0a";
  TEST(interpretTime(&time, clock16) == 0x1);

  //case 10:
  char clock17[] = "123232322:002123123:51231231230a";
  TEST(interpretTime(&time, clock17) == 0x6);

  //case 11:
  char clock18[] = "12:aa:13a";
  TEST(interpretTime(&time, clock18) == 0x2);
  
  //case 12:
  char clock19[] = "12:aa:1323a";
  TEST(interpretTime(&time, clock19) == 0x6);
 
  //case 13:
  char clock20[] = "123123:aa:1323a";
  TEST(interpretTime(&time, clock20) == 0x6);

  //case 14:
  char clock21[] = "aa:66:13a";
  TEST(interpretTime(&time, clock21) == 0x6);

  //case 15:
  char clock22[] = "12::aaa";
  TEST(interpretTime(&time, clock22) == 0x1);

  //case 16:
  char clock23[] = "10:00:00B";
  TEST(interpretTime(&time, clock23) == 0x1);
  fprintf(stderr, "String: %x\n",interpretTime(&time, clock23));

}

int main( void ) {

  fprintf(stderr, "Running tests for interpretTime...\n");
  testinterpretTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}



  



 
