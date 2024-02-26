#pragma once
#include <iostream>
#include <string>
using namespace std;

string removeComments(string str)
{
	size_t found = str.find("//");

	if (found != string::npos)
	{
		return str.substr(0, found);
	}

	return str;
}