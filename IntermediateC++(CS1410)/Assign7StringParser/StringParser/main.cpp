/**
* @file main.cpp
*
* @brief File containing the implementation of main
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>

#include "StringParser.hpp"

/**
* @brief Main
*
* @param argc The number of command line arguments
* @param pArgv The array of command line arguments
*
* @return 0
*/
int main(int argc, char** pArgv)
{
	StringParser parser;

	if (argc > 1)
	{
		if (!parser.parseFile(pArgv[1]))
		{
			printf("Parsing of file %s failed\n", pArgv[1]);
		}
	}
	else
	{
		printf("Usage:\n%s <input file>\n", pArgv[0]);
	}

	return 0;
}