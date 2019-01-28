/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test function incrementBCDValue.s
 * Date: Oct 28, 2018
 * Sources of Help: Tutor
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for incrementBCDValues.s
 *
 * Unsigned char incrementBCDValue( unsigned char* BCDdigits, 
 *                                  const unsigned,
 *                                  char resetThreshold, 
 *                                  const unsigned char resetValue)
 * The incrementBCDValue function should increment the value by 1.
 * Purpose: Tests this  implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases as well.
 * times, and others.
 */
void testincrementBCDValue() {

  // Test normal cases
  // case 1
  unsigned char BCDdigits = 0x12;
  unsigned char resetThreshold = 0x60;
  unsigned char resetValue = 0x00;
  unsigned char clock = incrementBCDValue(&BCDdigits, resetThreshold,
                                          resetValue);
  TEST(BCDdigits == 0x13); // increment by 1
  TEST(clock == 0);

  // case 2
  unsigned char BCDdigits2 = 0x00;
  unsigned char resetThreshold2 = 0x99;
  unsigned char resetValue2 = 0x00;
  unsigned char clock2 = incrementBCDValue(&BCDdigits2, resetThreshold2,
                                          resetValue2);
  TEST(BCDdigits2 == 0x01); // increment by 1
  TEST(clock2 == 0);

  // case 3
  unsigned char BCDdigits3 = 0x10;
  unsigned char resetThreshold3 = 0x80;
  unsigned char resetValue3 = 0x01;
  unsigned char clock3 = incrementBCDValue(&BCDdigits3, resetThreshold3,
                                          resetValue3);
  TEST(BCDdigits3 == 0x11); // increment by 1
  TEST(clock3 == 0);

  // case 4
  unsigned char BCDdigits4 = 0x80;
  unsigned char resetThreshold4 = 0x82;
  unsigned char resetValue4 = 0x10;
  unsigned char clock4 = incrementBCDValue(&BCDdigits4, resetThreshold4,
                                          resetValue4);
  TEST(BCDdigits4 == 0x81); // increment by 1
  TEST(clock4 == 0);


  
  // Test edge case
  // case 5
  unsigned char BCDdigits5 = 0x59;
  unsigned char resetThreshold5 = 0x60;
  unsigned char resetValue5 = 0x00;
  unsigned char clock5 = incrementBCDValue(&BCDdigits5, resetThreshold5,
                                          resetValue5);
  TEST(BCDdigits5 == 0x00); // reset
  TEST(clock5 == 1);

  // case 6
  unsigned char BCDdigits6 = 0x00;
  unsigned char resetThreshold6 = 0x01;
  unsigned char resetValue6 = 0x00;
  unsigned char clock6 = incrementBCDValue(&BCDdigits6, resetThreshold6,
                                          resetValue6);
  TEST(BCDdigits6 == 0x00); // reset
  TEST(clock6 == 1);

  // case 7
  unsigned char BCDdigits7 = 0x98;
  unsigned char resetThreshold7 = 0x99;
  unsigned char resetValue7 = 0x98;
  unsigned char clock7 = incrementBCDValue(&BCDdigits7, resetThreshold7,
                                          resetValue7);
  TEST(BCDdigits7 == 0x98); // reset
  TEST(clock7 == 1);

  // case 8
  unsigned char BCDdigits8 = 0x00;
  unsigned char resetThreshold8 = 0x01;
  unsigned char resetValue8 = 0x99;
  unsigned char clock8 = incrementBCDValue(&BCDdigits8, resetThreshold8,
                                          resetValue8);
  TEST(BCDdigits8 == 0x99); // reset
  TEST(clock8 == 1);

}

int main( void ) {

  fprintf(stderr, "Running tests for incrementBCDValue...\n");
  testincrementBCDValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
