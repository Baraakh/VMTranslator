#include <iostream>
#include "clsParser.h";
using namespace std;

int main()
{
    clsParser parser("C:/Users/minga/source/repos/VMTranslator/MemoryAccess/StaticTest/StaticTest.vm");

    while (parser.hasMoreCommands())
    {
        cout << "\"" << parser.getCurrentCommand() << "\"" << endl;
        parser.advance();
    }

    return 0;
}