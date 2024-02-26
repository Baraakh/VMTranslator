#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "utilities.h";
using namespace std;

class clsParser
{
private:

	ifstream _intputFile;
	// Will be CHANGED
	string _currentCommand;
	bool _hasMoreCommands;

public:

	clsParser(const string& inputFilePath)
	{
		_intputFile.open(inputFilePath, ios::in);
		advance();
	}

	~clsParser()
	{
		if (_intputFile.is_open()) _intputFile.close();
	}

	bool hasMoreCommands()
	{
		return _hasMoreCommands;
	}

	void advance()
	{
		if (getline(_intputFile, _currentCommand))
		{
			_currentCommand = removeComments(_currentCommand);

			_currentCommand.erase(0, _currentCommand.find_first_not_of(" \t\r\n"));
			_currentCommand.erase(_currentCommand.find_last_not_of(" \t\r\n") + 1);

			// if the current Line empty It will go the next line 
			if (_currentCommand == "") advance();

			_hasMoreCommands = true;
		}
		else
		{
			_hasMoreCommands = false;
		}
	}

	// WILL be CHANGED
	string getCurrentCommand()
	{
		return _currentCommand;
	}

};

