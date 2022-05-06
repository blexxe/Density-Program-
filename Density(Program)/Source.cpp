#include <ctime>
#include "Debug/WhriteFile.h"
#include <chrono>
#include "Debug/ReadFile.h"
#include "Debug/CalculusValueInPoint.h"
#include "Debug/PathLineInMatrix.h"

void printMatrixSchematic()
{
	std::cout << "���������� ������� � ��������� ABCD i ��������� a, b, c, d\n";
	std::cout << "          b\n";
	std::cout << "  B.-------------.C\n";
	std::cout << "   |             |\n";
	std::cout << "a  |             | c\n";
	std::cout << "   |             |\n";
	std::cout << "  A*-------------*D\n";
	std::cout << "          d\n";
	std::cout << "�� ��������i - wingt, �� ����������i - length \n";
}

char setCoordinate()
{
	char axis{ '0' };
	std::cout << "����i�� �����������, ��������������� �� ���, ���� �������������� ���� � ������i.\n";
	std::cout << "���� �������� ���������� '�' �� ���� ���� ������������ � ������i 'OYZ', ���� 'y' �� � ������i 'OXZ', ���� 'z' �� � ������i 'OXY'.\n";
	std::cout << "����i�� �����������: ";

	while (1)
	{
		std::cin >> axis;
		std::cin.ignore(2, '\n');
		if ((axis == 'x') || (axis == 'y') || (axis == 'z'))
			break;
		else
			std::cout << "�� ����� �� ��������� ��������. ����i�� ���� � ��� ������i�: 'x', 'y', 'z': \n";
	}
	return axis;
}

void deleteElementListDegres(PathLineInMatrix& pathInMatrix)
{
	pathInMatrix.printAllValueDegre();

	std::cout << "�� ������ �������� ��i �������� ���i�(1). ������ ������� �������� ��� ���������, �� ������i �������� �����������(2).\n";
	std::cout << "��� � �����i�� ��������, ��i �� ����������, �������� ��i �� ������� ��������(3).\n";

	char choiseDelete{'0'};

	while (1)
	{
		std::cin >> choiseDelete;
		std::cin.ignore(2, '\n');
		if ((choiseDelete == '1') || (choiseDelete == '2') || (choiseDelete == '3'))
			break;
		else
		{
			std::cout << "������ ���i���� ������ ����, ����i��: '1', '2', '3': \n";
		}
	}
	std::list<int> elementMapDegres;
	std::list<int>::const_iterator itElementMapDegres;
	itElementMapDegres = elementMapDegres.cbegin();
	
	int iteratorValueImputElement{ 0 }, iteratorImputElement{ 0 };

	switch (choiseDelete)
	{
	case '1':
		std::cout << "���i ������ ���������i �������� ��� ������� ����.\n";
		break;
	case '2':
		std::cout << "����i�� �i���i��� �������i�, ��i ��������: \n";

		while (true)
		{
			std::cin >> iteratorValueImputElement;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "����i�� �i�� �����: \n";
			}
			else
				break;
		}
		
		std::cout << "����i�� ����� ��������, ���� ������ ��������.\n";
		for (int i{ 0 }; i < iteratorValueImputElement; i++)
		{
			std::cout << "����� ��������: ";
			std::cin >> iteratorImputElement;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "����i�� �i�� �����: \n";
			}
			else
			{
				if ((iteratorImputElement > 0 )&& (iteratorImputElement <= pathInMatrix.getSizeListAllValuesDegre()))
					elementMapDegres.push_back(iteratorImputElement - 1);
				else if (iteratorImputElement <= 0)
				{
					std::cout << " �� ����� ������ ��������. ����i�� �������� �������� ��� ������ �� �i������.\n";
					iteratorValueImputElement--;
				}
				else
				{
					std::cout << " �� ����� �������� ��������. ����i�� �������� �������� ��� ������ �� �i������.\n";
					iteratorValueImputElement--;
				}
			}
		}
		std::cin.ignore(32767, '\n');

		pathInMatrix.deleteElementsListAllValuesDegres(elementMapDegres, '1');

		break;
	case '3':

		while (true)
		{
			std::cin >> iteratorValueImputElement;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "����i�� �i�� �����: \n";
			}
			else
				break;
		}

		for (int i{ 0 }; i < iteratorValueImputElement; i++)
		{
			std::cin >> iteratorImputElement;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			else
				elementMapDegres.push_back(iteratorImputElement);
		}
		std::cin.ignore(32767, '\n');

		pathInMatrix.deleteElementsListAllValuesDegres(elementMapDegres, '2');
		pathInMatrix.deleteElementMap();

		break;
	default:
		break;
	}

	std::cout << "�������� ��i ����������:\n";
	pathInMatrix.printAllValueDegre();
}

void writeFileIncisionMatrixPerpendicularToTheAxis(int maxValueCoordinate, char axis, std::string pathRead, std::string pathWrite)
{
	size_t coordinateStart{ 0 }, numberCreateFile{ 0 };
	WriteInFile writeInFile;

	bool checkForCorrectInput{ false };

	std::cout << "����������� �������� ���������� " << axis << ": " << maxValueCoordinate << '\n';

	std::cout << "����i�� ��������� ������: ";
	
	do 
	{
		std::cin >> coordinateStart;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "�� ����� �� ��������� �����, ����i�� �i�� ������ �����.\n";
			checkForCorrectInput = true;
		}
		else
		{
			if (coordinateStart >= maxValueCoordinate)
			{
				std::cout << "���������� ������ �i���� ������������� �������� (" << maxValueCoordinate << ").\n";
				std::cout << "����i�� ���������� ������: ";
				std::cin >> coordinateStart;
				checkForCorrectInput = true;
			}
			else
				checkForCorrectInput = false;
		}
				
	} while (checkForCorrectInput);
	coordinateStart--;

	std::cout << "I �� ��i���� ����i� ��������� ������ ������: ";

	do
	{
		std::cin >> numberCreateFile;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "�� ����� �� ��������� �����, ����i�� �i�� ������ �����.\n";
			checkForCorrectInput = true;
		}
		else
		{
			if (coordinateStart + numberCreateFile > maxValueCoordinate)
			{
				numberCreateFile -= ((coordinateStart + numberCreateFile) - maxValueCoordinate);
				std::cout << "�i���i��� ����������� ����i� �������� �� �������� (" << maxValueCoordinate << ").";
				std::cout << "���� ��i ��������, ��i �������� �� �i������ �i�������.\n ";
				checkForCorrectInput = false;
			}
			else
				checkForCorrectInput = false;
		}
		
	} while (checkForCorrectInput);

	writeInFile.writeInFilesMultipli(coordinateStart, numberCreateFile, axis, pathWrite, pathRead);

}

void incisionMatrixPerpendicularToTheAxis(std::string pathRead, std::string pathWrite, std::string lastStringFile)
{
	ConvertStringInNumber valueAxis{ lastStringFile };

	std::cout << "����i�� ���, ��������������� �� ��� ������ ����i��: 'x', 'y', 'z'.\n";

	char axis;
	std::cin >> axis;
	std::cin.ignore(2, '\n');

	bool checkForCorrectInput{ false };
	do
	{
		switch (axis)
		{
		case 'x':
			writeFileIncisionMatrixPerpendicularToTheAxis(valueAxis.getSizeX(), axis, pathRead, pathWrite);
			checkForCorrectInput = false;
			break;
		case 'y':
			writeFileIncisionMatrixPerpendicularToTheAxis(valueAxis.getSizeY(), axis, pathRead, pathWrite);
			checkForCorrectInput = false;
			break;
		case 'z':
			writeFileIncisionMatrixPerpendicularToTheAxis(valueAxis.getSizeZ(), axis, pathRead, pathWrite);
			checkForCorrectInput = false;
			break;
		default:
			std::cout << "�� ����� ������������ ������, ����i��: 'x', 'y', 'z'.\n";
			std::cin >> axis;
			std::cin.ignore(2, '\n');
			checkForCorrectInput = true;
			break;
		}
	} while (checkForCorrectInput);
}

void layingPathInMatrix(char axis, std::string pathRead, std::string& pathWrite, double increaseInTheValueOfTheAngle, PathLineInMatrix& pathInMatrix)
{
	char vertex{'A'};

	std::cout << "��� ������� ������ ����� �������� ���������� �� ����� �������, ��� ����������� ��������������� �� ������ ��i.\n";

	printMatrixSchematic();

	std::cout << "����i�� �������, � ��� ������ �������� ������i (A, B, C, D): \n";
	while (1)
	{
		std::cin >> vertex;
		std::cin.ignore(2, '\n');
		if ((vertex == 'A') || (vertex == 'B') || (vertex == 'C') || (vertex == 'D'))
			break;
		else
			std::cout << "�� ����� �� ��������� ��������. ����i�� ���� � ��� ������i�: 'A', 'B', 'C', 'D': \n";
	}

	switch (vertex)
	{
	case 'A':
		pathInMatrix.PathOutVertex('a', increaseInTheValueOfTheAngle);
		pathWrite += " out vertex ==A== ";
		break;
	case 'B':
		pathInMatrix.PathOutVertex('b', increaseInTheValueOfTheAngle);
		pathWrite += " out vertex ==B== ";
		break;
	case 'C':
		pathInMatrix.PathOutVertex('c', increaseInTheValueOfTheAngle);
		pathWrite += " out vertex ==C== ";
		break;
	case 'D':
		pathInMatrix.PathOutVertex('d', increaseInTheValueOfTheAngle);
		pathWrite += " out vertex ==D== ";
		break;
	default:
		break;
	}
}

void lineAtAnAngleToTheAxis(std::string pathRead, std::string& pathWrite, std::string lastStringFile, char axis, PathLineInMatrix& pathInMatrix)
{
	double increaseInTheValueOfTheAngle{ 0 };
	std::cout << "����� ����i�� ����i�� ����. �i� �� ���� ����� 90 ������i� i ������i�: ";

	while (1)
	{
		std::cin >> increaseInTheValueOfTheAngle;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
		{
			if ((increaseInTheValueOfTheAngle < 90) && (increaseInTheValueOfTheAngle > 0))
			{
				break;
			}
			else
				std::cout << " �� ����� ����������� ��������, ������ ����� ����� 90 ������i� i ����� ����: ";
		}
	}

	switch (axis)
	{
	case 'x':
		pathWrite += "�issection surface ==OYZ== ";
		layingPathInMatrix('x', pathRead, pathWrite, increaseInTheValueOfTheAngle, pathInMatrix);
		break;
	case 'y':
		pathWrite += "�issection surface ==OZX== ";
		layingPathInMatrix('y', pathRead, pathWrite, increaseInTheValueOfTheAngle, pathInMatrix);
		break;
	case 'z':
		pathWrite += "�issection surface ==OYX== ";
		layingPathInMatrix('z', pathRead, pathWrite, increaseInTheValueOfTheAngle, pathInMatrix);
		break;
	default:
		break;
	}
}

std::vector<double> calculusValueInPoint(char axis, std::vector<double>* pathOnLengthMatrix, std::vector<double>* pathOnWingtMatrix, std::vector<double>* pathOnHeigtMatrix, ParametersSystem &parametrSystem)
{
	CalculusValueInPoint calculusValue(pathOnHeigtMatrix->size(), pathOnWingtMatrix->size(), pathOnLengthMatrix->size(), parametrSystem);
	calculusValue.fillMatrix(pathOnLengthMatrix, pathOnWingtMatrix, pathOnHeigtMatrix);
	calculusValue.setSizeVectorPathLineInMatrix((pathOnWingtMatrix->size()) * (pathOnHeigtMatrix->size()));
	calculusValue.completeCalculatedValue(axis);
	return calculusValue.getPointerCalculatedValue();
}

void writeFileLineAtAnAngleToTheAxis(std::string pathRead, std::string pathWrite, std::string lastStringFile, ParametersSystem& parametrSystem)
{
	WriteInFile writeInFile;
	std::string nameFileWrite;
	char axis{ '0' };
	axis = setCoordinate();

	PathLineInMatrix pathInMatrix(lastStringFile, axis);
	lineAtAnAngleToTheAxis(pathRead, pathWrite, lastStringFile, axis, pathInMatrix);
	deleteElementListDegres(pathInMatrix);

	std::vector<double> pathOnLengthMatrix;
	std::vector<double> pathOnWingtMatrix;
	std::vector<double> pathOnHeigtMatrix;

	pathOnLengthMatrix.resize(pathInMatrix.getValueLengthMatrix() + 1);
	pathOnWingtMatrix.resize(pathInMatrix.getValueWigthMatrix() + 1);
	pathOnHeigtMatrix.resize(pathInMatrix.getValueHeigtMatrix() + 1);

	std::string wrintDegreInNameFile;

	for (size_t j{ 0 }; j < pathInMatrix.getSizeListAllValuesDegre(); j++)
	{
		for (size_t i{ 0 }; i < pathOnLengthMatrix.size(); i++)
			pathOnLengthMatrix[i] = pathInMatrix.getValueCoordinatLineOnLengt(pathInMatrix.getElementListAllValuesDegre(j), i);
		for (size_t i{ 0 }; i < pathOnWingtMatrix.size(); i++)
			pathOnWingtMatrix[i] = pathInMatrix.getValueCoordinatLineOnWingt(pathInMatrix.getElementListAllValuesDegre(j), i);
		for (size_t i{ 0 }; i < pathOnHeigtMatrix.size(); i++)
			pathOnHeigtMatrix[i] = pathInMatrix.getValueCoordinatLineOnHeigth(pathInMatrix.getElementListAllValuesDegre(j), i);
		wrintDegreInNameFile = std::to_string(pathInMatrix.getElementListAllValuesDegre(j));
		nameFileWrite += "at an angle ==";
		nameFileWrite += wrintDegreInNameFile;
		nameFileWrite += "==.txt";
		nameFileWrite = pathWrite + nameFileWrite;

		writeInFile.writeArrayInFile(nameFileWrite, calculusValueInPoint(axis, &pathOnLengthMatrix, &pathOnWingtMatrix, &pathOnHeigtMatrix, parametrSystem),
			(pathInMatrix.getValueHeigtMatrix() + 1), (pathInMatrix.getValueLengthMatrix() + 1));
		nameFileWrite.clear();
		std::cout << j + 1 << " � " << pathInMatrix.getSizeListAllValuesDegre() << " ����i� ��������.\n";
		wrintDegreInNameFile.clear();

	}

}

void setSidePath(PathLineInMatrix& pathInMatrix, int maxValueCoordinateLengt, int maxValueCoordinateWingt, std::string &nameFileWrite)
{
	//std::cout << "\n";
	std::cout << "��� ������� ������ ����� �������� ���������� �� ����� �������, ��� ����������� ��������������� �� ������ ��i.\n";

	printMatrixSchematic();

	std::cout << "�������� ����i�� ������� �� ��i� ���� ��������� �����: 'a', 'b', 'c', 'd',\n� ���i� ������� �� ��i� ���� ���i��������� �����: 'a', 'b', 'c', 'd'.\n";
	std::cout << "����� �� ����� ���� ��i �i��i �������.\n";
	char sideIn, sideOut;
	std::cout << "����� �������: ";
	while (1)
	{
		std::cin >> sideOut;
		std::cin.ignore(2, '\n');
		if ((sideOut == 'a') || (sideOut == 'b') || (sideOut == 'c') || (sideOut == 'd'))
			break;
		else
			std::cout << "�� ����� �� ��������� ��������. ����i�� ���� � ��� ������i�: 'a', 'b', 'c', 'd': \n";
	}
	std::cout << "����� �������: ";
	while (1)
	{
		std::cin >> sideIn;
		std::cin.ignore(2, '\n');
		if ((sideIn == 'a') || (sideIn == 'b') || (sideIn == 'c') || (sideIn == 'd'))
			break;
		else if (sideIn == sideOut)
			std::cout << "�� ����� ��������� ������� � ���� ���i�����, ����i�� i��� ������.\n";
		else
			std::cout << "�� ����� �� ��������� ��������. ����i�� ���� � ��� ������i�: 'a', 'b', 'c', 'd': \n";
	}

	size_t coordinateStart, coordinateEnd, maxValueSideStart, maxValueSideEnd;
	switch (sideOut)
	{
	case 'a':
		maxValueSideStart = maxValueCoordinateLengt;
		std::cout << "����� ����i�� ��������� ���������� �i� 1 �� " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "side start ==a== ";
		break;
	case 'b':
		maxValueSideStart = maxValueCoordinateWingt;
		std::cout << "����� ����i�� ��������� ���������� �i� 1 �� " << maxValueCoordinateWingt;
		std::cout << ":\n";
		nameFileWrite += "side start ==b== ";
		break;
	case 'c':
		maxValueSideStart = maxValueCoordinateLengt;
		std::cout << "����� ����i�� ��������� ���������� �i� 1 �� " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "side start ==c== ";
		break;
	case 'd':
		maxValueSideStart = maxValueCoordinateWingt;
		std::cout << "����� ����i�� ��������� ���������� �i� 1 �� " << maxValueCoordinateWingt;
		std::cout << ":\n";
		nameFileWrite += "side start ==d== ";
		break;
	default:
		break;
	}

	while (1)
	{
		std::cin >> coordinateStart;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "����i�� �������� �i�� ����� ����� " << maxValueSideStart + 1 <<" i �i���� 0.\n";
		}
		else
		{
			if (coordinateStart > maxValueSideStart+1)
				std::cout << "����i�� �������� ����� " << maxValueSideStart + 1 <<"\n";
			else
				break;
		}
	}

	nameFileWrite += "coordinate start ==";
	nameFileWrite += std::to_string(coordinateStart);

	switch (sideIn)
	{
	case 'a':
		maxValueSideEnd = maxValueCoordinateLengt;
		std::cout << "����� ����i�� �i����� ���������� �i� 1 �� " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==a== ";
		break;
	case 'b':
		maxValueSideEnd = maxValueCoordinateWingt;
		std::cout << "����� ����i�� �i����� ���������� �i� 1 �� " << maxValueCoordinateWingt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==b== ";
		break;
	case 'c':
		maxValueSideEnd = maxValueCoordinateLengt;
		std::cout << "����� ����i�� �i����� ���������� �i� 1 �� " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==c== ";
		break;
	case 'd':
		maxValueSideEnd = maxValueCoordinateWingt;
		std::cout << "����� ����i�� �i����� ���������� �i� 1 �� " << maxValueCoordinateWingt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==d== ";
		break;
	default:
		break;
	}

	while (1)
	{
		std::cin >> coordinateEnd;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "����i�� �������� �i�� ����� ����� " << maxValueSideEnd << " i �i���� 0.\n";
		}
		else
		{
			if (coordinateEnd > maxValueSideEnd)
				std::cout << "����i�� �������� ����� " << maxValueSideEnd << "\n";
			else
				break;
		}
	}

	nameFileWrite += "coordinate end ==";
	nameFileWrite += std::to_string(coordinateEnd);
	nameFileWrite += "==.txt";

	pathInMatrix.pathOutFirstSideInSecondSide(coordinateStart, coordinateEnd, sideOut, sideIn);
}

void writeFileInFirstSideOutSecondSide(std::string pathRead, std::string pathWrite, std::string lastStringFile, ParametersSystem& parametrSystem)
{
	WriteInFile writeInFile;

	char axis{ '0' };
	axis = setCoordinate();

	PathLineInMatrix pathInMatrix(lastStringFile, axis);

	int stop�ycle{ 0 };

	std::vector<double> pathOnLengthMatrix;
	std::vector<double> pathOnWingtMatrix;
	std::vector<double> pathOnHeigtMatrix;

	std::string nameFileWrite;

	while (true)
	{
		nameFileWrite = pathWrite;

		switch (axis)
		{
		case 'x':
			nameFileWrite += "�issection surface ==OYZ== ";
			break;
		case 'y':
			nameFileWrite += "�issection surface ==OZX== ";
			break;
		case 'z':
			nameFileWrite += "�issection surface ==OYX== ";
			break;
		default:
			break;
		}

		setSidePath(pathInMatrix, parametrSystem.getLegth(), parametrSystem.getWingt(), nameFileWrite);

		pathOnLengthMatrix.resize(pathInMatrix.getValueLengthMatrix() + 1);
		pathOnWingtMatrix.resize(pathInMatrix.getValueWigthMatrix() + 1);
		pathOnHeigtMatrix.resize(pathInMatrix.getValueHeigtMatrix() + 1);

		std::string wrintDegreInNameFile;

		for (size_t i{ 0 }; i < pathOnLengthMatrix.size(); i++)
			pathOnLengthMatrix[i] = pathInMatrix.getValueCoordinatLineOnLengt(pathInMatrix.getElementListAllValuesDegre(1), i);
		for (size_t i{ 0 }; i < pathOnWingtMatrix.size(); i++)
			pathOnWingtMatrix[i] = pathInMatrix.getValueCoordinatLineOnWingt(pathInMatrix.getElementListAllValuesDegre(1), i);
		for (size_t i{ 0 }; i < pathOnHeigtMatrix.size(); i++)
			pathOnHeigtMatrix[i] = pathInMatrix.getValueCoordinatLineOnHeigth(pathInMatrix.getElementListAllValuesDegre(1), i);

		writeInFile.writeArrayInFile(nameFileWrite, calculusValueInPoint(axis, &pathOnLengthMatrix, &pathOnWingtMatrix, &pathOnHeigtMatrix, parametrSystem),
			(pathInMatrix.getValueHeigtMatrix() + 1), (pathInMatrix.getValueLengthMatrix() + 1));
		nameFileWrite.clear();

		std::cout << "���� ������ ������� �� ���� ����i� ����i�� '1', ���� �i �� '2'.\n";
		std::cout << "����� ������ '1' ������ ��������� �� '1', � ����� �i���� '2', �� '2': \n";
		while (1)
		{
			std::cin >> stop�ycle;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "����i�� �i�� �����.\n";
			}
			else
				break;
		}
		if (stop�ycle <= 1)
			continue;
		else
			break;

		pathInMatrix.clearArray();
	}
}

bool checkOpenPathWriteFile(std::string pathWrite)
{
	WriteInFile w;
	return w.checkOpen(pathWrite);
}

int main()
{
	setlocale(LC_CTYPE, "ukr");
	//C:\Users\User\Documents\Kursova\Density(Program)\ZnO.charg_frm
	//E:\New_FIle\

	std::string pathRead{"C:\\Users\\User\\Documents\\Kursova\\Density(Program)\\ZnO.charg_frm"}, pathWrite{ "E:\\New_FIle\\" };

	std::cout << "����i�� ����-���� ������ ��� ������� ������ ��������.\n";
	std::cin >> pathRead;

	std::cout << "����i�� ���� �� ����� � ����� ������ ��������� ���i.\n";
	std::cin >> pathRead;
	
	char checkStopProgram, checkChangePathRead, checkChangePathWrite;
	ReadFile readFile;
	readFile.openNewFile(pathRead);
	do
	{
		if (!readFile.is_open())
		{
			std::cout << "����i�� ���� �� ����� ������, ���� �� �� ���� ����� �� �� �����, ���� �� �i����������.\n";
			std::cin >> pathRead;
			readFile.openNewFile(pathRead);
			readFile.clear();
		}
		else
			continue;
	} while (!readFile.is_open());

	ParametersSystem parametrSystem;

	std::cout << "����i�� ���� �� ����� � ��� ������ ���������� ���i. ���� �� �i�� ����� �� ������� ���� ��������i �������:\n";
	std::cin >> pathWrite;

	while (true)
	{
		if (checkOpenPathWriteFile(pathWrite))
			break;
		else
		{
			std::cout << "�� ����� �� ���������� ����, ����i�� ���� ������:\n";
			pathWrite.clear();
			std::cin >> pathWrite;
		}
	}

	bool checkVectorAllElecDen{ false };
	std::string lastStringFile{ readFile.lastStringFile() };
	while (true)
	{
		std::cout << "�����i�� �� ������ ���i���� ������� ����������������� �� ����� ��i ����i����(1),";
		std::cout << " �� �i� ����� �� �i�� ��i(2), �� ��������� ���� �i� ������� �������(3):\n";

		size_t choiceImput{ 3 };
		std::cin >> choiceImput;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
		{
			switch (choiceImput)
			{
			case 1:
				incisionMatrixPerpendicularToTheAxis(pathRead, pathWrite, lastStringFile);
				break;
			case 2:
				if (!checkVectorAllElecDen)
				{
					parametrSystem.newParameter(readFile.lastStringFile(), '0');
					parametrSystem = readFile.allValueEleDen();
					checkVectorAllElecDen = true;
				}
				else
				{ }
				writeFileLineAtAnAngleToTheAxis(pathRead, pathWrite, lastStringFile, parametrSystem);
				break;
			case 3:
				if (!checkVectorAllElecDen)
				{
					parametrSystem.newParameter(readFile.lastStringFile(), '0');
					parametrSystem = readFile.allValueEleDen();
					checkVectorAllElecDen = true;
					writeFileInFirstSideOutSecondSide(pathRead, pathWrite, lastStringFile, parametrSystem);
				}
				else
				{
					writeFileInFirstSideOutSecondSide(pathRead, pathWrite, lastStringFile, parametrSystem);
				}
				break;
			default:
				break;
			}
		}

		std::cout << "������ ���������� ��������� ��������? ���� ��� �� ����i�� 'y'(���������� �i� Yes), ���� ������ ���i����� �� ������ �� ����i�� 'n' (���������� �i� No)\n";

		while (true)
		{
			std::cin >> checkStopProgram;
			std::cin.ignore(2, '\n');
			if((checkStopProgram != 'y') && (checkStopProgram != 'n'))
			{
				std::cout << "����i�� 'y' ��� 'n'.\n";
			}
			else
				break;
		}

		if (checkStopProgram == 'n')
			break;
		else
		{
			std::cout << "������ ���i���� ���� � ����� ���������� ���i? ���� ��� �� ����i�� 'y'(���������� �i� Yes), ���� ������ ���i����� �� ������ �� ����i�� 'n' (���������� �i� No)\n";

			while (true)
			{
				std::cin >> checkChangePathRead;
				std::cin.ignore(2, '\n');
				if ((checkChangePathRead != 'y') && (checkChangePathRead != 'n'))
				{
					std::cout << "����i�� 'y' ��� 'n'.\n";
				}
				else
					break;
			}
			
			if(checkChangePathRead == 'y')
			{ 
				std::cout << "����i�� ���� �� ����� � ����� ������ ��������� ���i.\n";
				std::cin >> pathRead;

				readFile.openNewFile(pathRead);
				lastStringFile = readFile.lastStringFile();
				while(true)
				{
					if (!readFile.is_open())
					{
						std::cout << "����i�� ���� �� ����� ������, ���� �� �� ���� ����� �� �� �����, ���� �� �i����������.\n";
						std::cin >> pathRead;
						readFile.openNewFile(pathRead);
						readFile.clear();
						checkVectorAllElecDen = false;
					}
					else
						break;
				}
			}
			else
				std::cout << "���i ����i ������ ���i ����������� � ���� ������ �����.\n";

			std::cout << "���� ������ ������� i��� i������ ����� ��� ������ �� ����i�� 'y', ���� ������ ��� ���������� � �� ���� �� 'n'.\n";

			while (true)
			{
				std::cin >> checkChangePathWrite;
				std::cin.ignore(2, '\n');
				if ((checkChangePathWrite != 'y') && (checkChangePathWrite != 'n'))
				{
					std::cout << "����i�� 'y' ��� 'n'.\n";
				}
				else
					break;
			}

			if (checkChangePathWrite == 'y')
			{
				std::cout << "���i ����i�� ����� ���� �� ����� � ��� ������ ���������� ���i. ���� �� �i�� ����� �� ������� ���� ��������i �������:\n";
				std::cin >> pathWrite;

				while (true)
				{
					if (checkOpenPathWriteFile(pathWrite))
						break;
					else
					{
						std::cout << "�� ����� �� ���������� ����, ����i�� ���� ������:\n";
						pathWrite.clear();
						std::cin >> pathWrite;
					}
				}
			}
			else
				std::cout << "���i ����i ������ ���i ������������ � �� ���� �����.\n";
		}
	}

	return 0;
}