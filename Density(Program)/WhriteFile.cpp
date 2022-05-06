#include "Debug/WhriteFile.h"

//Запис в кілька файлів
void WriteInFile::writeInFilesMultipli(int coordinateStart, int numberCreateFile, char symbolColumn, std::string pathInPapkcWrite, std::string pathInPapkcRead)
{
	std::string pathInFile;
	ReadFile read(pathInPapkcRead);
	read.chekOpenFile('r');
	ParametersSystem parametr(read.lastStringFile(), symbolColumn);
	ConvertStringInNumber convertNumInStr;
	RandomName randName;
	std::list<std::string> arrRandName;

	for (int i{ coordinateStart }; i < numberCreateFile; i++)
	{
		switch (symbolColumn)
		{
		case 'x':
			parametr = read.searchingInFile('x', convertNumInStr.convertNubmerInString(i + 1));
			randName.generationName('x', convertNumInStr.convertNubmerInString(i + 1));
			break;
		case 'y':
			parametr = read.searchingInFile('y', convertNumInStr.convertNubmerInString(i + 1));
			randName.generationName('y', convertNumInStr.convertNubmerInString(i + 1));
			break;
		case 'z':
			parametr = read.searchingInFile('z', convertNumInStr.convertNubmerInString(i + 1));
			randName.generationName('z', convertNumInStr.convertNubmerInString(i + 1));
			break;
		default:
			try
			{
				throw "======>WRONG_SYMBOL<======";
			}
			catch (const char* strE)
			{
				int i{ 0 };
				while (i!= 10)
				{
					std::cout << strE[i];
					i++;
				}

				std::cout << "\nВи ввели не правильний символ стовпчика.\nДопустимi тiльки символи : 'x', 'y', 'z'.\a\n";
				std::cout << "Введiть один з допустимих символiв: ";
				std::cin >> symbolColumn;
				i--;
			}
			break;
		}
		pathInFile = pathInPapkcWrite;
		pathInFile += randName.getName() += ".txt";
		WriteInOneFile(pathInFile, symbolColumn, parametr);
		arrRandName.push_back(randName.getRadomName());
		randName.destrucRandomName();
	}
	std::cout << "Успiшно створено " << numberCreateFile << " файлiв, по осi " << symbolColumn <<  '\n';
}

//Запис в конкретний файл
void WriteInFile::WriteInOneFile(std::string pathInFile, char symbolColumn, ParametersSystem& parametr)
{
	m_file.open(pathInFile, std::ios_base::out | std::ios_base::app);
	chekOpenFile('w');
	int parametrElDen{ 0 }, firCoor{ 0 }, secCoor{ 0 };
	std::string str;

	switch (symbolColumn)
	{
	case 'x':
		firCoor = parametr.getNumberCoordinate('x', 'z');
		secCoor = parametr.getNumberCoordinate('x', 'y');
		break;
	case 'y':
		firCoor = parametr.getNumberCoordinate('y', 'z');
		secCoor = parametr.getNumberCoordinate('y', 'x');
		break;
	case 'z':
		firCoor = parametr.getNumberCoordinate('z', 'y');
		secCoor = parametr.getNumberCoordinate('z', 'x');
		break;
	default:
		break;
	}

	for (int j{ 0 }; j < firCoor; j++)
	{
		for (int i{ 0 }; i < secCoor; i++)
		{
			str = parametr.getElecDens(parametrElDen);
			m_file << i + 1 << "\t" << j + 1 << '\t';
			writeStr(str);

			str.clear();
			++parametrElDen;
		}
	}
	m_file.close();
	m_file.clear();
}

void WriteInFile::writeArrayInFile(std::string pathInFile, std::vector<double> vectorValues, int valueOutsideIterator, int valueInsideIterator)
{
	m_file.open(pathInFile, std::ios_base::out | std::ios_base::app);
	if (m_file.is_open())
	{
		for (int j{ 0 }, iterator{ 0 }; j < valueOutsideIterator; j++)
		{
			for (int i{ 0 }; i < valueInsideIterator; i++, iterator++)
			{
				m_file << i + 1 << "\t" << j + 1 << '\t';
				m_file << vectorValues[iterator];
				m_file << '\n';
			}
		}
		m_file.close();
	}
	else
		throw "EROR_OPEN_FILE";
}

//Запис рядка
void WriteInFile::writeStr(std::string str)
{
	for (size_t k{ 1 }; k < str.size(); k++)
	{
		m_file << str[k];
	}
	m_file << '\n';
}

//Запис списку створених файлів
void WriteInFile::listFiles(std::list<std::string> &arrNameFile, char coordinatWrite)
{
	m_file.open("E:\\New_FIle\\List file.txt", std::ios_base::out | std::ios_base::app);
	m_file << '\n' << "\t\t======COORDINATE [" << coordinatWrite << "]======\n";
	int i{ 0 };
	for (auto itr{ arrNameFile.begin() }; itr != arrNameFile.end(); ++itr, i++)
	{
		m_file << "File: " << *itr << " create. Coordinate write: '" << coordinatWrite << "'. Number coordinate: ";
		m_file << i +1 << std::endl;
	}
	m_file << '\n' << '\n';
	m_file.clear();
	m_file.close();
}
