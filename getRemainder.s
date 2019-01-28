/*
 * File: getRemainder.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that has function calculates and returns the remainder of the
 *              division between dividend and the divisor
 * Date: Oct 14, 2018
 * Source of Help: Tutor
 */

@ Raspberry Pi directives
        .cpu    cortex-a53                  @ Version of our Pis
        .syntax unified                     @ Modern syntax
@ Useful source code constants 
        .equ    FP_OFFSET, 4                @ Offset to set fp to the base
        .equ    LOCAL_VAR_SPACE, 8          @ Allocate 8 bytes of local vars
        .equ    A_OFFSET, -8                @ Local var a offset from fp
        .equ    B_OFFSET, -12               @ Local var b offset from fp
        .equ    PARAM_SPACE, 8              @ Allocate 8 bytes of param vars
        .equ    PARAM1_OFFSET, -16          @ 1st param
        .equ    PARAM2_OFFSET, -20          @ 2nd param
@ Store numbers
        .global getRemainder                @ Specify as a global symbol
@ Text region
        .text                               @ Switch to Text segment
        .align 2                            @ Align

/*
 * Function Header: getRemainder()
 * Function Prototype: long getRemainder( long dividend, long divisor );
 * Description: returns the value of remainder
 * Parameters: dividend - divident
 *             divisor - divisor
 * Side Effects: none
 * Error Conditions: do not need to handle when divisor is 0
 * return value: the remainder
 * Registers used:
 * r0 - arg 1 -- dividend, also used as a return value
 * r1 - arg 2 -- divisor
 * r3 -- local variable
 */

getRemainder:
@ Standard prologue
        push    {fp, lr}                    @ save registers
        add     fp,sp, FP_OFFSET            @ set fp to the base

        @ Allocate space for local var
        sub     sp,sp, LOCAL_VAR_SPACE      @ allocate local var
       
        @ Allocate space for params
        sub     sp,sp, PARAM_SPACE          @ allocate params

        str     r0, [fp, PARAM1_OFFSET]     @ store dividend
        str     r1, [fp, PARAM2_OFFSET]     @ store divisor
        str     r2, [fp, A_OFFSET]          @ store quotient
        str     r3, [fp, B_OFFSET]          @ store tmp    
        //computer remainder
        sdiv    r2, r0, r1                  @ r2 = r0/r1
        mul     r3, r2, r1                  @ r3 = r2 * r1
        sub     r2, r0, r3                  @ r2 = r0-r3
        
        mov     r0, r2                      @ move the content of r2 to r0
        sub     sp,fp,FP_OFFSET             @ deallocate vars
        pop     {fp,pc}                     @ restore caller's fp
