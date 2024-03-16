#include <iostream>
#include <filesystem>
#include "clsParser.h";
#include "clsCodeWriter.h";
#include "utilities.h";
using namespace std;
namespace fs = std::filesystem;

int main()
{
    string PATH = "C:/Users/minga/Desktop/webprogrammer/Nand2Tetris/nand2tetris/projects/08/FunctionCalls/StaticsTest";
    fs::path pathObj(PATH);

    if (fs::exists(pathObj)) {
        if (fs::is_regular_file(pathObj)) {
            cout << PATH << " is a regular file." << endl;

            string OUTPUT_FILE_PATH;

            // genrating the output file path
            OUTPUT_FILE_PATH = PATH.substr(0, PATH.find_first_of("."));
            OUTPUT_FILE_PATH += ".asm";

            clsParser parser(PATH);
            clsCodeWriter codeWriter(OUTPUT_FILE_PATH);

            while (parser.hasMoreCommands())
            {
                clsCommand* currentCommand = parser.getCurrentCommand();

                codeWriter.writeCommandToAsm(currentCommand);

                parser.advance(); // go to next instruction

                delete currentCommand;
            }

            cout << "OUTPUT FilePath: " << OUTPUT_FILE_PATH << endl;

        }
        else if (fs::is_directory(pathObj)) {
            std::cout << PATH << " is a directory." << std::endl;

            /*
                psuedo code
  
                get all the .vm files paths

                codeWriter(firstFilePath);

                for path in filesPaths
                    clsParser(path)
                    codeWriter.setFile(fileName)

                    while (parser.hasMoreCommands())
                    {
                        clsCommand* currentCommand = parser.getCurrentCommand();

                        codeWriter.writeCommandToAsm(currentCommand);

                        parser.advance(); // go to next instruction

                        delete currentCommand;
                    }
                    
            */
            
            clsCodeWriter codeWriter(pathObj);

            for (const auto& file : fs::directory_iterator(pathObj))
            {
                if (fs::is_regular_file(file)) {
                    if (file.path().extension() == ".vm") {

                        clsParser parser(file.path().string());

                        string fileName = file.path().filename().string();
                        fileName.erase(fileName.find_first_of("."));

                        codeWriter.setFileName(fileName);

                        while (parser.hasMoreCommands())
                        {
                            clsCommand* currentCommand = parser.getCurrentCommand();

                            codeWriter.writeCommandToAsm(currentCommand);

                            parser.advance(); // go to next instruction

                            delete currentCommand;
                        }
                    }
                }
            }

            cout << "OUTPUT FilePath: " << pathObj.string() + "/" + pathObj.filename().string() + ".asm" << endl;
        }
        else {
            std::cout << PATH << " is neither a regular file nor a directory." << std::endl;
            return 0;
        }
    }
    else {
        std::cout << PATH << " does not exist." << std::endl;
        return 0;
    }

    
    cout << "\nTranslating the VM code into HACK assembly has been successfully done :)." << endl;

    return 0;
}