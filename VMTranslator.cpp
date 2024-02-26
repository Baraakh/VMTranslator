#include <iostream>
#include "clsParser.h";
#include "clsCodeWriter.h";
#include "utilities.h";
using namespace std;

int main()
{
    string FILE_PATH = "C:/Users/minga/source/repos/VMTranslator/StackArithmetic/StackTest/StackTest.vm";
    string OUTPUT_FILE_PATH;

    clsParser parser(FILE_PATH);

    // genrating the output file path
    vector<string> vPath = split(FILE_PATH, ".");
    OUTPUT_FILE_PATH = vPath[0] + ".asm";

    clsCodeWriter codeWriter(OUTPUT_FILE_PATH);

    while (parser.hasMoreCommands())
    {
        clsCommand* currentCommand = parser.getCurrentCommand();

        //cout << "Command Type: " << currentCommand->instructionType() << " Arg1: " << currentCommand->getArg1() << " Agr2: " << currentCommand->getArg2() << endl;
        


        parser.advance();

        delete currentCommand;
    }

    return 0;
}