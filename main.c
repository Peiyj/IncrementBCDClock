/*
 * Filename: main.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: The main function will drive the rest of the program. It will
 * first perform input checking by parsing the command line arguments and
 * checking for errors. If all inputs are valid, it will call ().
 * Otherwise, it will print the corresponding error message(s). Remember that
 * all error strings have format specifiers, so be sure to add the appropriate
 * arguments when printing error messages. Also, make sure you use your
 * rangeCheck() function when checking the limits of the command line argument
 * Date: Oct 28th
 * Source of help: Tutor, discussion 3 worksheet
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "pa2Strings.h"
#include "pa2.h"
#include <time.h>

#define second_r 2
#define null_p '\0'

/*
 * Function name: main.c
 * Function prototype: int main
 * Description: it will first perfrom input checking by parsing the command
 * arguments and checking for errors. If all inputs are valid, it will call
 * printClock()
 * Parameters: int argc: the number of arguments 
 *             char* argv[]: the arguments in char* form
 * Side effects: error printed out to stderr
 * Error conditions: numTicks, startTime
 * Return values: failure or success
 */

int main(int argc, char* argv[]){
    ///////////////First create an error counter///////////////////
    int counter = 0;
    ///////////////First create a unsigned long clock///////////////
    unsigned long clock;
    ///////////////Create structs/////////////
    struct tm* myTime;
    struct timeInfo printTime;
    struct timeval currentTime;
    long numTicks = DEF_TICKS;
    ////////First error check: user enter more than MAX_ARGS/////
    if(argc > MAX_ARGS){
        fprintf(stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, 
                DEF_TICKS, MIN_HR, MAX_HR,  MIN_MIN, 
                MAX_MIN, MIN_SEC, MAX_SEC);
        return EXIT_FAILURE;
    }

    //////////////////Special case: no args////////////////////
     if(argc == 1){
        
         //populate the struct tm with the default time using get currentTime
         
        getCurrentTime(&currentTime, NULL);
        myTime = localtime(&currentTime.tv_sec);
        convertTime(&printTime, myTime);
    }


    /////////////////////Now we parse the argument///////////////
     //////if the command line argument is STR_HELP////
    if(argc > 1){
        if (strcmp(argv[1],STR_HELP)==0){
            fprintf(stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, 
                    DEF_TICKS, MIN_HR, MAX_HR,  MIN_MIN, 
                    MAX_MIN, MIN_SEC, MAX_SEC);
            return EXIT_SUCCESS;
        }
    
    ///////////////////////Move on to numTicks///////////////////
    
        //If numTicks was not entered, initialize it with DEF_TICK
        if(argc == 1){
            numTicks = DEF_TICKS;
        }

         //convert numTicks from a string to a long using strtol()
    
        char* endptr;
        errno = 0;
        numTicks = strtol(argv[1], &endptr, BASE);
        //error case 1: overflow
        if(errno != 0){
            fprintf(stderr, STR_TICK_PARSE_ERR);
            counter++;
        }

        //error case 2: not numTicks
        else if(*endptr != null_p){
            fprintf(stderr, STR_TICK_PARSE_ERR);
            counter++;
        }
        /////////////////////if parsing the number succeeds///////////
        ////////////////////////////Move on to startTime/////////////////

        else if(*endptr == null_p && errno == 0)
        {
            //error case 1: not in range
            if(numTicks < MIN_TICKS || numTicks > MAX_TICKS){
                fprintf(stderr, STR_TICKS_RANGE_ERR, numTicks, MIN_TICKS, 
                    MAX_TICKS);
                counter ++;     
            }
            //if startTime is not entered
            if(argc != MAX_ARGS){
            //populate the struct tm with the default time
         
                getCurrentTime(&currentTime, NULL);
                myTime = localtime(&currentTime.tv_sec);
                convertTime(&printTime, myTime);
            }
        }
        //if starttime is entered
        //populate the struct tm
        if(argc == MAX_ARGS) { 
            unsigned long bitmap;
            bitmap = interpretTime(&printTime, argv[second_r]);
            if(bitmap == ERR_TIME_FORMAT){
                fprintf(stderr, STR_TIME_FORMAT_ERR);
                counter++;
            }
            else if(bitmap == ERR_TIME_LIMITS){
                fprintf(stderr, STR_TIME_RANGE_ERR);
                counter++;
            }
            else if(bitmap == ERR_TIME_NUM){
                fprintf(stderr, STR_TIME_PARSE_ERR);
                counter++;
            }
            else if(bitmap == ((ERR_TIME_FORMAT)|(ERR_TIME_LIMITS))){
                fprintf(stderr, STR_TIME_FORMAT_ERR);
                fprintf(stderr, STR_TIME_RANGE_ERR);
                counter++;
            }    
            else if(bitmap == ((ERR_TIME_FORMAT)|(ERR_TIME_NUM))){
                fprintf(stderr, STR_TIME_FORMAT_ERR);
                fprintf(stderr, STR_TIME_PARSE_ERR);
                counter++;
            }
            else if(bitmap == ((ERR_TIME_LIMITS)|(ERR_TIME_NUM))){
                fprintf(stderr, STR_TIME_RANGE_ERR);
                fprintf(stderr, STR_TIME_PARSE_ERR);
                counter++;
            }
            else if(bitmap == ((ERR_TIME_FORMAT)|
                (ERR_TIME_LIMITS)|(ERR_TIME_NUM))){
                fprintf(stderr, STR_TIME_FORMAT_ERR);
                fprintf(stderr, STR_TIME_RANGE_ERR);
                fprintf(stderr, STR_TIME_PARSE_ERR);
                counter++;
            }
        }

    }
    //If any errors occurred during the argument parsing
    if(counter != 0){
        //print usage and return fail
        fprintf(stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, 
                DEF_TICKS, MIN_HR, MAX_HR,  MIN_MIN, 
                MAX_MIN, MIN_SEC, MAX_SEC);
        return EXIT_FAILURE;
    }
    ///////////////////////////If no errors were encountered////////////////
    ////////////////////if starttime is not specified///////////////////
    if(argc == second_r || argc == 1){
        puts(asctime(myTime));
    }
    //set the clock to timeInfo * timeInfo
    setClock(&clock, &printTime);
    
    //For each tick in numTicks, display the BCD clock
    int i;
    for(i = 0; i < numTicks + 1; i++){
        printClock(&clock);
        tickClock(&clock);
    }
    return EXIT_SUCCESS;
}
 
