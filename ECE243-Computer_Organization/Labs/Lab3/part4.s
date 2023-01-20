/* Program that converts a binary number to decimal */
           .text               // executable code follows
           .global _start
_start:
            MOV    R4, #N
            MOV    R5, #Digits  // R5 points to the decimal digits storage location
            LDR    R4, [R4]     // R4 holds N
            MOV    R0, R4       // parameter for DIVIDE goes in R0
            BL     DIVIDE
            STRB   R1, [R5, #1] // Tens digit is now in R1
            STRB   R0, [R5]     // Ones digit is in R0
END:        B      END

/* Subroutine to perform the integer division R0 / 10.
 * Returns: quotient in R1, and remainder in R0
*/
DIVIDE:     MOV    R2, #0
CONT:       CMP    R0, #10
            BLT    DIV_END
            SUB    R0, #10
            ADD    R2, #1
            B      CONT
DIV_END:    MOV    R1, R2     // quotient in R1 (remainder in R0)
            MOV    PC, LR

N:          .word  76         // the decimal number to be converted
Digits:     .space 4          // storage space for the decimal digits

            .end




/* Program that converts a binary number to decimal */
           .text               // executable code follows
           .global _start
_start:
            MOV    R4, #N
            MOV    R5, #Digits  // R5 points to the decimal digits storage location
            LDR    R4, [R4]     // R4 holds N
            MOV    R0, R4       // parameter for DIVIDE goes in R0
            BL     DIVIDE
	        STRB   R8, [R5, #3] 
	        STRB   R7, [R5, #2]
            STRB   R1, [R5, #1] // Tens digit is now in R1
            STRB   R0, [R5]     // Ones digit is in R0
END:        B      END

/* Subroutine to perform the integer division R0 / 10.
 * Returns: quotient in R1, and remainder in R0
*/
DIVIDE:     MOV    R2, #0
CONT1:      CMP    R0, #1000
            BLT    CONT1_END
            SUB    R0, #1000
            ADD    R2, #1
            B      CONT1
CONT1_END:  MOV    R8, R2
	    MOV    R2, #0

CONT2:      CMP    R0, #100
            BLT    CONT2_END
            SUB    R0, #100
            ADD    R2, #1
            B      CONT2
CONT2_END:  MOV    R7, R2
	    MOV    R2, #0

CONT3:      CMP    R0, #10
            BLT    DIV_END
            SUB    R0, #10
            ADD    R2, #1
            B      CONT3

DIV_END:    MOV    R1, R2     // quotient in R1 (remainder in R0)
            MOV    PC, LR

N:          .word  9876         // the decimal number to be converted
Digits:     .space 4          // storage space for the decimal digits

            .end
