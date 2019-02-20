#include<iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

#include "StringParser.hpp"

/**
* @brief The constructor
*/
StringParser::StringParser(void)
{
	// Empty
}

/**
* @brief Parse a file line by line
*
* @param pFileName The file name
*
* @return True if parse was successful, else false
*/
bool StringParser::parseFile(const char* pFileName)
{
	bool ret = true;
	std::ifstream file(pFileName, std::ifstream::in);

	if (file.is_open())
	{
		char aLine[MAX_LINE_LENGTH];

		memset(aLine, 0, MAX_LINE_LENGTH);

		while (!file.eof() && ret)
		{
			file.getline(aLine, MAX_LINE_LENGTH);

			int length = strlen(aLine);
			if (length > 0)
			{
				ret = parseLine(aLine, length);
				printf("\n");
				memset(aLine, 0, length);
			}
		}

		if (ret)
		{
			printf("Parsing of file %s is complete\n", pFileName);
		}

		file.close();
	}
	else
	{
		ret = false;
	}

	return ret;
}

/**
* @brief Parse a line of the input file
*
* @param pLine The input line
* @param length the length of the input file
*
* @return True if line was successfully parse, else false
*/
bool StringParser::parseLine(const char* pLine, int length)
{
	char *command=new char[8];
	char *argument=new char[length];

	memset(command, 0, 8);
	memset(argument, 0, length);
	char delim;
	bool ret = true;
	int i = 0;
	for (i; pLine[i] != ':' && pLine[i]!='~'; i++) {
		command[i] = pLine[i];
		if (pLine[i] == '\0') ret = false;
	}
	delim = pLine[i];
	i++;
	int p = 0;
	for (i; i < length; i++) {
		argument[p] = pLine[i];
		p++;
	}
	ret = parseCommand(command, delim, argument);
	return ret;
}

/**
* @brief Parse a command
*
* @param pCommand The command string
* @param delimiter The delimiter between command and arguments
* @param pArgument The command argument
*
* @return True if successfully parsed, else false
*/
bool StringParser::parseCommand(const char* pCommand, char delimiter, const char* pArgument){
	int length = strlen(pCommand);
	if(length==1){
		if (strcmp(pCommand,"I")==0) {
			int a=parseInt(pArgument);
			std::cout << "Integer: " << a << std::endl;
		}
			
		else if (strcmp(pCommand, "F")==0) {
			float b=parseFloat(pArgument);
			std::cout << "Float: " << b << std::endl;

		}
		else if (strcmp(pCommand,"D")==0) {
			double c=parseDouble(pArgument);
			std::cout << "Double: " << c << std::endl;
		}
		else if (strcmp(pCommand,"S")==0) {
			char* c=parseString(pArgument);
			std::cout << "String: " << c << std::endl;
		}
		else if (strcmp(pCommand, "Y")==0) {
			int length = strlen(pArgument);
			char *args = new char(length);
			memset(args, 0, length);
			int k = 0;

			for (int i = 0; i<length; i++) {
				if (pArgument[i] == '~') {
					parseLine(args, strlen(args));
					k = 0;
					memset(args, 0, length);
				}
				else {
					args[k] = pArgument[i];
					k++;
				}
			}
			parseLine(args, strlen(args));

		}
	}
	if (length > 1) {
		char choice;
		int length = strlen(pArgument);
		char *args = new char(length);
		memset(args, 0, length);
		char *args2 = new char(length);
		memset(args2, 0, length);
		int i = 0;
		for (i; pArgument[i] != ':'; i++) {
			args[i] = pArgument[i];
		}
		if (pArgument[i + 1] == 'C') {
			choice = 'c';
			i = i + 8;
		}
		else {
			choice = 's';
			i = i + 11;
		}
		int k = 0;
		for (i; i < strlen(pArgument); i++) {
			args2[k++] = pArgument[i];
		}
		if (choice == 'c') {
			strcat(args, args2);
			char *b = parseString(args);
			std::cout << "Concat: " << b << std::endl;
		}
		if (choice == 's') {
			int begin=0, end=0;
			int a = 0;
			while (args2[a] != ':') {
				begin = begin * 10 + (args2[a] - '0');
				a++;
			}
			a++;
			while (args2[a] != '\0') {
				end = end * 10 + (args2[a] - '0');
				a++;
			}

			k = 0;
			memset(args2, 0, strlen(pArgument));
			for (int i = begin; i < begin+end; i++) {
				args2[k++] = args[i];
			}
		
			//char*b = parseString(args);
			std::cout << "Substring: " << args2 << std::endl;
		}
	}
	return true;
}

/**
* @brief Convert a double string into a double
*
* @param pDouble The string containing the double
*
* @return A double
*/
double StringParser::parseDouble(const char* pDouble)
{
	double pdbl;
	pdbl = atof(pDouble);
	return pdbl;
}

/**
* @brief Convert a float string into a float
*
* @param pFloat The string containing the float
*
* @return The float
*/
float StringParser::parseFloat(const char* pFloat)
{
	float pflt;
	pflt = atof(pFloat);
	return pflt;
}

/**
* @brief Convert an integer string into an integer
*
* @param pInt The string containing the integer
*
* @return The integer
*/
int StringParser::parseInt(const char* pInt)
{
	int pInteger;
	pInteger = atoi(pInt);
	return pInteger;
}

/**
* @brief Convert a constant character string into a c-string
*
* @param pString The original string
*
* @return The new c-string
*/
char* StringParser::parseString(const char* pString)
{
	//char *toR= new char[strlen(pString)];
	return _strdup(pString);
}

// TODO Place any extra functions below here