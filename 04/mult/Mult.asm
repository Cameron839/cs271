// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here


@R2		//Set the result 'R2' to 0
M=0

@R0		// Jump into STEP if R0 > 0
D=M
@STEP
D;JGT

@END		//If no jump occurred, go to the end. 
0;JMP

(STEP)
@R2		//Get R2
D=M		//D = R2

@R1		//Get R1
D=D+M	//Add R1 to R2

@R2		//Get R2
M=D		//Put result back into R2

@R0		//Get R0
D=M-1	//Reduce R0 by 1
M=D


@STEP
D;JGT	//If R0 is still > 0 then loop.

(END)	//Loop
@END
0;JMP
