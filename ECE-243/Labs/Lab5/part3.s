    .text
    .global _start
_start:
	        MOV R0, #0 //R0: display value
            LDR R1, HEX_ADDR //R1: HEX address
            LDR R2, KEY_ADDR //R2: KEY address
            MOV R4, #BIT_CODES //R4: BIT Codes
            LDR R5, EDGE_ADDR //R5: Edge address
            MOV R10, #0b1111
            LDR R11, TIMER_ADDR //R11: Timer address
    
MAIN:
	        MOV R3, R0
	        BL DIVIDE
	        BL DISPLAY    
            BL DO_DELAY
            ADD R0, R0, #1
            CMP R0, #100
            MOVEQ R0, #0 //If 100, reset to 0
            LDR R9, [R5] //Load Edge Register Value
            AND R9, R9, R10
            STR R9, [R5] //Reset Edge Captures
            CMP R9, #0
            BLNE WAIT_KEY
    
            B MAIN

WAIT_KEY:
	        LDR R6, [R5] //Load Edge Register Value
            AND R6, R6, R10
            STR R6, [R5] //Reset Edge Captures
            CMP R6, #0
            BXNE LR
            B WAIT_KEY 

/* 0.25s delay counter with TIMER */
//200Mhz
DO_DELAY:
	        LDR R6, =50000000 //(1/200000000)*50000000 = 0.25s
            STR R6, [R11] //Load Value to TIMER
            MOV R6, #1
            STR R6, [R11, #8] //E=1
            MOV R8, #1
SUB_LOOP:
            LDR R7, [R11, #12]
            CMP R7, #1 //If reaches 0, R7=F=1
            STREQ R8, [R11, #12] //Set F=1 (means Reset F)
            BXEQ LR
            BNE SUB_LOOP

/* R3 is inputed value
 * Subroutine to perform the integer division R3 / 10.
 * Returns: quotient in R7, and remainder in R3
 */
DIVIDE:     MOV    R7, #0
CONT:       CMP    R3, #10 //Compare R3 (remainder) to 10
            BLT    DIV_END
            SUB    R3, #10 //Subtract by chosen divisor
            ADD    R7, #1
            B      CONT
DIV_END:    BX     LR

    
//R7 - Tens
//R3 - Ones
DISPLAY:
	        LDRB R7, [R4, R7]
            LDRB R6, [R4, R3]
            LSL R7, #8
            ORR R7, R7, R6
            STR R7, [R1]
            BX LR
       
HEX_ADDR:   .word 0xFF200020
KEY_ADDR:   .word 0xFF200050 
EDGE_ADDR:  .word 0xFF20005C
TIMER_ADDR: .word 0xFFFEC600

BIT_CODES:  .byte 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
            .byte 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111


