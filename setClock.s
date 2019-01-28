/*
 * Filename: setClock.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: This function will set the time pattern in the clock using 
 * the hours, minutes, and seconds in timeInfo using struct timeInfo, 
 * and use the offsets defined in pa2Globals.c to access members.
 * Date: Oct 28, 2018
 * Source of help: tutor, discussion 3 worksheet, slides
 */

 @ Raspberry Pi
        .cpu    cortex-a53                          @ Versions of the Pis
        .syntax unified                             @ Modern syntax
 @ Useful source code
        .equ    FP_OFFSET, 4                        @ save regs 

        // local vars
        .equ    LOCAL_VAR_SPACE, 32                 @ allocate 32 bytes
        .equ    sec_OFFSET, -8                      @ Local var sec
        .equ    min_OFFSET, -12                     @ Local var min
        .equ    hour_OFFSET, -16                    @ Local var hour
        .equ    ap_OFFSET, -20                      @ Local var am/pm
        .equ    c_OFFSET, -24                       @ Local var clock

        .equ    l_OFFSET,-25                        @ left offset
        .equ    r_OFFSET, -26                       @ right offset
    
        // param space
        .equ    PARAM_SPACE, 8                      @ allocate 8 bytes
        .equ    PARAM1_OFFSET, -36                  @ 1st param
        .equ    PARAM2_OFFSET, -40                  @ 2nd param

 @ Define constants
        .equ    TEN, 10                             @ store 10
        .equ    FOUR, 4                             @ store 4
        .equ    ampm_address, 12                    @ store ampm
        .equ    sec_shift,8                         @ store 8
        .equ    min_shift,16                        @ store 16
        .equ    hour_shift,24                       @ store 24
 @ Text region
        .global setClock                            @ specify as global
        .text
        .align  2                                   @ 4 bytes alignment
/*
 * Function Header: setClock()
 * Function prototype: void setClock( unsigned long * clock , const struct
 *                                      timeInfo * timeInfo )
 * Description: This function will set the time pattern in the clock 
 * using the hours, minutes, and seconds in timeInfo. of struct timeInfo,
 * and use the offsets defined in pa2Globals.c to accs
 * members.
 * Parameters: clock: pointer that tells time
               timeInfo: a struct that has time infomation
 * Side Effects: none
 * error condition: none
 * Registers used:
 * r0: arg1: clock: return value
 * r1: arg2: timeInfo
 * r2: temp1 
 * r3: temp2
 */

 setClock:
         @ Standard prologue
         push   {fp,lr}                             @ push fp, lr
         add    fp,sp,FP_OFFSET                     @ set fp to the base

         @ Allocate space for local var
         sub    sp,sp,LOCAL_VAR_SPACE               @ allocate space local var

         @ Allocate space for param 
         sub    sp,sp,PARAM_SPACE                   @ allocate space param

         str    r0, [fp, PARAM1_OFFSET]             @ store the clock pointer
         str    r1, [fp, PARAM2_OFFSET]             @ store timeInfo pointer


         ////////////////////////////////////hour/////////////////////////////////////
         
         //Get hour offset from global vars
         ldr    r1, [fp, PARAM2_OFFSET]             @ load tm pointer
         ldr    r3, =timeInfo_hourOffset            @ load hour address    
         //deallocate the vars 
         ldr    r3, [r3]                            @ get the actual offset
         ldr    r0, [r1, r3]                        @ get the value
         //change it to BCD representation
         @ store to hour offset
         //r0 is now hour offset
         strb   r0, [fp, hour_OFFSET]               @ store the hour digits
         mov    r1, TEN                             @ r1: 10
         //get remainder 
         bl     getRemainder                        @ call get remainder
         strb   r0, [fp, r_OFFSET]                  @ store it into right offset

         //load hour_OFFSET
         mov    r2, TEN                             @ r2: 10
         ldrb   r0, [fp, hour_OFFSET]               @ r0: hour digits
         sdiv   r3,r0,r2                            @ r3: left digit
         
         strb   r3, [fp, l_OFFSET]                  @ store it left offset
         ldrb   r3, [fp, l_OFFSET]                  @ load left offset
         

         //bit shifting on the upper digit
         lsl    r3,r3,FOUR                          @ shift left by 4
         strb   r3, [fp, l_OFFSET]
         ldrb   r1, [fp, r_OFFSET] 
         ldrb   r3, [fp, l_OFFSET]
         
         //orr gate these two digits
         orr    r3,r3,r1                            @ orr gate these two digits

         

         @ store hour digit
         str    r3, [fp,hour_OFFSET]                @ store r3 into hour
         ldr    r3, [fp,hour_OFFSET]                @ get hour digit
         strb   r3, [fp,c_OFFSET]                   @ store to clock offset
         ldr    r3, [fp,c_OFFSET]                   @ load to clock offset
         lsl    r3,r3,sec_shift                     @ shift 8
         str    r3, [fp,c_OFFSET]                   @ store to clock offset


                 
         

          ////////////////////////////////////minute/////////////////////////////////////
         //Get minute offset from global vars
         ldr    r1, [fp, PARAM2_OFFSET]             @ load tm pointer
         ldr    r3, =timeInfo_minOffset             @ load minute address    
         //deallocate the vars 
         ldr    r3, [r3]                            @ get the actual offset
         ldr    r0, [r1, r3]                        @ get the value
         //change it to BCD representation
         @ store to minute offset
         //r0 is now hour offset
         strb   r0, [fp, min_OFFSET]                @ store the min digits
         mov    r1, TEN                             @ r1: 10
         //get remainder 
         bl     getRemainder                        @ call get remainder
         strb   r0, [fp, r_OFFSET]                  @ store it into right offset

         //load hour_OFFSET
         mov    r2, TEN                             @ r2: 10
         ldrb   r0, [fp, min_OFFSET]                @ r0: min digits
         sdiv   r3,r0,r2                            @ r3: left digit
         
         strb   r3, [fp, l_OFFSET]                  @ store it left offset
         ldrb   r3, [fp, l_OFFSET]                  @ load left offset
         

         //bit shifting on the upper digit
         lsl    r3,r3,FOUR                          @ shift left by 4
         strb   r3, [fp, l_OFFSET]
         ldrb   r1, [fp, r_OFFSET] 
         ldrb   r3, [fp, l_OFFSET]
         
         //orr gate these two digits
         orr    r3,r3,r1                            @ orr gate these two digits

         

         @ store minute digit
         str    r3, [fp,min_OFFSET]                 @ store r3 into minute
         ldr    r3, [fp,min_OFFSET]                 @ get min digit
         strb   r3, [fp,c_OFFSET]                   @ store to clock offset
         ldr    r3, [fp,c_OFFSET]                   @ load to clock offset
         lsl    r3,r3,sec_shift                     @ shift 8
         str    r3, [fp,c_OFFSET]                   @ store to clock offset


          ////////////////////////////////////second/////////////////////////////////////
          //Get second offset from global vars
         ldr    r1, [fp, PARAM2_OFFSET]             @ load tm pointer
         ldr    r3, =timeInfo_secOffset             @ load second address    
         //deallocate the vars 
         ldr    r3, [r3]                            @ get the actual offset
         ldr    r0, [r1, r3]                        @ get the value
         //change it to BCD representation
         @ store to hour offset
         //r0 is now hour offset
         strb   r0, [fp, sec_OFFSET]                @ store the sec digits
         mov    r1, TEN                             @ r1: 10
         //get remainder 
         bl     getRemainder                        @ call get remainder
         strb   r0, [fp, r_OFFSET]                  @ store it into right offset

         //load hour_OFFSET
         mov    r2, TEN                             @ r2: 10
         ldrb   r0, [fp, sec_OFFSET]                @ r0: sec  digits
         sdiv   r3,r0,r2                            @ r3: left digit
         
         strb   r3, [fp, l_OFFSET]                  @ store it left offset
         ldr    r3, [fp, l_OFFSET]                  @ load left offset
         

         //bit shifting on the upper digit
         lsl    r3,r3,FOUR                          @ shift left by 4
         strb   r3, [fp, l_OFFSET]                  @ store left
         ldrb   r1, [fp, r_OFFSET]                  @ load right
         ldrb   r3, [fp, l_OFFSET]                  @ load light
         
         //orr gate these two digits
         orr    r3,r3,r1                            @ orr gate these two digits

         

         @ store hour digit
         str    r3, [fp,sec_OFFSET]                 @ store r3 into hour
         ldr    r3, [fp,sec_OFFSET]                 @ get hour digit
         strb   r3, [fp,c_OFFSET]                   @ store to clock offset
         ldr    r3, [fp,c_OFFSET]                   @ load to clock offset
         lsl    r3,r3,sec_shift                     @ shift 8
         str    r3, [fp,c_OFFSET]                   @ store to clock offset


         ////////////////////////////////////ampm/////////////////////////////////////

         //find the address of am_pm
         ldr    r0, [fp,PARAM2_OFFSET]              @ load the tmPtr
         ldr    r1, =timeInfo_ampmOffset            @ load the ampm ptr
         ldr    r1, [r1]                            @ load the ampm value
         ldr    r0, [r0, r1]                        @ get the content
         strb   r0, [fp,ap_OFFSET]                  @ store the ampm offset

         //now combine the four bits
         ldr    r0, [fp,ap_OFFSET]                  @ load hour digit
         strb   r0, [fp,c_OFFSET]                   

         
         ldr    r0, [fp, PARAM1_OFFSET]
         ldr    r1, [fp, c_OFFSET]
         str    r1, [r0]


         //the end
         sub    sp,fp,FP_OFFSET                     @ deallocate vars
         pop    {fp,pc}                             @ restore caller's fp




                                                                                  



        

