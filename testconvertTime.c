/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function convertTime.s
 * Date: Oct 28, 2018
 * Sources of Help: worksheet, slides
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for convertTime.s
 *
 * void convertTime( const struct tInfo * tmPtr, unsigned char clock[] );
 *
 * The convertTime function should set the Binary coded decimal values for the
 * time into our clock arrauy.
 *
 * Purpose: Tests our convertTime implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testconvertTime() {

  // Declare our struct tInfo to hold our times
  struct timeInfo myTime;
  struct tm testTime; 

  //////////////////////////Normal cases////////////////////
  // Set the ttimes 
  testTime.tm_hour = 0;
  testTime.tm_min = 0;
  testTime.tm_sec = 0;

  convertTime(&myTime, &testTime);

  TEST(myTime.tm_hour == 0);
  TEST(myTime.tm_min == 0);
  TEST(myTime.tm_sec == 0);
  fprintf(stderr, "Second is : %c\n", myTime.am_pm);

  TEST(myTime.am_pm == 'a');



 
}

int main( void ) {

  fprintf(stderr, "Running tests for convertTime...\n");
  testconvertTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
