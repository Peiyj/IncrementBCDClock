/*
 * Filename: convertTime
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function will use hours, minutes, and seconds in tm to
 * populate the tm_sec, tm_min, tm_hour and am_pm members of the struct pointed
 * to by timeInfo.
 * Date: Oct 28, 2018
 * source of help: discussion 3 worksheet, slides
 */

 ///////////////////////////////////TODO: debug this/////////////////////////

 @ Raspberry Pi
        .cpu    cortex-a53                          @Versions of the Pis
        .syntax unified                             @ modern syntax
 @ Useful source code
        .equ    FP_OFFSET, 4                        @ save regs

        // local vars
        .equ    LOCAL_VAR_SPACE, 16                 @ allocate 32 bytes
        .equ    sec_OFFSET, -8                      @ second 
        .equ    min_OFFSET, -12                     @ minute 
        .equ    hour_OFFSET, -16                    @ hour
        .equ    ap_OFFSET, -20                      @ am/pm

        // param space
        .equ    PARAM_SPACE, 8                      @ allocate 8 bytes
        .equ    timeInfoPtr_OFFSET, -24             @ stores timeinfo pointer
        .equ    tmPtr_OFFSET, -28                   @ stores tm pointer

 @ Define constants
        .equ    am, 0x61                            @ store am
        .equ    pm, 0x70                            @ store pm
        .equ    change_ap, 12                       @ store 12
        .equ    twelve, 12                          @ store 12    
 

 @ Text
        .global convertTime                         @ make it global
        .text
        .align 2                                    @ 4 bytes alignment

 /*
  * Function Header: convertTime()
  * Function prototype: void convertTime( struct timeInfo * timeInfo, const
  * struct tm * tm);
  * Desctiption: This function will use hours, minutes, and seconds in tm to
  * populate the tm_sec, tm_min, tm_hour and am_pm members of the struct point
  * to by timeInfo.
  * Params: timeInfo: struct that contains time
  *         tm: struct that also contains time but in 24 hr form
  * Regs used:
  * r0: arg1: timeInfo
  * r1: arg2: tm
  * r3: temp
  * r4: temp
  */

  convertTime:
        @ Standard prologue

        push    {fp,lr}                             @ push fp,lr
        add     fp,sp,FP_OFFSET                     @ set fp to the base

        @ Allocate space for local var
        sub     sp,sp,LOCAL_VAR_SPACE               @ allocate local var

        @ Allocate space for param var
        sub     sp,sp,PARAM_SPACE                   @ allocate space param

        str     r0, [fp, timeInfoPtr_OFFSET]        @ store the timeInfo ptr
        str     r1, [fp, tmPtr_OFFSET]              @ store the tm ptr

        /////////////////////////////hour////////////////////////////////
        ldr     r1, [fp, tmPtr_OFFSET]              @ load tm pointer
        ldr     r3, =tm_hour_offset                 @ load hour offset

        ldr     r3, [r3]                            @ get the hour content
        ldr     r0, [r1,r3]                         @ get the hour offset

        // store the hour offset to hour_OFFSET
        str     r0, [fp, hour_OFFSET]               @ store into hour offset
        ldr     r0, [fp, hour_OFFSET]               @ load into hour offset

        // hour >= 12
        cmp     r0, twelve                          @ compare to 12
        bge     end_if                              @ branch if 12-23

        ///////if statements//////
        ///////hour is between 0-11, so it should be am///////////////
        ldr     r0, [fp, timeInfoPtr_OFFSET]        @ load time info pointer
        ldr     r3, =timeInfo_ampmOffset            @ load am/pm
        ldr     r3, [r3]                            @ get am/pm offset    

        //store am to ampmoffset
        mov     r2,am                               @ move am to r2
        strb    r2, [r0,r3]                         @ store it to address
        b       end                                 
 end_if:
        ///////hour is between 12-23, so it should be pm///////////////
        ldr     r0, [fp, timeInfoPtr_OFFSET]        @ load tm pointer
        ldr     r3, =timeInfo_ampmOffset            @ load am/pm
        ldr     r3, [r3]                            @ get am/pm offset    

        @ store to pm hour offset
        mov     r2,pm                               @ move am to r2
        strb    r2, [r0, r3]                        @ store it to address
 end:       
        //////////////////////////////store minutes/////////////////////////////////
        ldr     r1, [fp, tmPtr_OFFSET]              @ load tm ptr
        ldr     r2, =tm_min_offset                  @ load min offset
        ldr     r2, [r2]                            @ dereference
        ldr     r1, [r1,r2]                         @ r1: has the content of min
        str     r1, [fp, min_OFFSET]                @ store r1 to min offset

        ldr     r1, [fp, timeInfoPtr_OFFSET]        @ load time info ptr
        ldr     r2, =timeInfo_minOffset             @ load the address 
        ldr     r2, [r2]                            @ get the content of min
        ldr     r3, [fp, min_OFFSET]                @ get min
        str     r3, [r1,r2]                         @ store min in timeinfo
        //////////////////////////////store seconds/////////////////////////////////
        ldr     r1, [fp, tmPtr_OFFSET]              @ load tm ptr
        ldr     r2, =tm_sec_offset                  @ load sec offset
        ldr     r2, [r2]                            @ dereference
        ldr     r1, [r1,r2]                         @ r1: has the content of sec
        str     r1, [fp, sec_OFFSET]                @ store r1 to sec offset

        ldr     r1, [fp, timeInfoPtr_OFFSET]        @ load time info ptr
        ldr     r2, =timeInfo_secOffset             @ load the address 
        ldr     r2, [r2]                            @ get the content of sec
        ldr     r3, [fp, sec_OFFSET]                @ get sec
        str     r3, [r1,r2]                         @ store sec in timeinfo
 
        ///////////////////////////manipulate hours////////////////////////////
        ldr     r0, [fp, hour_OFFSET]               @ load hour from hour offset
        ///oppsite logic hour > 12
        cmp     r0, change_ap                       @ compare to 12
        bgt     else_if2                            @ branch to elseif2
        //////////////////////////////Special cases//////////////////////////
        ldr     r0, [fp, hour_OFFSET]               @ load hour
        mov     r1, 0                               @ branch if not equal
        cmp     r0, r1                              @ compare when hour is 0
        bne     dont_changeap                       @ branch
        mov     r0, twelve                          @ mov 12 to r0     
        ldr     r1, [fp, timeInfoPtr_OFFSET]        @ load the timeinfoptr
        ldr     r2, =timeInfo_hourOffset            @ timeinfo hour
        ldr     r2,[r2]                             @ load the content
        str     r0, [r1,r2]                         @ store it to ampm

        ldr     r0, [fp, timeInfoPtr_OFFSET]        @ load time info pointer
        ldr     r3, =timeInfo_ampmOffset            @ load am/pm
        ldr     r3, [r3]                            @ get am/pm offset    

        //store am to ampmoffset
        mov     r2,am                               @ move am to r2
        strb    r2, [r0,r3]                         @ store it to address
 
        b       end2


dont_changeap:
        ///if it is 1-11, store 1-11
        ldr     r0, [fp, hour_OFFSET]               @ load hour again
        ldr     r1, [fp, timeInfoPtr_OFFSET]        @ load the timeinfo ptr
        ldr     r2, =timeInfo_hourOffset            @ load the hour offset
        ldr     r2, [r2]
        str     r0, [r1,r2]                         @ store back to r1
        b       end2                                @ branch to end2
else_if2:
        ///if it is bigger than 12, store hour - 12
        ldr     r0, [fp, hour_OFFSET]               @ load hour again
        sub     r0,r0,twelve                        @ hour - 12

        ldr     r1, [fp, timeInfoPtr_OFFSET]        @ load the timeinfo ptr
        ldr     r2, =timeInfo_hourOffset            @ load the hour offset
        ldr     r2, [r2]
        str     r0, [r1,r2]
        b       end2                                @ branch to end2
end2:
        sub     sp,fp,FP_OFFSET                     @ store sp to fp
        pop     {fp,pc}                             @ pop everything
             
        


        
