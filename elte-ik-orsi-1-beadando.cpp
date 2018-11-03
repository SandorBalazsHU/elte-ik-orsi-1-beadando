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
	void puzzleSolver();
	void addRow(std::vector<int>);
	std::string toString();
};

void WORK(Puzzle* puzzle)
{
	puzzle->puzzleSolver();
	std::cout << puzzle->toString() << "\n";
};

void fileReader();

int main()
{
	static const int puzzlesNumber = 1;
	std::array<std::thread, puzzlesNumber> threads;
	std::vector<Puzzle*> puzzles;

	for (size_t i = 0; i < puzzlesNumber; i++)
	{
		puzzles.push_back(new Puzzle(3));
	}
	std::vector<int> v1 = { 1, 0, 0 };
	std::vector<int> v2 = { 0, 1, 0 };
	std::vector<int> v3 = { 2, 0, 0 };
	puzzles[0]->addRow(v1);
	puzzles[0]->addRow(v2);
	puzzles[0]->addRow(v3);

	for (size_t i = 0; i < puzzlesNumber; i++)
	{
		threads[i] = std::thread(&WORK, puzzles[i]);
	}

	for (size_t i = 0; i < puzzlesNumber; i++)
		threads[i].join();

	return 0;
};

Puzzle::Puzzle(std::size_t size) 
: size(size) {};

void Puzzle::puzzleSolver()
{
	buildEmptyFieldRegister();
	if (this->isSolution())
	{

	}
	std::cout << "Puzzle merete: " << this->size << "\n";
};

//Ha a teljesen kitöltött sorok vagy oszlopok nem az [1..N] sorozat valamely ekvivalensét tartalmazzák akkor nincs megoldás.
bool Puzzle::isSolution()
{
	bool isSolution = true;
	if (this->rowsEmptyFields.size() != 0 && columnsEmptyFields.size() != 0 && matrix.size() != 0)
	{
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
	}
	else
	{
		isSolution = false;
	}
	return isSolution;
};

void Puzzle::buildEmptyFieldRegister()
{
	if (this->rowsEmptyFields.size() == 0 && columnsEmptyFields.size() == 0 && matrix.size() != 0)
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
};

void Puzzle::addRow(std::vector<int> row)
{
	this->matrix.push_back(row);
}

std::string Puzzle::toString()
{
	std::string outputString = "";
	if (matrix.size() != 0)
	{
		for (const std::vector<int> row : this->matrix)
		{
			for (const int field : row)
			{
				outputString += std::to_string(field) + " ";
			}
			outputString.replace(outputString.size() - 1, 1,  "\n");
		}
	}
	return outputString;
};