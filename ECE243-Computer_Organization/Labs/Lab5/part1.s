    .text
    .global _start
_start:
            MOV R0, #0 //R0 holds HEX0 displayed value
            LDR R1, HEX_ADDR //R1 holds HEX address
            LDR R2, KEY_ADDR //R2 holds KEY address
            MOV R3, #BIT_CODES

INPUT_KEY: //Checking for KEY pressed
            //Check KEY0
            LDR R4, [R2]
            CMP R4, #1 //0001
            BEQ KEY0

            //Check KEY1
            LDR R4, [R2]
            CMP R4, #2 //0010
            BEQ KEY1

            //Check KEY2
            LDR R4, [R2]
            CMP R4, #4 //0100
            BEQ KEY2

            //Check KEY3
            LDR R4, [R2]
            CMP R4, #8 //1000
            BEQ KEY3

            B INPUT_KEY //polled I/O

KEY0: //Subroutine for KEY0: Make 0
            MOV R0, #0 //Make 0
LOOP0:      LDR R6, [R2]
            CMP R6, #1
            BEQ LOOP0 //Loop until button Released

            LDRB R7, [R3, R0] //Load 0
            STR R7, [R1]
            B INPUT_KEY

KEY1: //Subroutine for KEY1: Increase 1
            ADD R0, #1 //+1
            CMP R0, #10 //If >10, back to 0
            MOVEQ R0, #0
LOOP1:      LDR R6, [R2]
            CMP R6, #2
            BEQ LOOP1 //Loop until button Released

            LDRB R7, [R3, R0]
            STR R7, [R1]
            B INPUT_KEY

KEY2: //Subroutine for KEY2: Decrease 1
            SUBS R0, #1 //-1
            MOVMI R0, #9 //If <0, back to 9
LOOP2:      LDR R6, [R2]
            CMP R6, #4
            BEQ LOOP2 //Loop until button Released

            LDRB R7, [R3, R0]
            STR R7, [R1]
            B INPUT_KEY

KEY3: //Subroutine for KEY3: Blank
            LDR R6, [R2]
            CMP R6, #8
            BEQ KEY3 //Loop until button Released
            MOV R0, #0
            STR R0, [R1] //Make Blank
ANY_KEY:    LDR R6, [R2] //Check KEY0
            CMP R6, #1
            BLEQ MAKE_0 //Make 0 if any KEY0
            BEQ INPUT_KEY //Go back to INPUT
    
            LDR R6, [R2] //Check KEY1
            CMP R6, #2
            BLEQ MAKE_0 //Make 0 if any KEY1
            BEQ INPUT_KEY //Go back to INPUT
    
            LDR R6, [R2] //Check KEY2
            CMP R6, #4
            BLEQ MAKE_0 //Make 0 if any KEY2
            BEQ INPUT_KEY //Go back to INPUT
    
            LDR R6, [R2] //Check KEY3
            CMP R6, #8
            BLEQ MAKE_0 //Make 0 if any KEY3
            BEQ INPUT_KEY //Go back to INPUT

            B ANY_KEY //Loop until Any Key is pressed

MAKE_0:     LDRB R7, [R3] //Load 0
            STR R7, [R1]
            BX LR

HEX_ADDR:   .word 0xFF200020
KEY_ADDR:   .word 0xFF200050

BIT_CODES:  .byte 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
            .byte 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111