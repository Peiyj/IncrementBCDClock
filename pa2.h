/*
 * Filename: pa2.h
 * Author: TODO
 * Userid: TODO
 * Description: Constants and function prototypes used in PA2.
 * Date: TODO
 * Sources of Help: Given.
 */

#ifndef PA2_H
#define PA2_H

#include <time.h>  /* For struct timeval and struct timeInfo(below) */
#include <sys/time.h>

/* timeInfo struct used to store time values: sec, min, hr, am_pm flag */
struct timeInfo {
  int tm_sec;
  int tm_min;
  int tm_hour;
  unsigned char am_pm;
};

/* C routines */
unsigned long interpretTime( struct timeInfo * timeInfo, const char * time );
void printClock( const unsigned long * clock );
void chime( const unsigned long * clock );
void tickClock( unsigned long * clock );
int getCurrentTime( struct timeval * tp, void * p );

/* Assembly routines */
void setClock( unsigned long * clock, const struct timeInfo * timeInfo );
void convertTime( struct timeInfo * timeInfo, const struct tm * tm );
unsigned char incrementBCDValue( unsigned char* BCDbits,
                                   const unsigned char resetThreshold ,
                                   const unsigned char resetValue);
long rangeCheck( long num, long min, long max );
void printChar( char c );
long getRemainder( long dividend, long divisor );


/* Min and max number of optional command line args (includes program name) */
#define MIN_ARGS 2
#define MAX_ARGS 3

/* Indicies of optional arguments in argv */
#define HELP_INDEX       1
#define NUM_TICKS_INDEX  1
#define START_TIME_INDEX 2

/* Start time limits */
#define MIN_HR  0
#define MAX_HR  12
#define MIN_MIN 0
#define MAX_MIN 59
#define MIN_SEC 0
#define MAX_SEC 59

/* Default hour value */
#define DEFAULT_HR 12

/* Max values of clock digits */
#define MAX_ONES_SEC 9
#define MAX_TENS_SEC 5
#define MAX_ONES_MIN 9
#define MAX_TENS_MIN 5
#define MAX_ONES_HR 9
#define MAX_TENS_HR 1

#define BASE 10

/* The threshold and reset values to pass into incrementBCDValue*/
#define SEC_THRESHOLD 0x60
#define SEC_RESERT    0x0
#define MIN_THRESHOLD 0x60
#define MIN_RESERT    0x0
#define HR_THRESHOLD  0x13
#define HR_RESET      0x1

/* Number of segments in our time format i.e., hours, minutes, and seconds. */
#define NUM_TIME_SEGMENTS  3
#define NUM_BITS_IN_NIBBLE 4
#define REQ_SEPARATORS     2

/* Number of clock ticks limits */
#define MIN_TICKS 0
#define MAX_TICKS 61
#define DEF_TICKS 7

#define CHAR_BIT_SET    'o'
#define CHAR_BIT_UNSET  '.'
#define CHAR_SPACER     ' '
#define CHAR_SEPARATOR  ':'
#define CHAR_BORDER     '|'
#define CHAR_M          'M'

/* interpretTime errors: Check for the following errors */
#define ERR_TIME_FORMAT   0x1   /* Invalid start time format */
#define ERR_TIME_NUM      0x2   /* Time values (hh/mm/ss) not a valid num */ 
#define ERR_TIME_LIMITS   0x4   /* Time values (hh/mm/ss) out of limits */


/* Values to use for the Extra Credit */
#define MIN_HR_EC  0
#define MAX_HR_EC  23

/* TODO: Add more constants here if necessary. */


#endif /* PA2_H */
