/*
 * Filename: incrementBCDValue.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Desciption: This assembly module will incrememnt the value of BCD by 1
 * and return 1 or 0 depends on resetThreshold.
 * Date: Oct 21, 2018
 * Source of Help: Tutor, discussion 3 worksheet, discussion 3 slide
 */

 @ Raspberry Pi
        .cpu    cortex-a53                          @ Version of the Pis
        .syntax unified                             @ Modern syntax
 
 @ Useful source code constants                     
        .equ    FP_OFFSET, 4                        @ (saved register - 1) * 4
        
        //locar vars
        .equ    LOCAL_VAR_SPACE, 8                  @ have three local vars
        .equ    left_OFFSET, -8                     @ Local var left digit
        .equ    right_OFFSET, -9                    @ Local var right digit
        .equ    bcd_OFFSET, -10                     @ Local bcd digit


        //these are param vars
        .equ    PARAM_SPACE,8                       @ alocate 8 bytes 
        .equ    PARAM1_OFFSET, -16                  @ 1st formal param
        .equ    PARAM2_OFFSET, -20                  @ 2nd formal param
        .equ    PARAM3_OFFSET, -21                  @ 3rd formal param
        

 @ define constants
        .equ    FOUR, 4                             @ store 4
        .equ    ONE, 1                              @ store 1
        .equ    ZERO, 0                             @ store 0
        .equ    right_F, 0x0F                       @ right_F
        .equ    left_F, 0xF0                        @ left_F
        .equ    TEN, 10                             @ store 10
 @ Text region
        .global incrementBCDValue                   @ specify as global
        .text
        .align  2                                   @ align to 4 bytes

/*
 * Function Header: incrementBCDValue()
 * Function Prototype: unsigned char incrementBCDValue( unsigned char* BCDdigits, 
 *                                const unsigned char resetThreshold,
 *                                const unsigned char resetValue )
 *
 * Description: This function will be the carry-out of this operation. I.e. 
 * return 1if the threshold is crossed (and the value is reset), else 
 * return 0 to indicate there is no carry to the next d 
 * Parameters: BCDdigits: unsigned two bcd digits as char
 *             resetThreshold: unsigned resetThreshold value as char
 *             resetValue: unsigned resetValue as char
 * Side Effects: increment by 1
 * return values: 1 or 0
 * error condition: none
 * Registers used:
 * r0: -- arg 1 -- BCDdigits
 * r1: -- arg 2 -- resetThreshold
 * r2: -- arg 3 -- resetValue
 * r3: temp register
 */

 incrementBCDValue:
 @ Standard prologue:
        push    {fp,lr}                             @ push fp, lr
        add     fp,sp,FP_OFFSET                     @ set fp to the base
        
        @ Allocate space for local_var
        sub     sp,sp,LOCAL_VAR_SPACE               @ allocate space local var

        @ Allocate space for param 
        
        sub     sp,sp,PARAM_SPACE                   @ allocate space param

        str     r0, [fp, PARAM1_OFFSET]             @ store r0: the pointer
        strb    r1, [fp, PARAM2_OFFSET]             @ store r1: resetThreshold
        strb    r2, [fp, PARAM3_OFFSET]             @ store r2: resetValue
 
        //Deallocate r2 and move the content to PARAM1
        ldrb    r2, [r0]                            @ get actual offset
        strb    r2, [fp, bcd_OFFSET]                @ store the content of r0

        //Fetch the BCDdigits and separate the two digits
        ldrb    r0, [fp, bcd_OFFSET]                @ load unsigned byte
        
        //store the right digit
        mov     r3, right_F                         @ store temp = 0x0f
        and     r3, r0, r3                          @ get right digit
        strb    r3, [fp, right_OFFSET]              @ store into right local var
        
        //store the left digit
        ldrb    r0, [fp, bcd_OFFSET]                @ load bcd again
        mov     r3, left_F                          @ store temp = 0xf0
        and     r3, r0, r3                          @ get left digit
        lsr     r3, r3, FOUR                        @ lsr by 4
        strb    r3, [fp, left_OFFSET]               @ store into left loca var

        //check for internal carry by adding right d + 1
        ldrb    r3, [fp,right_OFFSET]               @ get the right digit
        add     r3,r3,ONE                           @ increment by 1
        strb    r3, [fp,right_OFFSET]               @ store it
        
        //if the incremented value != 10
        cmp     r3, TEN                             @ check for carryover
        bne     end_if                              @ not equal then branch

        /* if statements */
        ldrb    r3, [fp,right_OFFSET]               @ load the right digit
        mov     r3, ZERO                            @ reset the right digit
        strb    r3, [fp,right_OFFSET]               @ store the rigth digit

        ldrb    r3, [fp,left_OFFSET]                @ load the left digit
        add     r3,r3, ONE                          @ increment 
        strb    r3, [fp,left_OFFSET]                @ store the left digit 

 end_if:
        //lsl left digit by 4 
        //or gate left and right digits
        //and compare to threshold
        ldrb    r3, [fp, left_OFFSET]               @ load the left digit
        lsl     r3,r3,FOUR                          @ lsl left by 4
        ldrb    r0, [fp, right_OFFSET]              @ load the right digit
        orr     r0,r0,r3                            @ or gate these two digits
        strb    r0, [fp, bcd_OFFSET]                @ store back to two digit

        //if the value != resetThreshold
        ldrb    r0, [fp, bcd_OFFSET]                @ load the two digits
        ldrb    r1, [fp, PARAM2_OFFSET]             @ load threshold

        cmp     r0,r1                               @ compare
        bne     end_if2                             @ branch

        /* if statement */
        //change the BCD to resetValue
        ldr     r0, [fp, PARAM1_OFFSET]             @ load the pointer 
        ldrb    r3, [fp, PARAM3_OFFSET]             @ load the resetValue
        strb    r3, [r0]                            @ store it back to r0
        mov     r0, ONE                             @ return one
        b       end                                 @ branch end

        // change the value of BCDDigits
 end_if2:  
        ldr     r0, [fp, PARAM1_OFFSET]             @ load the pointer
        ldrb    r3, [fp, bcd_OFFSET]                @ get bcd digit
        strb    r3, [r0]                            @ store it back to r0

        mov     r0, ZERO                            @ return zero
 
 end:
        sub     sp,fp,FP_OFFSET                     @ deallocates vars
        pop     {fp, pc}                            @ restore caller's fp



        


        


