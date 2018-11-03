/*
	Első beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.
	Készítette: Sándor Balázs
	Neptun: AZA6NL
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <thread>

//A puzzle-t reprezentáló osztály.
class Puzzle {
private:
	const std::size_t size;	
	std::vector <std::vector<int>> matrix;
	std::vector<int> rowsEmptyFields;
	std::vector<int> columnsEmptyFields;

	
	void buildEmptyFieldRegister();

public:
	bool isSolution();
	Puzzle(std::size_t size);
	void puzzleSolver();
	void addRow(std::vector<int>);
	std::string toString();
};

//A puzzle-ök megoldását végzi új szálon.
void WORK(Puzzle* puzzle)
{
	puzzle->puzzleSolver();
};

//A bemeneti fájl beolvasását és feldolgozását végzi.
void fileReader();

//Az eredmények fájlba írását végzi
void fileWriter();

//A főprogram
int main()
{
	static const int puzzlesNumber = 3;
	std::array<std::thread, puzzlesNumber> threads;
	std::vector<Puzzle*> puzzles;

	/*for (size_t i = 0; i < puzzlesNumber; i++)
	{
		puzzles.push_back(new Puzzle());
	}*/

	puzzles.push_back(new Puzzle(2));
	std::vector < int> av1 = { 1, 1 };
	std::vector < int> av2 = { 0, 0 };
	puzzles[0]->addRow(av1);
	puzzles[0]->addRow(av2);

	puzzles.push_back(new Puzzle(3));
	std::vector<int> bv1 = { 1, 0, 0 };
	std::vector<int> bv2 = { 0, 1, 0 };
	std::vector<int> bv3 = { 2, 0, 0 };
	puzzles[1]->addRow(bv1);
	puzzles[1]->addRow(bv2);
	puzzles[1]->addRow(bv3);

	puzzles.push_back(new Puzzle(4));
	std::vector<int> cv1 = { 1, 2, 4, 0 };
	std::vector<int> cv2 = { 3, 0, 0, 0 };
	std::vector<int> cv3 = { 0, 0, 1, 2 };
	std::vector<int> cv4 = { 2, 4, 1, 1 };
	puzzles[2]->addRow(cv1);
	puzzles[2]->addRow(cv2);
	puzzles[2]->addRow(cv3);
	puzzles[2]->addRow(cv4);

	for (size_t i = 0; i < puzzlesNumber; i++)
	{
		threads[i] = std::thread(&WORK, puzzles[i]);
	}

	for (size_t i = 0; i < puzzlesNumber; i++)
		threads[i].join();

	//debug
	for (size_t i = 0; i < puzzlesNumber; i++)
	{
		std::cout << puzzles[i]->toString();
		std::cout << "Megoldhato: " << puzzles[i]->isSolution() << std::endl;
	}

	return 0;
};

//A Puzzle osztály konstruktora
Puzzle::Puzzle(std::size_t size) 
: size(size) {};

//A tényleges megoldó algoritmus.
void Puzzle::puzzleSolver()
{
	buildEmptyFieldRegister();
	if (this->isSolution())
	{

	}
};

//Ha a teljesen kitöltött sorok vagy oszlopok nem az [1..N] sorozat valamely ekvivalensét tartalmazzák akkor nincs megoldás.
bool Puzzle::isSolution()
{
	bool isSolution = true;
	if (matrix.size() != 0)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			std::map<int, int> checkRow;
			std::map<int, int> checkCol;
			for (size_t j = 0; j < this->size; j++)
			{
				auto row = checkRow.insert(std::pair<int, int>(this->matrix[i][j], 1));
				if (row.second == false) row.first->second++;
				auto col = checkCol.insert(std::pair<int, int>(this->matrix[j][i], 1));
				if (col.second == false) col.first->second++;
			}
			for (auto & elem : checkRow)
				if (elem.first != 0 && elem.second > 1) isSolution = false;
			for (auto & elem : checkCol)
				if (elem.first != 0 && elem.second > 1) isSolution = false;
		}
	}
	else
	{
		isSolution = false;
	}
	return isSolution;
};

//Feljegyzi az üres mezők számát soronként és oszloponként
void Puzzle::buildEmptyFieldRegister()
{
	if (this->rowsEmptyFields.size() == 0 && columnsEmptyFields.size() == 0 && matrix.size() != 0)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			int emptyFieldsInRow = 0, emptyFieldsInColumn = 0;
			for (size_t j = 0; j < this->size; j++)
			{
				if (this->matrix[i][j] == 0) emptyFieldsInRow++;
				if (this->matrix[j][i] == 0) emptyFieldsInColumn++;
			}
			this->rowsEmptyFields.push_back(emptyFieldsInRow);
			this->columnsEmptyFields.push_back(emptyFieldsInColumn);
		}
	}
};

//Új sort ad a puzzle-hez.
void Puzzle::addRow(std::vector<int> row)
{
	this->matrix.push_back(row);
}

//Szüveggé alakítja a puzzle-t.
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