#pragma once
#ifndef SEARCH_IN_FILE_H
#define SEARCH_IN_FILE_H

#include <string>
#include <iostream>

class SearchInFile
{
private:
	std::string editM_Str;
	std::string m_str;

    std::string reverseStr(std::string str, bool deleteLastSymbol);

	void writeEditM_Str(int numberCoordinate, std::string searchStr);

	std::string deleteStr(std::string str, int indexDelete);

public:
	SearchInFile() {};
	~SearchInFile() {};

	std::string strWrite(char nameCoordinate, std::string searchStr, std::string StFile);

	std::string strWriteTwoCoordinate(char nameFirstCoordinate, std::string searchStrFrCo, char nameSecondCoordinate, std::string searchStrSecCo, std::string StrFile);

	std::string electronDensityStr(std::string strReserve);
	
};

#endif // !SEARCH_IN_FILE_H
