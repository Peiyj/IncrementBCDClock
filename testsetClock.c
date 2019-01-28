/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function setClock.s
 * Date: Oct 28, 2018
 * Sources of Help: worksheet, slides
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
void testsetClock() {

  // Declare our struct tInfo to hold our times
  struct timeInfo time;

  // Set the times to all 0 for a zeroed out test
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;            
  time.am_pm = 'a'; 
  unsigned long clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x00000061); // 'a' has ascii value 0x61

  // // Test some random times
  time.tm_hour = 12;
  time.tm_min = 23;
  time.tm_sec = 50;
  time.am_pm = 'p'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x12235070);
 
  /*
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */

  // normal cases 
  
  time.tm_hour = 9;
  time.tm_min = 1;
  time.tm_sec = 5;
  time.am_pm = 'a'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x09010561);

  time.tm_hour = 12;
  time.tm_min = 01;
  time.tm_sec = 03;
  time.am_pm = 'a'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x12010361);

  time.tm_hour = 02;
  time.tm_min = 11;
  time.tm_sec = 13;
  time.am_pm = 'p'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x02111370);
  
  time.tm_hour = 6;
  time.tm_min = 10;
  time.tm_sec = 22;
  time.am_pm = 'p'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x06102270);

  // edge case
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;            
  time.am_pm = 'p'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x00000070); 

  time.tm_sec = 0;
  time.tm_min = 1;
  time.tm_hour = 0;            
  time.am_pm = 'a'; 
   clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x00010061); 
  
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 1;            
  time.am_pm = 'a'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x01000061); 
}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testsetClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
