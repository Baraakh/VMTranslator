#include <iostream>
#include "clsParser.h";
#include "clsCodeWriter.h";
#include "utilities.h";
using namespace std;

int main()
{
    string FILE_PATH = "C:/Users/minga/source/repos/VMTranslator/StackArithmetic/StackTest/StackTest.vm";
    string OUTPUT_FILE_PATH;

    // genrating the output file path
    OUTPUT_FILE_PATH = FILE_PATH.substr(0, FILE_PATH.find_first_of("."));
    OUTPUT_FILE_PATH += ".asm";

    clsParser parser(FILE_PATH);
    clsCodeWriter codeWriter(OUTPUT_FILE_PATH);

    while (parser.hasMoreCommands())
    {
        clsCommand* currentCommand = parser.getCurrentCommand();

        codeWriter.writeCommandToAsm(currentCommand);

        parser.advance(); // go to next instruction

        delete currentCommand;
    }

    return 0;
}