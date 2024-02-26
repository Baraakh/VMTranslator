#include <iostream>
#include "clsParser.h";
using namespace std;

int main()
{
    clsParser parser("C:/Users/minga/source/repos/VMTranslator/StackArithmetic/StackTest/StackTest.vm");

    while (parser.hasMoreCommands())
    {
        clsCommand* currentCommand = parser.getCurrentCommand();

        cout << "Command Type: " << currentCommand->instructionType() << " Arg1: " << currentCommand->getArg1() << " Agr2: " << currentCommand->getArg2() << endl;
        parser.advance();
    }

    return 0;
}