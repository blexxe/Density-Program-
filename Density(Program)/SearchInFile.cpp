#include "SearchInFile.h"

//Розворот певного рядка
std::string SearchInFile::reverseStr(std::string str, bool deleteLastSymbol = false)
{
	std::string reverseStr;
	int checkCoord{ 0 };
	//std::cout << " 1str: {" << str << "}\n";
	for (size_t j{ str.size() }; j > 0; j--)
	{
		if (str[j] == '\t' || str[j] == '\n' || str[j] == ' ')
			break;
		else
			reverseStr += str[j];
	}
	//std::cout << "reverse: {" << reverseStr << "}\n";
	for (int j{ static_cast<int>(reverseStr.size()) }, i{ 0 }; j >0 ; j--, i++)
	{
		std::swap(reverseStr[j], reverseStr[i]);
	}
	str = reverseStr;
	if (deleteLastSymbol)
	{
		if (str.size() != 0)
		{
			std::swap(str[0], str[str.size() - 1]);
			str.pop_back();
		}
	}
	return str;
}

//Пошук потрібного рядка в файлі по конкретному значенні певного стовбця
void SearchInFile::writeEditM_Str(int numberCoordinate, std::string searchingStr)
{
	std::string interimStr, numberColomn{ "" }, space{ " " };
	int checkCoordinat{ 0 }, numberNotSpace{ 0 };
	for (size_t i{ 0 }; i < m_str.size(); i++)
	{
		numberColomn += m_str.at(i);
		if (m_str[i] == '\t' && checkCoordinat < numberCoordinate)
		{
			checkCoordinat++;
		}
		else if (m_str[i] == ' ' && checkCoordinat < numberCoordinate)
		{
			if (space.size() == 0)
			{
				checkCoordinat++;
				space = " ";
			}
			space += m_str[i];
		}
		else
			space = "";

		if (checkCoordinat == numberCoordinate)
		{
			numberColomn.pop_back();
			break;
		}
	}

	//std::cout << "numberColomn: {" << numberColomn << "}\n";
	
	numberColomn = reverseStr(numberColomn, true);

	//std::cout << "numberColomn: {" << numberColomn << "}\n";
	editM_Str.clear();
	checkCoordinat = 0;
	if (searchingStr == numberColomn)
	{
		
		editM_Str = m_str;
	}
}

//Вибір координати по якій буде здійснюватися пошук(по одній координаті)
std::string SearchInFile::strWrite(char nameCoordinate, std::string searchStr, std::string StrFile)
{ 
	m_str = StrFile;
	switch (nameCoordinate)
	{
	case 'x':
		writeEditM_Str(1, searchStr);
		break;
	case  'y':
		writeEditM_Str(2, searchStr);
		break;
	case 'z':
		writeEditM_Str(3, searchStr);
		break;
	default:
		break;
	}
	return editM_Str;
}

//Вибір координати по якій буде здійснюватися пошук(по двом координатам координаті)
std::string SearchInFile::strWriteTwoCoordinate(char nameFirstCoordinate, std::string searchStrFrCo, char nameSecondCoordinate, std::string searchStrSecCo, std::string StrFile)
{
	m_str = StrFile;
	switch (nameFirstCoordinate | nameSecondCoordinate)
	{
	case 'x' | 'z':
		writeEditM_Str(3, searchStrFrCo);
		if (editM_Str == m_str)
			writeEditM_Str(1, searchStrSecCo);
		else
			editM_Str = "";
		break;
	case  'y' | 'z':
		writeEditM_Str(3, searchStrFrCo);
		if (editM_Str == m_str)
			writeEditM_Str(2, searchStrSecCo);
		else
			editM_Str = "";
		break;
	default:
		break;
	}
	return editM_Str;
}

//Витяг з рядка значення електроної густини в певній тоці
std::string SearchInFile::electronDensityStr(std::string strReserve)
{
	std::string elecDenStr;
	elecDenStr = reverseStr(strReserve);
	//std::cout << "elecDenStr: " << elecDenStr << '\n';
	return elecDenStr;
}

// ця функція видаляє всі символи після певного індекса, а всі символи до нього зберігає
std::string SearchInFile::deleteStr(std::string str, int indexDelete) 
{
	std::string newStr{ "f" };
	for (int i{ 0 }; i < indexDelete; i++)
	{
		newStr += str[i];
	}
	return newStr;
}
