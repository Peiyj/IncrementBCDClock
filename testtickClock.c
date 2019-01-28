/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function tickClock.s
 * Date: Oct 28,2018
 * Sources of Help: tutor
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for setClock.s
 *
 * void setClock( const struct tInfo * tmPtr, unsigned char clock[] );
 *
 * The setClock function should set the Binary coded decimal values for the
 * time into our clock arrauy.
 *
 * Purpose: Tests our setClock implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testtickClock() {

  // normal cases
  unsigned long clock = 0x00000061;
  tickClock(&clock);
  TEST(clock == 0x00000161);

  unsigned long clock1 = 0x00000261;
  tickClock(&clock1);
  TEST(clock1 == 0x00000361); 
    
  unsigned long clock2 = 0x12345661;
  tickClock(&clock2);
  TEST(clock2 == 0x12345761); 

  unsigned long clock3 = 0x12451261;
  tickClock(&clock3);
  TEST(clock3 == 0x12451361); 
  
  unsigned long clock4 = 0x00000270;
  tickClock(&clock4);
  TEST(clock4 == 0x00000370); 
    
  // edgy cases
  unsigned long clock5 = 0x00005961;
  tickClock(&clock5);
  TEST(clock5 == 0x00010061);

  unsigned long clock6 = 0x00595961;
  tickClock(&clock6);
  TEST(clock6 == 0x01000061); 
 
  unsigned long clock7 = 0x12595961;
  tickClock(&clock7);
  TEST(clock7 == 0x01000061); 

  unsigned long clock8 = 0x11595961;
  tickClock(&clock8);
  TEST(clock8 == 0x12000070); 

}

int main( void ) {

  fprintf(stderr, "Running tests for tickClock...\n");
  testtickClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
