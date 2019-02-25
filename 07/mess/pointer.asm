// NOTE IN HACK ASM *p means accessing an address, NOT dereference
// *p == RAM[p]


//set R[16] = 5
@5
D=A
@p
M=D

//set R[17] = 10
@10
D=A
@q
M=D


// *q = 1
@1
D=A
@q
A=M
M=D


// Access element one above pointer, set next value to 1
@q
A=M+1
M=D

// var = *p
@p
A=M
D=M

// Incrementing a value stored
@p
M=M+1


// Example of stack pointer
@256
D=A
@R0
M=D

@200
D=A
@R0
A=M
M=D
@R0
M=M+1
A=M
M=D



