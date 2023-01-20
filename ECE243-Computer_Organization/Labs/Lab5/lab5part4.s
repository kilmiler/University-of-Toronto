.global _start
_start:
	MOV R7, #0 // R7 holds the display value
    LDR R4, KEY_ADDRESS // R4 points to the KEY address
    LDR R5, HEX_ADDRESS // R5 points to the HEX address
    MOV R6, #BIT_CODES
    LDR R8, EDGE_ADDRESS
    MOV R10, #0b1111
    LDR R11, TIMER_ADDRESS
    LDR R12, =6000 // To check if the timer has reached the limit
    
MAIN:
	MOV R0, R7
	BL DIVIDE
    PUSH {R0} //Save Ones Digit
    MOV R0, R2 //Save the quotient into dividend
    BL DIVIDE
    PUSH {R0} //Save Tens digit
    MOV R0, R2
    BL DIVIDE
    MOV R3, R2 // Now R3 has thousands digit
    MOV R2, R0 // Now R2 has hundreds digit
	POP {R1} // Now R1 has tens digit
    POP {R0} // Now R0 has ones digit
	BL DISPLAY    
    BL DELAY
    ADD R7, R7, #1
    CMP R7, R12 //Compare with 6000
    MOVEQ R7, #0 //if the incremented value is 6000, reset it back to 0
    LDR R9, [R8] //Load the edge register value
    AND R9, R9, R10
    STR R9, [R8] //Reset the edge captures
    CMP R9, #0
    BLNE WAIT_FOR_ANOTHER_KEY_PRESS
    
    B MAIN


WAIT_FOR_ANOTHER_KEY_PRESS:
	LDR R1, [R8] //Load the edge register value
    AND R1, R1, R10
    STR R1, [R8] //Reset the edge captures
    CMP R1, #0
    BXNE LR
    B WAIT_FOR_ANOTHER_KEY_PRESS 

/* 0.01 seconds delay
 */
DELAY:
	LDR R1, =2000000 // Save the constant for the timer - 0.01s
    STR R1, [R11]
    MOV R1, #1 // To activate the counter
    STR R1, [R11, #8] // Now the E bit is set to 1
    MOV R3, #1
SUB_LOOP:
	LDR R2, [R11, #12] // Check for the interrupt status
    CMP R2, #1 // Check if the counter has hit 0 (If F=1)
    STREQ R3, [R11, #12] // Reset the interrupt status if it becomes 1
    BXEQ LR
    B SUB_LOOP


/* Subroutine to perform the integer division R0 / 10.
 * Returns: quotient in R2, and remainder in R0
 */
DIVIDE:     MOV    R2, #0
CONT:       CMP    R0, #10 	  // Compare R0 (remainder) to 10
            BXLT   LR
            SUB    R0, #10	  // Subtract by chosen divisor
            ADD    R2, #1
            B      CONT
    
/* Input: R3 - Thoudsands digit
 *		  R2 - Hundreds digit
 *		  R1 - Tens digit
 *		  R0 - Ones digit
 */
DISPLAY:
	// Load proper bit codes
	LDRB R3, [R6, R3]
    LSL R3, #24
	LDRB R2, [R6, R2]
    LSL R2, #16
    LDRB R1, [R6, R1]
    LSL R1, #8
    LDRB R0, [R6, R0]
    
    // Sum up all digits
    ORR R3, R3, R2
    ORR R3, R3, R1
    ORR R3, R3, R0
    
    // Display the result
    STR R3, [R5]
    BX LR
    
KEY_ADDRESS: .word 0xFF200050 
HEX_ADDRESS: .word 0xFF200020
EDGE_ADDRESS: .word 0xFF20005C
TIMER_ADDRESS: .word 0xFFFEC600

BIT_CODES: .byte 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
    .byte 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111


