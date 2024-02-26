#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsCommand.h";
#include "utilities.h";
using namespace std;

class clsCodeWriter
{
private:
	ifstream _outputFile;
	string fileName;

	void writeArithmetic(string arithmeticCommand)
	{

	}

	/*
	In the push method

	-(Local, argument, this, that). have thier own way in translating which is in pseudocode (addr = segmentPointer + i, *SP = *addr, SP++)
	push local i
	{
		@i
		D=A
		@LCL // it can be R1 == LCL, R2 = ARG, R3 = THIS, R4 = THAT
		A=D+M // addr = segmentPointer + i
		D=M
		@SP // *SP = *addr
		A=M
		M=D
		@SP //SP++
		M=M+1
	}

	-(constant). has unqic way also which is (*SP = i, SP++)
	or in assembly
	{
		// push constant i
		@i // i is a constant
		D=A
		@SP // R0 == SP
		A=M
		M=D //*SP = i
		@SP // SP++ // R0 == SP 
		M=M+1
	}

	-(static). has also a unqic way push static 5 (*SP = *staticVariableAddr, SP++)
	{
		@fileName.5 (assember alocat from RAM[16] - RAM[255])
		D=M 
		@SP // *SP = *staticVariableAddr // R0 == SP
		A=M
		M=D
		@SP // SP++ // R0 == SP
		M=M+1
	}

	-(temp). has also a unqic way push temp i (0 <= i <= 7) (addr = 5 + i, *SP = *addr, SP++) 
	{

		@i // (0 <= i <= 7)
		D=A
		@5 // Mapped on Ram location 5 to 12, 5 is the base address
		A=D+M // addr = 5 + i
		D=M
		@SP // *SP = *addr
		A=M
		M=D
		@SP //SP++
		M=M+1

	}


	-(pointer). has also a unqic way push point 0/1..
	A fixed, 2-place segment:
		accessing pointer 0 should result in accessing THIS
		accessing pointer 1 should result in accessing THAT
	(*sp = THIS/THAT, SP++)
	{
		if (i == 0) // THIS
		{
			@THIS
			D=M

		}
		else if (i == 1) // THAT
		{
			@THAT
			D=M
		}
		else
		{
			throw error
		}

		+

		@SP // *sp = THIS/THAT
		A=M
		M=D
		@SP //SP++
		M=M+1

	}

	*/

	void writePush(string command, int index)
	{

	}

	void writePop(string command, int index)
	{

	}
	
public:

	clsCodeWriter(const string& outputFilePath)
	{
		_outputFile.open(outputFilePath, ios::out);

		// taking the file name to use it with static variables

		fileName = outputFilePath;

		fileName.erase(0, fileName.find_last_of("/"));
		fileName.erase(fileName.find_first_of(".") + 1);

	}

	~clsCodeWriter()
	{
		if (_outputFile.is_open()) _outputFile.close();
	}

	void writeCommandToAsm(clsCommand* command)
	{
		switch (command->instructionType())
		{
		case C_ARITHMETIC:
			writeArithmetic(command->getArg1());
			break;
		case C_PUSH:

			// handling error in the constant
			if (command->getArg2() < 0)
			{
				cout << "Error I can't be less than 0" << endl;
				cout << "Instruction push " << command->getArg1() << " " << command->getArg2();
				throw "Error I can't be less than 0";	
			}

			writePush(command->getArg1(), command->getArg2());
			break;
		case C_POP:

			// handling error in the constant
			if (command->getArg2() < 0)
			{
				cout << "Error I can't be less than 0" << endl;
				cout << "Instruction push " << command->getArg1() << " " << command->getArg2();
				throw "Error I can't be less than 0";
				
			}

			writePop(command->getArg1(), command->getArg2());
			break;
		}
	}

};

