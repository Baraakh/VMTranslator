// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// eq
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE0
D;JEQ
@0
D=A
@END0
0;JMP
(TRUE0)
@0
D=A
D=!D
(END0)
@SP
AM=M+1
A=A-1
M=D
// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
// eq
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE1
D;JEQ
@0
D=A
@END1
0;JMP
(TRUE1)
@0
D=A
D=!D
(END1)
@SP
AM=M+1
A=A-1
M=D
// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// eq
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE2
D;JEQ
@0
D=A
@END2
0;JMP
(TRUE2)
@0
D=A
D=!D
(END2)
@SP
AM=M+1
A=A-1
M=D
// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE3
D;JLT
@0
D=A
@END3
0;JMP
(TRUE3)
@0
D=A
D=!D
(END3)
@SP
AM=M+1
A=A-1
M=D
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE4
D;JLT
@0
D=A
@END4
0;JMP
(TRUE4)
@0
D=A
D=!D
(END4)
@SP
AM=M+1
A=A-1
M=D
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE5
D;JLT
@0
D=A
@END5
0;JMP
(TRUE5)
@0
D=A
D=!D
(END5)
@SP
AM=M+1
A=A-1
M=D
// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE6
D;JGT
@0
D=A
@END6
0;JMP
(TRUE6)
@0
D=A
D=!D
(END6)
@SP
AM=M+1
A=A-1
M=D
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE7
D;JGT
@0
D=A
@END7
0;JMP
(TRUE7)
@0
D=A
D=!D
(END7)
@SP
AM=M+1
A=A-1
M=D
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@TRUE8
D;JGT
@0
D=A
@END8
0;JMP
(TRUE8)
@0
D=A
D=!D
(END8)
@SP
AM=M+1
A=A-1
M=D
// push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 53
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D+M
@SP
AM=M+1
A=A-1
M=D
// push constant 112
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
// sub
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D-M
@SP
AM=M+1
A=A-1
M=D
// neg
@SP
AM=M-1
D=M
D=-D
@SP
AM=M+1
A=A-1
M=D
// and
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D&M
@SP
AM=M+1
A=A-1
M=D
// push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
// or
@SP
AM=M-1
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
D=D|M
@SP
AM=M+1
A=A-1
M=D
// not
@SP
AM=M-1
D=M
D=!D
@SP
AM=M+1
A=A-1
M=D
