// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R0
D=M
@multcand
M=D   // store R0

@R1
D=M
@multiple
M=D    // store R1

@sum
M=0

(LOOP)
@multiple
D=M
@STOP
D;JEQ

@multcand
D=M
@sum
M=D+M


@multiple
D=M
M=D-1

@LOOP
0;JEQ



(STOP)
@sum
D=M
@R2
M=D

(END)
@END
0;JMP
