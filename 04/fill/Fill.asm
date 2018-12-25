// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
//@24576
@24576
D=A
@endscreen
M=D

(CHECKSCREEN)
@SCREEN
D=A
@screenaddr
M=D      // setting start point

@SCREEN
D=M
D=D+1
@KEYPROBE
D;JGT

(ERASE)
@endscreen
D=M
@screenaddr
D=D-M
@KEYPROBE
D;JEQ

@screenaddr
A=M
M=0
@screenaddr
M=M+1
@ERASE
0;JMP

(KEYPROBE)
@KBD
D=M
@CHECKSCREEN
D;JEQ



(FILL)
@endscreen
D=M
@screenaddr
D=D-M
@KEYPROBE
D;JEQ

@screenaddr
A=M
M=-1

@screenaddr
M=M+1

@FILL
0;JEQ
