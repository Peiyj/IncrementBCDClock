/*
 * Filename: interpretTime.c
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function will parse the time string and populate 
 * the tm_sec, tm_min, tm_hour and am_pm members of the struct timeInfo
 * pointed to by timeInfo. If there are no errors in this process, you
 * should return 0. Otherwise, the appropriate error flags/bits should 
 * be set in the unsigned long bitmap to be returned (see pa2.h for 
 * the error flags). You should not print any error messages in this function.  
 *
 * Date: Oct, 28, 2018
 * Source of help: tutor, discussiion 3 worksheets, slides
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include <string.h>
#include <errno.h>

#define TWO 2
#define THREE 3

#define am_low 'a'
#define am_cap 'A'
#define pm_low 'p'
#define pm_cap 'P'
#define nullT '\0'

unsigned long interpretTime(struct timeInfo* timeInfo, const char* time){
   //////////////////////////////initialize bit map/////////////////////////
   unsigned long bitmap = 0;
   //////////////copy the contents of time into local char array/////////////
   char copy[BUFSIZ] = {nullT};
   strncpy(copy, time, BUFSIZ);
   
   char *ret;
   //find first ":"
   ret = strchr(copy, CHAR_SEPARATOR);
   
   //set the ERR_TIME_FORMAT if it is null
   if(ret == NULL){
       return bitmap = ERR_TIME_FORMAT;
   }
   //else set it to null terminator
   else{
       *ret = nullT;
   }
    
   //find second ":"
   ret ++;
   ret = strchr(ret, CHAR_SEPARATOR);
   if(ret == NULL){
       return bitmap = ERR_TIME_FORMAT;
   }
   else{
       *ret = nullT;
   }
   ret ++;
   //error checking, if it reaches the end and return null

   ret = strchr(ret, CHAR_SEPARATOR);
   if(ret != NULL){
       return bitmap = ERR_TIME_FORMAT;
   }
   
   //Convert each unit of time (hours, minutes, seconds) to an integer val
   /////////////////////////////initialize errno///////////////////////////
   errno = 0;
   char *endptr;
   /////////////////////////////////parse hour/////////////////////////////
   long hour = strtol(copy, &endptr, BASE);
   //if parsing the number succeeds
   if(*endptr == nullT && errno == 0){
       //case 1: check if the number is between 0 to 12
       if(hour < MIN_HR || hour > MAX_HR){
           bitmap = (bitmap|ERR_TIME_LIMITS);
       }
       //case 2: check if the number is 0, we set it to 12
       if(hour == MIN_HR){
           hour = MAX_HR;
       }
   }

   //case 3: overflow
   if(errno != 0){
       bitmap = (bitmap | ERR_TIME_NUM);
   }

   //case 4: if the hour contains non-numeric characters
   if(*endptr != nullT){
       bitmap = (bitmap | ERR_TIME_NUM);
   }
   

   errno = 0;
   if(endptr != nullT){
        endptr = strchr(endptr, nullT);
   }
   endptr++;
   /////////////////////////////////parse minute///////////////////////////
   long minute = strtol(endptr, &endptr, BASE);
   //if parsing the number succeeds
   if(*endptr == nullT && errno == 0){
       //case 1: check if the number is between 0 to 60
       if(minute < MIN_MIN || minute > MAX_MIN){
           bitmap = (bitmap|ERR_TIME_LIMITS);
       }
   }

   //case 3: overflow
   if(errno != 0){
       bitmap = (bitmap | ERR_TIME_NUM);
   }

   //case 4: if the minute contains non-numeric characters
   if(*endptr != nullT){
       bitmap = (bitmap | ERR_TIME_NUM);
   }
    
   errno = 0;
   if(endptr != nullT){
        endptr = strchr(endptr, nullT);
   }   
   endptr++;
   /////////////////////////////////parse second/////////////////////////
   long second = strtol(endptr, &endptr, BASE);
   //if parsing the number succeeds
   if(((*endptr == am_low) || (*endptr == am_cap) || (*endptr == pm_low) 
               || (*endptr == pm_cap)) && errno == 0){
       //case 1: check if the number is between 0 to 60
       if(second < MIN_SEC || second > MAX_SEC){
           bitmap = (bitmap|ERR_TIME_LIMITS);
       }
    }

   //case 3: overflow
   if(errno != 0){
       bitmap = (bitmap | ERR_TIME_NUM);
   }
   
   /////////////////////////////////parse ampm//////////////////////////////
   char ampm = *endptr;
   //if parsing the number succeeds
       //case 1: check if it is indeed 'a', 'A', 'p', 'P'
   if( ampm != am_low && ampm != am_cap 
       && ampm != pm_low && ampm != pm_cap){
       bitmap = (bitmap | ERR_TIME_FORMAT);
   }
    
   
   //////error checking if it is null terminated////////
   char null = *(++endptr);
   if( null != nullT){
       bitmap = (bitmap | ERR_TIME_FORMAT);
   }

   /////////////////////////if bitmap is not zero, return///////////////
   if(bitmap != 0){
       return bitmap;
   }
   /////////////////////now store every time to the struct/////////////
   (*timeInfo).tm_sec = second;
   (*timeInfo).tm_min = minute;
   (*timeInfo).tm_hour = hour;

   /////////special case for storing am, pm///////////////
   if(ampm == am_low || ampm == am_cap){
       ampm = am_low;
   }

   if(ampm == pm_low || ampm == pm_cap){
       ampm = pm_low;
   }

   (*timeInfo).am_pm = ampm;

   return bitmap;
}

