/* Program that counts consecutive 1's, 0's, A's, and Displays on HEX */
//R5 holds the count for 1's for Longest
//R6 holds the count for 0's for Longest
//R7 holds the count for A's for Longest
//
//R0 holds the count for 1's for each word
//R1 holds word
//R8 holds 0101 0101 0101 0101 0101 0101 0101 0101
//R9 holds temp Longest A's to Compare

//ANSWER SHOULD BE:
//R5 = d.16 = h.00000010 
//R6 = d.09 = h.00000009 
//R7 = d.11 = h.0000000b
//ANSWER SHOULD BE ON HEX: R7 R6 R5 = 11 09 16

          .text                   // executable code follows
          .global _start      
_start:   MOV     R5, #0          //R5 holds Resulting Longest consecutive 1's
          MOV     R6, #0          //R6 holds Resulting Longest consecutive 0's
          MOV     R7, #0          //R7 holds Resulting Longest consecutive A's
          MOV     R8, #CONSTANT   //R8 holds address pf CONSTANT
          LDR     R8, [R8]        //R8 holds 0101 0101 0101 0101 0101 0101 0101 0101
          MOV     R9, #0          //R9 used for temporary R7
          MOV     R3, #TEST_NUM   //R3 holds address of first word of list
MAIN:     LDR     R1, [R3]        //R1 loaded with word of list
          CMP     R1, #0          //loop until R1 reaches the last word (0)
          BEQ     DISPLAY         //If R1 = 0, end MAIN loop, go to DISPLAY

          BL      ONES            //Else, go to Subroutine ONES
          CMP     R5, R0          //Current compared with New (1's)
          MOVLT   R5, R0          //R5 holds Longest 1's

          LDR     R1, [R3]        //R1 loaded again for ZEROS
          MVN     R4, R1          //R4 holds Complement of R1
          BL      ZEROS           //After ONES, go to ZEROS
          CMP     R6, R0          //Current compared with New (0's)
          MOVLT   R6, R0          //R6 holds Longest 0's

          LDR     R1, [R3]        //R1 loaded again for ALTERNATE for 1's
          BL      ALTERNATE       //To Perform XOR with R8
          BL      ONES            //Count consecutive 1's
          MOV     R9, R0          //R9 holds 1's count

          LDR     R1, [R3]        //R1 loaded again for ALTERNATE for 0's
          BL      ALTERNATE       //To Perform XOR with R8
          MVN     R4, R1          //R4 holds Complement of XOR
          BL      ZEROS           //Count consecutive 0's
          CMP     R9, R0          //1's compared to 0's for A's
          MOVLT   R9, R0          //R9 holds temp Longest A's

          CMP     R7, R9          //Current compared with New (A's)
          MOVLT   R7, R9          //R7 holds Longest A's

          ADD     R3, R3, #4      //R3 now holds address of next word in list
          B       MAIN
                    
/* Display R5 on HEX1-0, R6 on HEX3-2 and R7 on HEX5-4 */
DISPLAY:  LDR     R8, =0xFF200020 // base address of HEX3-HEX0

          //code for R5
          MOV     R0, R5          // display R5 on HEX1-0
          BL      DIVIDE          // ones digit will be in R0; tens digit in R1
          MOV     R9, R1          // save the tens digit //R9=tens
          BL      SEG7_CODE       // Ones goes into subroutine as R0
          MOV     R4, R0          // save bit code //R4=ones
          MOV     R0, R9          // retrieve the tens digit, get bit code
          BL      SEG7_CODE       // Tens goes into subroutine as R0
          LSL     R0, #8          // Tens shifted left 8
          ORR     R4, R0          // Ones + Tens of R5
            
          //code for R6
          MOV     R0, R6          // display R6 on HEX3-2
          BL      DIVIDE          // ones digit will be in R0; tens digit in R1
          MOV     R9, R1          // save the tens digit //R9=tens
          BL      SEG7_CODE       // Ones goes into subroutine as R0
          MOV     R10, R0         // save bit code //R10=ones
          MOV     R0, R9          // retrieve the tens digit, get bit code
          BL      SEG7_CODE       // Tens goes into subroutine as R0
          LSL     R0, #8          // Tens shifted left 8
          ORR     R10, R0         // Ones + Tens of R6
          LSL     R10, #16        // R6 shifted left 16
          ORR     R4, R10         // R5 + R6

          STR     R4, [R8]        // display the numbers from R6 and R5
          LDR     R8, =0xFF200030 // base address of HEX5-HEX4
            
          //code for R7
          MOV     R0, R7          // display R7 on HEX5-4
          BL      DIVIDE          // ones digit will be in R0; tens digit in R1
          MOV     R9, R1          // save the tens digit //R9=tens
          BL      SEG7_CODE       // Ones goes into subroutine as R0
          MOV     R4, R0          // save bit code //R4=ones
          MOV     R0, R9          // retrieve the tens digit, get bit code
          BL      SEG7_CODE       // Tens goes into subroutine as R0
          LSL     R0, #8          // Tens shifted left 8
          ORR     R4, R0          // Ones + Tens of R7
            
          STR     R4, [R8]        // display the number from R7

END:      B       END


/* Subroutine to find length of consecutive 1's, 0's, Alternatives */
ONES:     MOV     R0, #0          //R0 will hold the result
LOOP_O:   CMP     R1, #0          //loop until the word contains no more 1's
          BXEQ    lr              //If R1 = 0, return from Subroutine Loop
          LSR     R2, R1, #1      //perform SHIFT
          AND     R1, R1, R2      //then AND, Saved to R1
          ADD     R0, #1          //count current string length 1's
          B       LOOP_O  

ZEROS:    MOV     R0, #0          //R0 will hold the result
LOOP_Z:   CMP     R4, #0          //loop until the word contains no more 1's
          BXEQ    lr              //If R1 = 0, return from Subroutine Loop
          LSR     R2, R4, #1      //perform SHIFT
          AND     R4, R4, R2      //then NOT AND, Saved to R1
          ADD     R0, #1          //count current string length 0's
          B       LOOP_Z  

ALTERNATE:EOR     R1, R1, R8      //Perform XOR with R8
          BX      lr              //Return from Subroutine
/* Subroutine to find length of consecutive 1's, 0's, Alternatives */


/* Subroutine to convert the digits from 0 to 9 to be shown on a HEX display. */
//Parameters: R0 = the decimal value of the digit to be displayed
//Returns: R0 = bit patterm to be written to the HEX display
SEG7_CODE:  MOV     R1, #BIT_CODES  
            ADD     R1, R0         // index into the BIT_CODES "array"
            LDRB    R0, [R1]       // load the bit pattern (to be returned)
            MOV     PC, LR              
/* Subroutine to convert the digits from 0 to 9 to be shown on a HEX display. */


/* Subroutine to perform the integer division R0/10. */
//Returns: quotient in R1, and remainder in R0
DIVIDE:     MOV    R2, #0
CONT:       CMP    R0, #10
            BLT    DIV_END
            SUB    R0, #10
            ADD    R2, #1
            B      CONT
DIV_END:    MOV    R1, R2     // quotient in R1 (remainder in R0)
            MOV    PC, LR
/* Subroutine to perform the integer division R0/10. */


/* LISTS */
BIT_CODES:  .byte   0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
            .byte   0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111
            .skip   2      // pad with 2 bytes to maintain word alignment

                                  //1s  //0s  //A's //32-bit
TEST_NUM: .word   0xff3feaaf      //9   //2   //11  //1111 1111 0011 1111 1110 1010 1010 1111
          .word   0xfe3ff55f      //10  //3   //9   //1111 1110 0011 1111 1111 0101 0101 1111
          .word   0xfc3ffaaf      //11  //4   //9   //1111 1100 0011 1111 1111 1010 1010 1111
          .word   0xf83ffd5f      //12  //5   //7   //1111 1000 0011 1111 1111 1101 0101 1111
          .word   0xf03ffeaf      //13  //6   //7   //1111 0000 0011 1111 1111 1110 1010 1111
          .word   0xe03fff5f      //14  //7   //5   //1110 0000 0011 1111 1111 1111 0101 1111
          .word   0xc03fffaf      //15  //8   //5   //1100 0000 0011 1111 1111 1111 1010 1111
          .word   0x803fffdf      //16  //9   //3   //1000 0000 0011 1111 1111 1111 1101 1111
          
          .word   0x00000000      //Used to end loop of list
CONSTANT: .word   0x55555555      //0101 0101 0101 0101 0101 0101 0101 0101

          .end 