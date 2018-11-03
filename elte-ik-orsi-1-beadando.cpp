/*
	Első beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.
	Készítette: Sándor Balázs
	Neptun: AZA6NL
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <thread>

void fileReader();

class Puzzle {

private:
	const std::size_t size;	
	std::vector <std::vector<int>> matrix;
	std::vector<int> rowsEmptyFields;
	std::vector<int> columnsEmptyFields;

	bool isSolution();
	void buildEmptyFieldRegister();

public:
	Puzzle(std::size_t size);
	void operator()();
	void puzzleSolver();
	std::string toString();
};

int main()
{
	static const int threadNumber = 5;
	std::array<std::thread, threadNumber> threads;

	for (size_t i = 0; i < threadNumber; i++)
	{
		std::string s = "Thread_" + std::to_string(i+1) + "\n";
		threads[i] = std::thread(&puzzleSolver, s);
	}

	std::cout << "main thread\n";

	for (size_t i = 0; i < threadNumber; i++)
	{
		threads[i].join();
	}

	std::cout << "end\n";

	return 0;
}

Puzzle::Puzzle(std::size_t size) 
: size(size)
{
	buildEmptyFieldRegister();
}

void Puzzle::operator()()
{

}

//Ha a teljesen kitöltött sorok vagy oszlopok nem az [1..N] sorozat valamely ekvivalensét tartalmazzák akkor nincs megoldás.
bool Puzzle::isSolution()
{
	bool isSolution = true;
	std::set<int> correctSolution;
	for (size_t i = 1; i < this->size; i++) correctSolution.insert(i);
	for (size_t i = 0; i < this->size; i++)
	{
		if (this->rowsEmptyFields[i] == 0)
		{
			std::set<int> rowCheck;
			for (size_t j = 0; j < this->size; j++)
				rowCheck.insert(this->matrix[i][j]);
			if (rowCheck != correctSolution) isSolution = false;
		}
		if (this->columnsEmptyFields[i] == 0)
		{
			std::set<int> columnCheck;
			for (size_t j = 0; j < this->size; j++)
				columnCheck.insert(this->matrix[j][i]);
			if (columnCheck != correctSolution) isSolution = false;
		}
	}
	return isSolution;
}

void Puzzle::buildEmptyFieldRegister()
{
	if (this->rowsEmptyFields.size() == 0 && columnsEmptyFields.size() == 0)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			int emptyFieldsInRow = 0, emptyFieldsInColumn = 0;
			for (size_t j = 0; j < this->size; j++)
			{
				if (this->matrix[j][i] == 0) emptyFieldsInRow++;
				if (this->matrix[i][j] == 0) emptyFieldsInColumn++;
			}
			this->rowsEmptyFields.push_back(emptyFieldsInRow);
			this->columnsEmptyFields.push_back(emptyFieldsInColumn);
		}
	}
}

std::string Puzzle::toString()
{
	std::string outputString;
	for (const std::vector<int> row : this->matrix)
	{
		for (const int field : row)
		{
			outputString += std::to_string(field) + " ";
		}
		outputString.replace(1, outputString.size() - 1, "\n");
	}
	return outputString;
}