/*
 * File: rangeCheck.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that checks if the value is in the range of min and max
 *              value
 * Date: Oct 14, 2018
 * Sources of Help: Tutor
 */

@ Raspberry Pi directives
        .cpu    cortex-a53              @ Version of our Pis
        .syntax unified                 @ Mordern syntax
@ Useful source code constants
        .equ    FP_OFFSET, 4            @ Offset to set fp to base of saved regs
    
        .equ    PARAM_SPACE, 12         @ Allocate 12 bytes to parameters
        .equ    PARAM1_OFFSET, -8       @ 1st Formal param offset from fp
        .equ    PARAM2_OFFSET, -12      @ 2nd Formal param offset from fp
        .equ    PARAM3_OFFSET, -16      @ 3rd Formal param offset from fp
@ store numbers
        .equ    ERROR, -1               @ return value of error =  -1
        .equ    ONE, 1                  @ return value of 1 if it is in range
        .equ    ZERO, 0                 @ return value of 0 if not in range
        .global rangeCheck              @ Specify rangeCheck as a global symbol
@ Text region   
        .text                           @ Switch to Text segment
        .align 2                        @ Align 

/*
 * Function Header: rangeCheck()
 * Function Prototype: long rangeCheck(long value, long minRange, long MaxRange);
 * Description: Returns the value of whether it is in range
 * Parameters: value - value to be checked
 *             minRange - the lower bound
 *             maxRange - the upper bound
 * Side Effects: None
 * Error Conditions: minRange is greater than or equal to maxRange, return  -1
 * Return value: -1, 0 or 1 depends on the if conditions
 * Registers used:
 *  r0 - arg 1 -- value, also used as a return value
 *  r1 - arg 2 -- minRange
 *  r2 - arg 3 -- maxRange
 */

rangeCheck:
@ Standard prologue
        push    {fp, lr}                @ save registers: fp, lr
        add     fp, sp, FP_OFFSET       @ set fp to the base of saved registers
        
        @ Allocate space for the incoming formal parameters (divisible by 4)
        sub     sp, sp, PARAM_SPACE     @ allocate space for r0-r2

        str     r0, [fp, PARAM1_OFFSET] @ store value - highest memory address
        str     r1, [fp, PARAM2_OFFSET] @ store minRange 
        str     r2, [fp, PARAM3_OFFSET] @ store maxRange - lowest memory address

        // If(r1 >= r2), then return r0=-1
        ldr     r1, [fp, PARAM2_OFFSET] @ get the value of "minRange"
        ldr     r2, [fp, PARAM3_OFFSET] @ get the value of "maxRange"

        cmp     r1,r2                   @ minRange < maxRange
        blt     else                    @ branch else

        
        mov     r0, ERROR               @ return value r0 = -1
        b       end_if

else:
        //if statement: if value >= minRange && value <= maxRange, then return
        //value
        ldr     r0, [fp, PARAM1_OFFSET] @ get the "value"
        ldr     r1, [fp, PARAM2_OFFSET] @ get "minRange"

        //use opposite logic (if value < minRange), branch to else
        cmp     r0, r1                  @ compare value and minRange
        blt     else2                   @ go to the second else

        //use opposite logic if (value >= maxRange)
        ldr     r0, [fp, PARAM1_OFFSET] @ get the "value"
        ldr     r2, [fp, PARAM3_OFFSET] @ get "maxRange"
        cmp     r0, r2                  @ compare value and maxRange
        bge     else2                   @ go to the second else
        mov     r0, ONE                 @ return value r0 = 1
        b       end_if
else2: 
        mov     r0, ZERO                @ return value r0 = 0
                                        @ pop returns address lr into pc
        b       end_if
end_if:
        sub     sp,fp,FP_OFFSET         @ deallocates vars  
        pop     {fp, pc}                @ restore caller's fp 


                                        @ pop returns address lr into pc
