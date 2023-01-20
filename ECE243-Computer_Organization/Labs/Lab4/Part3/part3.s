/* Program that counts consecutive 1's */
//R5 holds the count for 1's for Longest
//R6 holds the count for 0's for Longest
//R7 holds the count for A's for Longest
//
//R0 holds the count for 1's for each word
//R1 holds word
//R8 holds 0101 0101 0101 0101 0101 0101 0101 0101
//R9 holds temp Longest A's to Compare


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
          BEQ     END             //If R1 = 0, end MAIN loop

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

END:      B       END
                    
                                  //1s  //0s  //A's //32-bit
TEST_NUM: .word   0xff3feaaf      //9   //2   //11 //1111 1111 0011 1111 1110 1010 1010 1111
          .word   0xfe3ff55f      //10  //3   //9  //1111 1110 0011 1111 1111 0101 0101 1111
          .word   0xfc3ffaaf      //11  //4   //9  //1111 1100 0011 1111 1111 1010 1010 1111
          .word   0xf83ffd5f      //12  //5   //7  //1111 1000 0011 1111 1111 1101 0101 1111
          .word   0xf03ffeaf      //13  //6   //7  //1111 0000 0011 1111 1111 1110 1010 1111
          .word   0xe03fff5f      //14  //7   //5  //1110 0000 0011 1111 1111 1111 0101 1111
          .word   0xc03fffaf      //15  //8   //5  //1100 0000 0011 1111 1111 1111 1010 1111
          .word   0x803fffdf      //16  //9   //3  //1000 0000 0011 1111 1111 1111 1101 1111
          
          .word   0x00000000      //Used to end loop of list
CONSTANT: .word   0x55555555      //0101 0101 0101 0101 0101 0101 0101 0101

          .end                            
