/*
 * File: printChar.s
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: file that can print single character
 * Date: Oct 14, 2018
 * Source of Help: Tutor
 */

 @ Raspberry Pi directives
        .cpu    cortex-a53                  @ Version of our Pis
        .syntax unified                     @ Midern syntax
 @ Useful source code constants
        .equ    FP_OFFSET,4                 @ Offset to set fp to the base
 @ store global
        .global    printChar                @ Specify as a global symbol
 @ text
        .section .rodata
 fmt:   .asciz  "%c"
        .text
        .align 2
/*
 * Function Header: printChar(
 * Function Prototype:void printChar( char ch );
 * Desciption: return  the character argument to stdout 
 * Side Effects: none
 * Error Conditions: none
 * registers used:
 * r0 -- arg 1 -- char, also as return value
 */
printChar:
@ Standard prologue
        push    {fp,lr}                     @ save registers
        add     fp,sp,FP_OFFSET             @ set fp to the base
       
        mov     r1,r0                       @ move string to r1 to call printf
        ldr     r0,=fmt                     @ get address of format char
        bl      printf                      @ calls printf


        sub     sp,fp,FP_OFFSET             @ deallocate vars
        pop     {fp,pc}                     @ restore caller's fp
   

