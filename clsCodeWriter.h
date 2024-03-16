#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "clsCommand.h";
#include "utilities.h";
using namespace std;
namespace fs = std::filesystem;

class clsCodeWriter
{
private:
	ofstream _outputFile;
	string fileName;

	int functionReturnCounter = 0;
	int labelCounter = 0;

	void writeInit()
	{
		// some code and the begining

		// Bootstrap code (should be written in assembly)

		/*
			@256 // SP = 256		
			D=A
			@SP
			M=D


		*/

		_outputFile << "// Bootstrap code\n";

		_outputFile << "@256\nD=A\n@SP\nM=D\n";

		string returnAddress = (fileName + "$ret." + to_string(functionReturnCounter));
		functionReturnCounter++;

		_outputFile << "@" + returnAddress + "\nD=A\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@LCL\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@ARG\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@THIS\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@THAT\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@SP\nD=M\n@5\nD=D-A\n@0\nD=D-A\n@ARG\nM=D\n";

		_outputFile << "@SP\nD=M\n@LCL\nM=D\n";

		_outputFile << "@Sys.init\n0;JMP\n";
		_outputFile << ("(" + returnAddress + ")\n");

	}

	void writeArithmetic(string arithmeticCommand)
	{
		_outputFile << "// " + arithmeticCommand + "\n";

		if (arithmeticCommand == "add")
		{
			/*
				add x + y //////////////////
			{
				// pop y

				@SP
				AM=M-1 //SP--
				D=M

				@R13
				M=D

				// pop x

				@SP
				AM=M-1 //SP--
				D=M

				// short cut
				@R13
				D=D+M // x + y

				// long way
				{
					@R14
					M=D

					// add x + y

					@R13
					D=M
					@R14
					D=D+M
				}

				// push sum

				@SP
				AM=M+1
				A=A-1
				M=D

			}
			*/

			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and sum
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D+M\n";
			// push sum
			
		}
		else if (arithmeticCommand == "sub")
		{
			/*
				sub x - y ///////////////////////
				{
				// pop y

					@SP
					AM=M-1 //SP--
					D=M

					@R13
					M=D

					// pop x

					@SP
					AM=M-1 //SP--
					D=M

					// short cut
					@R13
					D=D-M // x - y

					// long way
					{
						@R14
						M=D
			
						// sub x - y

						@R13
						D=M
						@R14
						D=D-M
					}

					// push difference

					@SP
					AM=M+1
					A=A-1
					M=D
				}
			*/

			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and diff
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D-M\n";
			// push diff
			

		}
		else if (arithmeticCommand == "neg")
		{
			/*
			neg -y /////////////////
				{
					// pop y

					@SP
					AM=M-1 //SP--
					D=M

					// neg D

					D=-D

					// push negation

					@SP
					AM=M+1
					A=A-1
					M=D

				}
			*/

			// pop y and neg D
			_outputFile << "@SP\nAM=M-1\nD=M\nD=-D\n";
			// push negation


		}
		else if (arithmeticCommand == "eq")
		{
			/*
			eq x == 0 /////////////
			{
				// pop y

				@SP
				AM=M-1 //SP--
				D=M

				@R13
				M=D

				// pop x

				@SP
				AM=M-1 //SP--
				D=M

				// short cut
				@R13
				D=D-M // x - y

				@TRUE
				D;JEQ

				@0
				D=A
				@END
				0;JMP

				(TRUE)
				@0
				D=A
				D=!D

				(END)
				@SP // push result
				AM=M+1
				A=A-1
				M=D
			}
			*/

			string TrueLabel = "TRUE" + to_string(labelCounter);
			string EndLabel = "END" + to_string(labelCounter);

			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and diff and conditio
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D-M\n@" + TrueLabel + "\nD;JEQ\n@0\nD=A\n@" + EndLabel + "\n0;JMP\n("+TrueLabel+")\n@0\nD=A\nD=!D\n("+EndLabel+")\n";
			// push result
			

			labelCounter++;
		}
		else if (arithmeticCommand == "gt")
		{
			/*
			gt x > y //////////////////////
			{
				// pop y

				@SP
				AM=M-1 //SP--
				D=M

				@R13
				M=D

				// pop x

				@SP
				AM=M-1 //SP--
				D=M

				// short cut
				@R13
				D=D-M // x - y

				@TRUE
				D;JGT

				@0
				D=A
				@END
				0;JMP

				(TRUE)
				@0
				D=A
				D=!D

				(END)
				@SP // push result
				AM=M+1
				A=A-1
				M=D
			}
			*/

			string TrueLabel = "TRUE" + to_string(labelCounter);
			string EndLabel = "END" + to_string(labelCounter);

			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and diff and conditio
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D-M\n@" + TrueLabel + "\nD;JGT\n@0\nD=A\n@" + EndLabel + "\n0;JMP\n(" + TrueLabel + ")\n@0\nD=A\nD=!D\n(" + EndLabel + ")\n";
			// push diff
			

			labelCounter++;
		}
		else if (arithmeticCommand == "lt")
		{
			/*
				lt x < y
			{
				// pop y

				@SP
				AM=M-1 //SP--
				D=M

				@R13
				M=D

				// pop x

				@SP
				AM=M-1 //SP--
				D=M

				// short cut
				@R13
				D=D-M // x - y

				@TRUE
				D;JLT

				@0
				D=A
				@END
				0;JMP

				(TRUE)
				@0
				D=A
				D=!D

				(END)
				@SP // push result
				AM=M+1
				A=A-1
				M=D
			}
			*/
			
			string TrueLabel = "TRUE" + to_string(labelCounter);
			string EndLabel = "END" + to_string(labelCounter);

			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and diff and conditio
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D-M\n@" + TrueLabel + "\nD;JLT\n@0\nD=A\n@" + EndLabel + "\n0;JMP\n(" + TrueLabel + ")\n@0\nD=A\nD=!D\n(" + EndLabel + ")\n";
			// push diff
			

			labelCounter++;

		}
		else if (arithmeticCommand == "and")
		{
			/*
				and x and y
			{
				// pop y

				@SP
				AM=M-1 //SP--
				D=M

				@R13
				M=D

				// pop x

				@SP
				AM=M-1 //SP--
				D=M

				// short cut
				@R13
				D=D&M // x and y

				@SP // push result
				AM=M+1
				A=A-1
				M=D
			}
			*/
			
			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and &
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D&M\n";
			// push result
			

		}
		else if (arithmeticCommand == "or")
		{
			/*
				or x or y
			{
			// pop y

				@SP
				AM=M-1 //SP--
				D=M

				@R13
				M=D

				// pop x

				@SP
				AM=M-1 //SP--
				D=M

				// short cut
				@R13
				D=D|M // x and y

				@SP // push result
				AM=M+1
				A=A-1
				M=D
			}
			*/

			// pop y
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nM=D\n";
			// pop x and &
			_outputFile << "@SP\nAM=M-1\nD=M\n@R13\nD=D|M\n";
			// push result
			
		}
		else if (arithmeticCommand == "not")
		{
			/*
			 not noty
			{
			// pop y

				@SP
				AM=M-1 //SP--
				D=M

				// neg D

				D=!D

				// push negation

				@SP
				AM=M+1
				A=A-1
				M=D
			}
			*/

			// pop y and neg D
			_outputFile << "@SP\nAM=M-1\nD=M\nD=!D\n";
			// push negation
			
		}

		_outputFile << "@SP\nAM=M+1\nA=A-1\nM=D\n";
	}

	void writePush(string command, int index)
	{
		//writing the VM commmand as a comment for debugging 
		_outputFile << "// push " + command + " " + to_string(index) + "\n";

		if (command == "constant")
		{
			/*
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
			*/

			_outputFile << "@" + to_string(index) + "\nD=A\n";
		}
		else if (command == "local")
		{
			/*
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
			*/

			_outputFile << "@" + to_string(index) + "\nD=A\n@LCL\nA=D+M\nD=M\n";
		}
		else if (command == "argument")
		{
			_outputFile << "@" + to_string(index) + "\nD=A\n@ARG\nA=D+M\nD=M\n";
		}
		else if (command == "this" )
		{
			_outputFile << "@" + to_string(index) + "\nD=A\n@THIS\nA=D+M\nD=M\n";
		}
		else if (command == "that")
		{
			_outputFile << "@" + to_string(index) + "\nD=A\n@THAT\nA=D+M\nD=M\n";
		}
		else if (command == "static")
		{
			/*
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
			*/

			_outputFile << "@" + fileName + "." + to_string(index) + "\nD=M\n";
		}
		else if (command == "temp")
		{
			/*
			-(temp). has also a unqic way push temp i (0 <= i <= 7) (addr = 5 + i, *SP = *addr, SP++) 
				{

					@i // (0 <= i <= 7)
					D=A
					@5 // Mapped on Ram location 5 to 12, 5 is the base address
					A=D+A // addr = 5 + i
					D=M
					@SP // *SP = *addr
					A=M
					M=D
					@SP //SP++
					M=M+1

				}
			*/

			_outputFile << "@" + to_string(index) + "\nD=A\n@5\nA=D+A\nD=M\n";
		}
		else if (command == "pointer")
		{
			/*
			-(pointer). has also a unqic way push point 0/1..
				A fixed, 2-place segment:
					accessing pointer 0 should result in accessing THIS
					accessing pointer 1 should result in accessing THAT
				(*sp = THIS/THAT, SP++)
				{
					if (i == 0) // THIS
					{
						@THIS
					}
					else if (i == 1) // THAT
					{
						@THAT
					}
					else
					{
						throw error
					}

					+

					// same
					D=M
					@SP // *sp = THIS/THAT 
					A=M
					M=D
					@SP //SP++
					M=M+1

				}
			*/


			if (index == 0)
			{
				_outputFile << "@THIS\nD=M\n";
			}
			else if (index == 1)
			{
				_outputFile << "@THAT\nD=M\n";
			}
			else
			{
				cout << "Error pointer constant: " << to_string(index) << " is not acceptable." << endl;
				throw "Error pointer constant: " + to_string(index) + " is not acceptable.";
			}
		}
		else
		{
			cout << "Error memory segment: " << command << " is not defined." << endl;
			throw "Error memory segment: " + command + " is not defined.";
		}

		// this code can be optimized
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";
	}

	void writePop(string command, int index)
	{
		//writing the VM commmand as a comment for debugging 
		_outputFile << "// pop " + command + " " + to_string(index) + "\n";

		if (command == "local")
		{
			/*
				-(Local, argument, this, that). have thier own way in translating which is in pseudocode (addr = segmentPointer + i, SP++, *addr = *SP)
				ex. push local i
				{
					@i
					D=A
					@LCL // it can be R1 == LCL, R2 = ARG, R3 = THIS, R4 = THAT
					D=D+M // addr = segmentPointer + i
					@R13
					M=D // store addr in temp

					@SP 
					AM=M-1 //SP--
					D=M // D = *SP

					@R13
					A=M // @addr
					M=D *addr = *SP
				}
			*/

			_outputFile << "@" + to_string(index) + "\nD=A\n@LCL\nD=D+M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if (command == "argument")
		{
			_outputFile << "@" + to_string(index) + "\nD=A\n@ARG\nD=D+M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if (command == "this")
		{
			_outputFile << "@" + to_string(index) + "\nD=A\n@THIS\nD=D+M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if (command == "that")
		{
			_outputFile << "@" + to_string(index) + "\nD=A\n@THAT\nD=D+M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if (command == "static")
		{
			/*
			-(static). have thier own way in translating which is in pseudocode ()
				pop static 5
				{
					@SP
					AM=M-1 //SP--
					D=M // D = *SP

					@fileName.5
					M=D
				}
			*/



			_outputFile <<"@SP\nAM=M-1\nD=M\n@" + fileName + "." + to_string(index) + "\nM=D\n";
		}
		else if (command == "temp")
		{
			/*
			-(temp). have thier own way in translating which is in pseudocode (addr = 5 + i, SP--, *addr = *SP)
				{
					@i // (0 <= i <= 7)
					D=A
					@5 // Mapped on Ram location 5 to 12, 5 is the base address
					D=D+A // addr = 5 + i
					@R13
					M=D // store addr in temp

					@SP
					AM=M-1 //SP--
					D=M // D = *SP

					@R13
					A=M // @addr
					M=D *addr = *SP

				}
			*/

			_outputFile << "@" + to_string(index) + "\nD=A\n@5\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if (command == "pointer")
		{
			/*
			-(pointer). have thier own way in translating which is in pseudocode (SP--, THIS/THAT = *SP)
				{
					@SP
					AM=M-1 //SP--
					D=M // D = *SP

					if (i == 0)
					{
						@THIS
						M=D
					}
					else if (i == 1)
					{
						@THAT
						M=D
					}
					else
					{
						Error
					}
				}
			*/


			_outputFile << "@SP\nAM=M-1\nD=M\n";

			if (index == 0)
			{
				_outputFile << "@THIS\nM=D\n";
			}
			else if (index == 1)
			{
				_outputFile << "@THAT\nM=D\n";
			}
			else
			{
				cout << "Error pointer constant: " << to_string(index) << " is not acceptable." << endl;
				throw "Error pointer constant: " + to_string(index) + " is not acceptable.";
			}

		}
		else
		{
			cout << "Error memory segment: " << command << " is not defined." << endl;
			throw "Error memory segment: " + command + " is not defined.";
		}

	}
	
	void writeLabel(string label)
	{
		_outputFile << "// label: " + label + "\n";

		/*
		VM:
			label LabelName
		Hack asm:
			(LabelName)
		*/

		_outputFile << ("(" + label + ")\n");
	}

	void writeGoto(string label)
	{
		_outputFile << "// writeGoto: " + label + "\n";

		/*
		VM:
			goto labelName
		Hack asm:
			@labelName
			0;JMP
		*/

		_outputFile << "@" + label + "\n0;JMP\n";

	}

	void writeIf(string label)
	{
		_outputFile << "// IF-goto : " + label + "\n";

		/*
		VM:
			if-goto labelName
		Hack asm:
			
			// pop y

			@SP
			AM=M-1 //SP--
			D=M
			
			@labelName // if D > 0 (true = 1x16, false = 0x16)
			D;JNE


		*/
		
		_outputFile << "@SP\nAM=M-1\nD=M\n";
		_outputFile << "@" + label + "\nD;JNE\n";
	}

	void writeFunction(string functionName, int numVars)
	{

		_outputFile << "// Function Label : " + functionName + "\n";
		/*
		assembly code:

		(functionName)			// declares a label for the function entry
			repeat nVars times: // nVars = number of local variables
			push 0				// initializes the local variables to 0

		Hack assembly:

		(functionName)
		c++ code
		for(int i = 0; i < numVars; i++)
		{
			@0 // i is a constant
			D=A
			@SP // R0 == SP
			A=M
			M=D //*SP = i
			@SP // SP++ // R0 == SP 
			M=M+1
		}


		*/


		_outputFile << "(" + functionName +")\n";

		for (int i = 0; i < numVars; i++)
		{
			_outputFile << "@" + to_string(0) + "\nD=A\n";
			_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";
		}
	}

	void writeCall(string functionName, int numArgs)
	{
		_outputFile << "// Function call : " + functionName + "\n";

		/*
			assembly code:

			push returnAddress
			push LCL
			push ARG
			push THIS
			push THAT
			ARG = SP - 5 - nArgs
			LCL = SP
			goto functionName
			(returnAddress)

			Hack assembly:

			@returnAddress //  -- push returnAddress --
			D=A
			@SP // R0 == SP
			A=M
			M=D //*SP = i
			@SP // SP++ // R0 == SP
			M=M+1

			@LCL //  -- push LCL --
			D=M
			@SP // R0 == SP
			A=M
			M=D //*SP = i
			@SP // SP++ // R0 == SP
			M=M+1

			@ARG //  -- push ARG --
			D=M
			@SP // R0 == SP
			A=M
			M=D //*SP = i
			@SP // SP++ // R0 == SP
			M=M+1

			@THIS //  -- push THIS --
			D=M
			@SP // R0 == SP
			A=M
			M=D //*SP = i
			@SP // SP++ // R0 == SP
			M=M+1

			@THAT //  -- push THAT --
			D=M
			@SP // R0 == SP
			A=M
			M=D //*SP = i
			@SP // SP++ // R0 == SP
			M=M+1

			-- ARG = SP - 5 - nArgs --

			@SP
			D=M
			@5 // i is a constant
			D=D-A
			@nArgs
			D=D-A
			@ARG 
			M=D

			-- LCL = SP -- 

			@SP
			D=M
			@LCL
			M=D

			@functionName
			0;JMP
			(returnAddress)
		*/

		string returnAddress = (fileName + "$" + "ret." + to_string(functionReturnCounter));
		functionReturnCounter++;

		_outputFile << "@" + returnAddress + "\nD=A\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@LCL\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@ARG\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@THIS\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@THAT\nD=M\n";
		_outputFile << "@SP\nA=M\nM=D\n@SP\nM=M+1\n";

		_outputFile << "@SP\nD=M\n@5\nD=D-A\n@" + to_string(numArgs) + "\nD=D-A\n@ARG\nM=D\n";

		_outputFile << "@SP\nD=M\n@LCL\nM=D\n";

		_outputFile << "@" + functionName + "\n0;JMP\n";
		_outputFile << ("(" + returnAddress + ")\n");
	}

	void writeReturn()
	{
		_outputFile << "// (Function return)\n";

		/*
			Hack assembly:

			@LCL //  -- endFrame = LCL --
			D=M
			@R13
			M=D

			@R13 // -- retAddr = *(endFrame - 5)
			D=M
			@5
			A=D-A
			D=M
			@R14
			M=D

			@SP // -- *ARG = pop() --
			AM=M-1 //SP--
			D=M // D = *SP
			@ARG
			A=M
			M=D

			@ARG // -- SP = ARG + 1 --
			D=M+1
			@SP
			M=D

			@R13 // -- THAT = *(endFrame - 1)
			A=M-1
			D=M
			@THAT 
			M=D

			@R13 // -- THIS = *(endFrame - 2)
			D=M
			@2
			A=D-A
			D=M
			@THIS
			M=D

			@R13 // -- ARG = *(endFrame - 3)
			D=M
			@3
			A=D-A
			D=M
			@ARG
			M=D

			@R13 // -- LCL = *(endFrame - 4)
			D=M
			@4
			A=D-A
			D=M
			@LCL
			M=D

			@R14 // -- goto retAddr
			A=M
			0;JMP
		*/

		_outputFile << "@LCL\nD=M\n@R13\nM=D\n";

		_outputFile << "@R13\nD=M\n@5\nA=D-A\nD=M\n@R14\nM=D\n";

		_outputFile << "@SP\nAM=M-1\nD=M\n@ARG\nA=M\nM=D\n";

		_outputFile << "@ARG\nD=M+1\n@SP\nM=D\n";

		_outputFile << "@R13\nD=M\n@1\nA=D-A\nD=M\n@THAT\nM=D\n";
		_outputFile << "@R13\nD=M\n@2\nA=D-A\nD=M\n@THIS\nM=D\n";
		_outputFile << "@R13\nD=M\n@3\nA=D-A\nD=M\n@ARG\nM=D\n";
		_outputFile << "@R13\nD=M\n@4\nA=D-A\nD=M\n@LCL\nM=D\n";

		_outputFile << "@R14\nA=M\n0;JMP\n";

	}

public:

	clsCodeWriter(const string& outputFilePath)
	{
		_outputFile.open(outputFilePath, ios::out);

		// taking the file name to use it with static variables

		fileName = outputFilePath;

		fileName.erase(0, fileName.find_last_of("/") + 1);
		fileName.erase(fileName.find_first_of("."));
	}

	clsCodeWriter(fs::path& directoryPath, const string& startingFileName = "boot")
	{
		string outputFilePath = directoryPath.string() + "/" + directoryPath.filename().string() + ".asm";

		_outputFile.open(outputFilePath, ios::out);

		fileName = startingFileName;

		// Bootstrap code (should be written in assembly)
		writeInit();
	}

	~clsCodeWriter()
	{
		if (_outputFile.is_open()) _outputFile.close();
	}

	void setFileName(string _FileName)
	{

		_outputFile << "/////////////////////////////// From " + this->fileName + " ---> " + _FileName + " ////////////////////////////////\n";

		this->fileName = _FileName;
		labelCounter = 0;
		functionReturnCounter = 0;
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
				cout << "Error no index is declared" << endl;
				cout << "Instruction push " << command->getArg1() << " " << command->getArg2();
				throw "Error no index is declared";	
			}

			writePush(command->getArg1(), command->getArg2());
			break;
		case C_POP:

			// handling error in the constant
			if (command->getArg2() < 0)
			{
				cout << "Error no index is declared" << endl;
				cout << "Instruction push " << command->getArg1() << " " << command->getArg2();
				throw "Error no index is declared";
				
			}

			writePop(command->getArg1(), command->getArg2());
			break;

		case C_LABEL:
			writeLabel(command->getArg1());
			break;
		case C_GOTO:
			writeGoto(command->getArg1());
			break;
		case C_IF:
			writeIf(command->getArg1());
			break;
		case C_FUNCTION:
			writeFunction(command->getArg1(), command->getArg2());
			break;
		case C_CALL:
			writeCall(command->getArg1(), command->getArg2());
			break;
		case C_RETURN:
			writeReturn();
			break;
		}
	}

};

