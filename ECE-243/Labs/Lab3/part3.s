/* Program that finds the largest number in a list of integers	*/

            .text                   // executable code follows
            .global _start                  
_start:                             
            MOV     R4, #RESULT     // R4 points to result location
            LDR     R0, [R4, #4]    // R0 holds the number of elements in the list
            MOV     R1, #NUMBERS    // R1 points to the start of the list
            BL      LARGE           
            STR     R0, [R4]        // R0 holds the subroutine return value

END:        B       END             

/* Subroutine to find the largest integer in a list
 * Parameters: R0 has the number of elements in the lisst
 *             R1 has the address of the start of the list
 * Returns: R0 returns the largest item in the list
 */
LARGE:      LDR     R2, [R1]        //Get the first element
            SUBS    R0, #1          //Decrement the loop counter
LOOP:       ADD     R1, #4          //Make R1 point to next number
            LDR     R3, [R1]        //Get the next number
            CMP     R2, R3          //Compare current and next value
            MOVLT   R2, R3          //Move Greater value into R2
            SUBS    R0, #1          //Decrement the loop counter
            BNE     LOOP            //Loop if loop counter is not yet = 0
            MOV     R0, R2          //Save largest value into R0
            BX      lr              //Return from subroutine to _start

RESULT:     .word   0           
N:          .word   7           // number of entries in the list
NUMBERS:    .word   4, 5, 3, 6  // the data
            .word   1, 8, 2                 

            .end                            

