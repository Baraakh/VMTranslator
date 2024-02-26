#pragma once
#include <iostream>
#include <vector>
using namespace std;

enum CommandType {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL};

class clsCommand
{
private:

public:

	virtual enum CommandType instructionType() = 0;

	virtual string getArg1() { return ""; }

	virtual int getArg2() { return -1; }
};

class clsCArithmetic : public clsCommand
{
private:

	string _Arg1;

public:

	clsCArithmetic(string arg1)
	{
		_Arg1 = arg1;
	}

	enum CommandType instructionType()
	{
		return C_ARITHMETIC;
	}

	string getArg1() { return _Arg1; }
};

class clsCPush : public clsCommand
{
private:

	string _Arg1;
	int _Arg2;

public:

	clsCPush(string arg1, int arg2)
	{
		_Arg1 = arg1;
		_Arg2 = arg2;
	}

	enum CommandType instructionType()
	{
		return C_PUSH;
	}

	string getArg1() { return _Arg1; }

	int getArg2() { return _Arg2; }
};

class clsCPop : public clsCommand
{
private:

	string _Arg1;
	int _Arg2;

public:

	clsCPop(string arg1, int arg2)
	{
		_Arg1 = arg1;
		_Arg2 = arg2;
	}

	enum CommandType instructionType()
	{
		return C_POP;
	}

	string getArg1() { return _Arg1; }

	int getArg2() { return _Arg2; }
};
