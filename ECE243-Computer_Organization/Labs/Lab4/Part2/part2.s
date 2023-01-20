/* Program that counts consecutive 1's */
//R0 holds the count for 1's for each word
//R5 holds the count for 1's for Longest
//R1 holds word

          .text                   // executable code follows
          .global _start      
_start:   MOV     R5, #0          //R5 holds Resulting Longest consecutive 1's
          MOV     R3, #TEST_NUM   //R3 holds address of first word of list
MAIN:     LDR     R1, [R3]        //R1 loaded with word of list
          ADD     R3, R3, #4      //R3 now holds address of next word in list
          CMP     R1, #0          //loop until R1 reaches the last word (0)
          BEQ     END             //If R1 = 0, end list loop
          BL      ONES            //Else, go to Subroutine ONES
          CMP     R5, R0          //Current compared with New
          MOVLT   R5, R0          //R5 holds word with Longer 1's
          B       MAIN

ONES:     MOV     R0, #0          //R0 will hold the result
LOOP:     CMP     R1, #0          //loop until the word contains no more 1's
          BXEQ    lr              //If R1 = 0, return from Subroutine Loop
          LSR     R2, R1, #1      //perform SHIFT
          AND     R1, R1, R2      //then AND, Saved to R1
          ADD     R0, #1          //count current string length
          B       LOOP  

END:      B       END
                    

TEST_NUM: .word   0x103fd00f      //8   //0001 0000 0011 1111 1101 0000 0000 1111
          .word   0x103fe00f      //9   //0001 0000 0011 1111 1110 0000 0000 1111
          .word   0x103ff00f      //10  //0001 0000 0011 1111 1111 0000 0000 1111
          .word   0x103ff80f      //11  //0001 0000 0011 1111 1111 1000 0000 1111
          .word   0x103ffc0f      //12  //0001 0000 0011 1111 1111 1100 0000 1111
          .word   0x103ffe0f      //13  //0001 0000 0011 1111 1111 1110 0000 1111
          .word   0x103fff0f      //14  //0001 0000 0011 1111 1111 1111 0000 1111
          .word   0x103fff8f      //15  //0001 0000 0011 1111 1111 1111 1000 1111
          
          .word   0x00000000      //Used to end loop of list

          .end                            


//shifts R1 to right by 1, saves to R2, R1 & R2 saved to R1, R0+=1 (Count)
//compares until & value (saved to R1) = 0