#include <ctime>
#include "Debug/WhriteFile.h"
#include <chrono>
#include "Debug/ReadFile.h"
#include "Debug/CalculusValueInPoint.h"
#include "Debug/PathLineInMatrix.h"

void printMatrixSchematic()
{
	std::cout << "Прямокутна матриця з вершинами ABCD i сторонами a, b, c, d\n";
	std::cout << "          b\n";
	std::cout << "  B.-------------.C\n";
	std::cout << "   |             |\n";
	std::cout << "a  |             | c\n";
	std::cout << "   |             |\n";
	std::cout << "  A*-------------*D\n";
	std::cout << "          d\n";
	std::cout << "По вертикалi - wingt, по горизонталi - length \n";
}

char setCoordinate()
{
	char axis{ '0' };
	std::cout << "Введiть коордтинату, перпендекулярно до якої, буде прокладоватися шлях в площинi.\n";
	std::cout << "Якщо виберете координату 'х' то шлях буде прокладатися в площинi 'OYZ', якщо 'y' то в площинi 'OXZ', якщо 'z' то в площинi 'OXY'.\n";
	std::cout << "Введiть коордтинату: ";

	while (1)
	{
		std::cin >> axis;
		std::cin.ignore(2, '\n');
		if ((axis == 'x') || (axis == 'y') || (axis == 'z'))
			break;
		else
			std::cout << "Ви ввели не правильне значення. Введiть один з цих варіантiв: 'x', 'y', 'z': \n";
	}
	return axis;
}

void deleteElementListDegres(PathLineInMatrix& pathInMatrix)
{
	pathInMatrix.printAllValueDegre();

	std::cout << "Ви хочете зберегти всi значення кутiв(1). Хочете вибрати елементи для видалення, не вибранi елементи збережуться(2).\n";
	std::cout << "Або ж виберiть елементи, якi не видаляться, елементи якi не вибрали видалять(3).\n";

	char choiseDelete{'0'};

	while (1)
	{
		std::cin >> choiseDelete;
		std::cin.ignore(2, '\n');
		if ((choiseDelete == '1') || (choiseDelete == '2') || (choiseDelete == '3'))
			break;
		else
		{
			std::cout << "Такого варiанта вибору немає, введiть: '1', '2', '3': \n";
		}
	}
	std::list<int> elementMapDegres;
	std::list<int>::const_iterator itElementMapDegres;
	itElementMapDegres = elementMapDegres.cbegin();
	
	int iteratorValueImputElement{ 0 }, iteratorImputElement{ 0 };

	switch (choiseDelete)
	{
	case '1':
		std::cout << "Тодi будуть похарованi значення для кожного кута.\n";
		break;
	case '2':
		std::cout << "Введiть кiлькiсть елементiв, якi видалете: \n";

		while (true)
		{
			std::cin >> iteratorValueImputElement;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "Введiть цiле число: \n";
			}
			else
				break;
		}
		
		std::cout << "Введiть номер елемента, який будете видаляти.\n";
		for (int i{ 0 }; i < iteratorValueImputElement; i++)
		{
			std::cout << "Номер елемента: ";
			std::cin >> iteratorImputElement;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "Введiть цiле число: \n";
			}
			else
			{
				if ((iteratorImputElement > 0 )&& (iteratorImputElement <= pathInMatrix.getSizeListAllValuesDegre()))
					elementMapDegres.push_back(iteratorImputElement - 1);
				else if (iteratorImputElement <= 0)
				{
					std::cout << " Ви ввели замале значення. Введiть значення елемента без виходу за дiапазон.\n";
					iteratorValueImputElement--;
				}
				else
				{
					std::cout << " Ви ввели завелике значення. Введiть значення елемента без виходу за дiапазон.\n";
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
				std::cout << "Введiть цiле число: \n";
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

	std::cout << "Значення якi залишилися:\n";
	pathInMatrix.printAllValueDegre();
}

void writeFileIncisionMatrixPerpendicularToTheAxis(int maxValueCoordinate, char axis, std::string pathRead, std::string pathWrite)
{
	size_t coordinateStart{ 0 }, numberCreateFile{ 0 };
	WriteInFile writeInFile;

	bool checkForCorrectInput{ false };

	std::cout << "Максимальне значення координати " << axis << ": " << maxValueCoordinate << '\n';

	std::cout << "Введiть кординату старту: ";
	
	do 
	{
		std::cin >> coordinateStart;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "Ви ввели не правильне число, введiть цiле додатнє число.\n";
			checkForCorrectInput = true;
		}
		else
		{
			if (coordinateStart >= maxValueCoordinate)
			{
				std::cout << "Координата старту бiльша максимального значення (" << maxValueCoordinate << ").\n";
				std::cout << "Введiть координату старту: ";
				std::cin >> coordinateStart;
				checkForCorrectInput = true;
			}
			else
				checkForCorrectInput = false;
		}
				
	} while (checkForCorrectInput);
	coordinateStart--;

	std::cout << "I те скiльки файлiв координат вперед пройти: ";

	do
	{
		std::cin >> numberCreateFile;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Ви ввели не правильне число, введiть цiле додатнє число.\n";
			checkForCorrectInput = true;
		}
		else
		{
			if (coordinateStart + numberCreateFile > maxValueCoordinate)
			{
				numberCreateFile -= ((coordinateStart + numberCreateFile) - maxValueCoordinate);
				std::cout << "Кiлькiсть створюваних файлiв виходить за максимум (" << maxValueCoordinate << ").";
				std::cout << "Тому всi значення, якi виходять за дiапазон вiдкинуто.\n ";
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

	std::cout << "Введiть ось, перпендикулярно до якої будуть розрiзи: 'x', 'y', 'z'.\n";

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
			std::cout << "Ви ввели неправильний символ, введiть: 'x', 'y', 'z'.\n";
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

	std::cout << "Для початку роботи краще спочатку подивитися на схему плошини, яка знаходиться перпенлекулярно до обраної осi.\n";

	printMatrixSchematic();

	std::cout << "Введiть вершину, з якої будете будувати променi (A, B, C, D): \n";
	while (1)
	{
		std::cin >> vertex;
		std::cin.ignore(2, '\n');
		if ((vertex == 'A') || (vertex == 'B') || (vertex == 'C') || (vertex == 'D'))
			break;
		else
			std::cout << "Ви ввели не правильне значення. Введiть один з цих варіантiв: 'A', 'B', 'C', 'D': \n";
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
	std::cout << "Також введiть прирiст кута. Вiн має бути менше 90 градусiв i додатнiм: ";

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
				std::cout << " Ви ввели неправильне значення, введіть число менше 90 градусiв i більше нуля: ";
		}
	}

	switch (axis)
	{
	case 'x':
		pathWrite += "Вissection surface ==OYZ== ";
		layingPathInMatrix('x', pathRead, pathWrite, increaseInTheValueOfTheAngle, pathInMatrix);
		break;
	case 'y':
		pathWrite += "Вissection surface ==OZX== ";
		layingPathInMatrix('y', pathRead, pathWrite, increaseInTheValueOfTheAngle, pathInMatrix);
		break;
	case 'z':
		pathWrite += "Вissection surface ==OYX== ";
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
		std::cout << j + 1 << " з " << pathInMatrix.getSizeListAllValuesDegre() << " файлiв створено.\n";
		wrintDegreInNameFile.clear();

	}

}

void setSidePath(PathLineInMatrix& pathInMatrix, int maxValueCoordinateLengt, int maxValueCoordinateWingt, std::string &nameFileWrite)
{
	//std::cout << "\n";
	std::cout << "Для початку роботи краще спочатку подивитися на схему плошини, яка знаходиться перпенлекулярно до обраної осi.\n";

	printMatrixSchematic();

	std::cout << "Спочатку введiть сторону на якiй буде почнатися пряма: 'a', 'b', 'c', 'd',\nа потiм сторону на якiй буде закiнчуватися пряма: 'a', 'b', 'c', 'd'.\n";
	std::cout << "Також це мають бути двi рiзнi сторони.\n";
	char sideIn, sideOut;
	std::cout << "Перша сторона: ";
	while (1)
	{
		std::cin >> sideOut;
		std::cin.ignore(2, '\n');
		if ((sideOut == 'a') || (sideOut == 'b') || (sideOut == 'c') || (sideOut == 'd'))
			break;
		else
			std::cout << "Ви ввели не правильне значення. Введiть один з цих варіантiв: 'a', 'b', 'c', 'd': \n";
	}
	std::cout << "Друга сторона: ";
	while (1)
	{
		std::cin >> sideIn;
		std::cin.ignore(2, '\n');
		if ((sideIn == 'a') || (sideIn == 'b') || (sideIn == 'c') || (sideIn == 'd'))
			break;
		else if (sideIn == sideOut)
			std::cout << "Ви ввели одинакову сторону в обох варiантах, введiть iншу сторну.\n";
		else
			std::cout << "Ви ввели не правильне значення. Введiть один з цих варіантiв: 'a', 'b', 'c', 'd': \n";
	}

	size_t coordinateStart, coordinateEnd, maxValueSideStart, maxValueSideEnd;
	switch (sideOut)
	{
	case 'a':
		maxValueSideStart = maxValueCoordinateLengt;
		std::cout << "Тепер введiть початкову координату вiд 1 до " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "side start ==a== ";
		break;
	case 'b':
		maxValueSideStart = maxValueCoordinateWingt;
		std::cout << "Тепер введiть початкову координату вiд 1 до " << maxValueCoordinateWingt;
		std::cout << ":\n";
		nameFileWrite += "side start ==b== ";
		break;
	case 'c':
		maxValueSideStart = maxValueCoordinateLengt;
		std::cout << "Тепер введiть початкову координату вiд 1 до " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "side start ==c== ";
		break;
	case 'd':
		maxValueSideStart = maxValueCoordinateWingt;
		std::cout << "Тепер введiть початкову координату вiд 1 до " << maxValueCoordinateWingt;
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
			std::cout << "Введiть значення цiле число менше " << maxValueSideStart + 1 <<" i бiльше 0.\n";
		}
		else
		{
			if (coordinateStart > maxValueSideStart+1)
				std::cout << "Введiть значення менше " << maxValueSideStart + 1 <<"\n";
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
		std::cout << "Тепер введiть кiнцеву координату вiд 1 до " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==a== ";
		break;
	case 'b':
		maxValueSideEnd = maxValueCoordinateWingt;
		std::cout << "Тепер введiть кiнцеву координату вiд 1 до " << maxValueCoordinateWingt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==b== ";
		break;
	case 'c':
		maxValueSideEnd = maxValueCoordinateLengt;
		std::cout << "Тепер введiть кiнцеву координату вiд 1 до " << maxValueCoordinateLengt;
		std::cout << ":\n";
		nameFileWrite += "== side end ==c== ";
		break;
	case 'd':
		maxValueSideEnd = maxValueCoordinateWingt;
		std::cout << "Тепер введiть кiнцеву координату вiд 1 до " << maxValueCoordinateWingt;
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
			std::cout << "Введiть значення цiле число менше " << maxValueSideEnd << " i бiльше 0.\n";
		}
		else
		{
			if (coordinateEnd > maxValueSideEnd)
				std::cout << "Введiть значення менше " << maxValueSideEnd << "\n";
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

	int stopСycle{ 0 };

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
			nameFileWrite += "Вissection surface ==OYZ== ";
			break;
		case 'y':
			nameFileWrite += "Вissection surface ==OZX== ";
			break;
		case 'z':
			nameFileWrite += "Вissection surface ==OYX== ";
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

		std::cout << "Якщо бажаєте зробити ще один розрiз введiть '1', якщо нi то '2'.\n";
		std::cout << "Числа меньше '1' будуть вважатися як '1', а числа бiльше '2', як '2': \n";
		while (1)
		{
			std::cin >> stopСycle;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "Введiть цiле число.\n";
			}
			else
				break;
		}
		if (stopСycle <= 1)
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

	std::cout << "Введiть будь-який символ для початку роботи програми.\n";
	std::cin >> pathRead;

	std::cout << "Введiть шлях до файла з якого будете зчитувати данi.\n";
	std::cin >> pathRead;
	
	char checkStopProgram, checkChangePathRead, checkChangePathWrite;
	ReadFile readFile;
	readFile.openNewFile(pathRead);
	do
	{
		if (!readFile.is_open())
		{
			std::cout << "Введiть шлях до файла заново, тому що по тому шляху що Ви ввели, файл не вiдкривається.\n";
			std::cin >> pathRead;
			readFile.openNewFile(pathRead);
			readFile.clear();
		}
		else
			continue;
	} while (!readFile.is_open());

	ParametersSystem parametrSystem;

	std::cout << "Введiть шлях до папки в яку будете записувати данi. Шлях до тiєї папки не повинен мати кириличнi символи:\n";
	std::cin >> pathWrite;

	while (true)
	{
		if (checkOpenPathWriteFile(pathWrite))
			break;
		else
		{
			std::cout << "Ви ввели не правильний шлях, введiть його заново:\n";
			pathWrite.clear();
			std::cin >> pathWrite;
		}
	}

	bool checkVectorAllElecDen{ false };
	std::string lastStringFile{ readFile.lastStringFile() };
	while (true)
	{
		std::cout << "Виберiть чи хочете нарiзати матрицю перпендикулярними до певної осi розрiзами(1),";
		std::cout << " чи пiд кутом до тiєї осi(2), чи прокласти шлях мiж певними точками(3):\n";

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

		std::cout << "Бажаєте продовжити виконання програми? Якщо так то введiть 'y'(скорочення вiд Yes), якщо бажаєте закiнчити її роботу то введiть 'n' (скорочення вiд No)\n";

		while (true)
		{
			std::cin >> checkStopProgram;
			std::cin.ignore(2, '\n');
			if((checkStopProgram != 'y') && (checkStopProgram != 'n'))
			{
				std::cout << "Введiть 'y' або 'n'.\n";
			}
			else
				break;
		}

		if (checkStopProgram == 'n')
			break;
		else
		{
			std::cout << "Бажаєте замiнити файл з якого зчитуються данi? Якщо так то введiть 'y'(скорочення вiд Yes), якщо бажаєте закiнчити її роботу то введiть 'n' (скорочення вiд No)\n";

			while (true)
			{
				std::cin >> checkChangePathRead;
				std::cin.ignore(2, '\n');
				if ((checkChangePathRead != 'y') && (checkChangePathRead != 'n'))
				{
					std::cout << "Введiть 'y' або 'n'.\n";
				}
				else
					break;
			}
			
			if(checkChangePathRead == 'y')
			{ 
				std::cout << "Введiть шлях до файла з якого будете зчитувати данi.\n";
				std::cin >> pathRead;

				readFile.openNewFile(pathRead);
				lastStringFile = readFile.lastStringFile();
				while(true)
				{
					if (!readFile.is_open())
					{
						std::cout << "Введiть шлях до файла заново, тому що по тому шляху що Ви ввели, файл не вiдкривається.\n";
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
				std::cout << "Тодi даннi будуть далi зчитуватися з того самого файла.\n";

			std::cout << "Якщо хочете вибрати iншу iснуючу папку для запису то введiть 'y', якщо хочете далі запичувати в ту саму то 'n'.\n";

			while (true)
			{
				std::cin >> checkChangePathWrite;
				std::cin.ignore(2, '\n');
				if ((checkChangePathWrite != 'y') && (checkChangePathWrite != 'n'))
				{
					std::cout << "Введiть 'y' або 'n'.\n";
				}
				else
					break;
			}

			if (checkChangePathWrite == 'y')
			{
				std::cout << "Тодi введiть новий шлях до папки в яку будете записувати данi. Шлях до тiєї папки не повинен мати кириличнi символи:\n";
				std::cin >> pathWrite;

				while (true)
				{
					if (checkOpenPathWriteFile(pathWrite))
						break;
					else
					{
						std::cout << "Ви ввели не правильний шлях, введiть його заново:\n";
						pathWrite.clear();
						std::cin >> pathWrite;
					}
				}
			}
			else
				std::cout << "Тодi даннi будуть далi записуватися в ту саму папку.\n";
		}
	}

	return 0;
}