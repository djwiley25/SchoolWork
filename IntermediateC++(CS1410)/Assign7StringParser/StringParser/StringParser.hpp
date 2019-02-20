#ifndef _STRING_PARSER_HPP
#define _STRING_PARSER_HPP

/**
* @class StringParser
*
* @brief A class used to parse a set of string conversion and manipulation arguments
*/
class StringParser
{
public:
	StringParser();

	bool parseFile(const char* pFile);

	/**
	* @brief Important values
	*/
	enum
	{
		MAX_LINE_LENGTH = 1000000

		// TODO add enums as needed
	};

private:
	bool parseCommand(const char* pCommand, char delimiter, const char* pArgument);
	bool parseLine(const char* pLine, int length);

	double parseDouble(const char* pDouble);
	float parseFloat(const char* pFloat);
	int parseInt(const char* pInt);
	char* parseString(const char* pString);

	// TODO Implement any needed functions below here
};

#endif //_STRING_PARSER_HPP