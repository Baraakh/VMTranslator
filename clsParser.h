#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "utilities.h";
#include "clsCommand.h";
using namespace std;

class clsParser
{
private:

	ifstream _intputFile;
	vector<string> _vCurrentCommand;
	bool _hasMoreCommands;
	
	map<string, CommandType> _CommandType = {
		{ "add", CommandType::C_ARITHMETIC},
		{ "sub", CommandType::C_ARITHMETIC},
		{ "neg", CommandType::C_ARITHMETIC},
		{ "eq", CommandType::C_ARITHMETIC},
		{ "gt", CommandType::C_ARITHMETIC},
		{ "lt", CommandType::C_ARITHMETIC},
		{ "and", CommandType::C_ARITHMETIC},
		{ "or", CommandType::C_ARITHMETIC},
		{ "not", CommandType::C_ARITHMETIC},
		{ "push", CommandType::C_PUSH},
		{ "pop", CommandType::C_POP},
		{"label", CommandType::C_LABEL},
		{"goto", CommandType::C_GOTO},
		{"if-goto", CommandType::C_IF}
	};

	enum CommandType chechType()
	{
		if (_CommandType.find(_vCurrentCommand[0]) != _CommandType.end())
		{
			return _CommandType[_vCurrentCommand[0]];
		}
		else
		{
			cout << "Error Command: " << _vCurrentCommand[0] << " is not found" << endl;
			throw "Error Command: " + _vCurrentCommand[0] + " is not found";
		}

	}

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
		string _currentCommand;

		if (getline(_intputFile, _currentCommand))
		{
			_currentCommand = removeComments(_currentCommand);

			_currentCommand.erase(0, _currentCommand.find_first_not_of(" \t\r\n"));
			_currentCommand.erase(_currentCommand.find_last_not_of(" \t\r\n") + 1);

			// if the current Line empty It will go the next line 
			if (_currentCommand == "") return advance();

			_hasMoreCommands = true;

			_vCurrentCommand = split(_currentCommand, " ");

		}
		else
		{
			_hasMoreCommands = false;
		}
	}

	clsCommand* getCurrentCommand()
	{
		CommandType Ctype = chechType();

		clsCommand* command = nullptr;

		// here must be some exception handling but it's ok.

		switch (Ctype)
		{
		case C_ARITHMETIC:
			command = new clsCArithmetic(_vCurrentCommand[0]);
			break;
		case C_PUSH:
			command = new clsCPush(_vCurrentCommand[1], stoi(_vCurrentCommand[2]));
			break;
		case C_POP:
			command = new clsCPop(_vCurrentCommand[1], stoi(_vCurrentCommand[2]));
			break;
		case C_LABEL:
			command = new clsCLabel(_vCurrentCommand[1]);
			break;
		case C_GOTO:
			command = new clsCGoto(_vCurrentCommand[1]);
			break;
		case C_IF:
			command = new clsCIf(_vCurrentCommand[1]);
			break;
		}

		return command;
	}

};

