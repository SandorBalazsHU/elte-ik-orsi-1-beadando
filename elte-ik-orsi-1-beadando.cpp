/*
	Első beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.
	Készítette: Sándor Balázs
	Neptun: AZA6NL
	---
	Az algoritmus:
	   1 2 2 2
	   -------
	1 | 1 2 4 0
	3 | 3 0 0 0
	2 | 0 0 1 2
	1 | 2 4 0 1
	Első lépésként a fent látható módon megjelöljük az üres mezőket és eltároljuk az emptyFieldRegister-ben.
	Ez az első lépésben 1 3 2 1 1 2 2 2. Ebben kiválasztjuk az első legkissebbet ami az 1.
	Ezel kiválasztottuk a 0,3 pontot első kitöltésre. A megoldást innen a halmazműveletekre alapozom.
	Mivel a sorban 1 szabad hely van így [1 2 3 4] - [1 2 4 0] = [3] kerül ebbe a mezőbe. Ha 1-nél több üres hely
	van akkor ezt a kivonást elvégezzük a pontra merőleges sorra is és a két eredmény metszetéből kerül ki az eredmny.
	Ezután frissítjük az emptyFieldRegister-t és folytatódik az iteráció mindaddig míg az emptyFieldRegister ki nem ürül.
	---
	A feladatkírás szerint a teljes program 1 fájlba került.
	---
	A feladatot GitHub-on verziókezeltem. A leadási határidő utáni napon privátról publikussá teszem a repositoryt.
	A repository címe: https://github.com/SandorBalazsHU/elte-ik-orsi-1-beadando
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <thread>
#include <map>
#include <set>

//A puzzle-t reprezentáló osztály.
class Puzzle {
private:
	const std::size_t size;	
	std::vector <std::vector<int>> matrix;
	std::vector<int> emptyFieldRegister;

	bool isSolution();
	void buildEmptyFieldRegister();
	std::vector<int>* getRow(int);
	std::vector<int> getCol(int);
	std::map<char, int> getNextField();
	int find(std::vector<int>*, int);
	bool solutionIsRedy();

public:
	Puzzle(std::size_t size);
	void puzzleSolver();
	void addRow(std::vector<int>);
	std::string toString();
}; 

//A puzzle-ök megoldását végzi új szálon.
void WORK(Puzzle* puzzle) {
	puzzle->puzzleSolver();
};

//A bemeneti fájl beolvasását és feldolgozását végzi.
std::vector<Puzzle*> fileReader(std::string);

//Az eredmények fájlba írását végzi
void fileWriter(std::vector<Puzzle*>, std::string);

//sring konverzió int be whitespace-ek nélkül
int stringToInt(std::string);

//A főprogram
int main() {
	std::vector<Puzzle*> puzzles = fileReader("input.txt");
	std::vector<std::thread> threads;
	const size_t puzzlesNumber = puzzles.size();
	for (size_t i = 0; i < puzzlesNumber; i++) threads.push_back(std::thread(&WORK, puzzles[i]));
	for (size_t i = 0; i < puzzlesNumber; i++) threads[i].join();
	fileWriter(puzzles, "output.txt");
};

//A Puzzle osztály konstruktora
Puzzle::Puzzle(std::size_t size) : size(size) {};

//A tényleges megoldó algoritmus. (A Leírás a fejlécben található)
void Puzzle::puzzleSolver() {
	if (this->isSolution()) {

		this->buildEmptyFieldRegister();
		std::set<int> pattern;
		std::vector<int> mem;
		for (int i = 1; i <= this->size; i++) pattern.insert(i);

		while (this->solutionIsRedy()) {

			std::map<char, int>	field = this->getNextField();
			this->emptyFieldRegister[field['x']] -= 1;
			this->emptyFieldRegister[this->size + field['y']] -= 1;

			std::set<int> current;
			if (field['o'] == 1)  current = std::set<int>(this->getRow(field['x'])->begin(), this->getRow(field['x'])->end());
			if (field['o'] == -1) {
				std::vector<int> col = getCol(field['y']);
				current = std::set<int>(col.begin(), col.end());
			}
			std::set<int> difference;
			std::set_difference(pattern.begin(), pattern.end(), current.begin(), current.end(), std::inserter(difference, difference.begin()));
			int insertable = -1;
			if (field['v'] == 1) {
				insertable = *difference.begin();
				this->matrix[field['x']][field['y']] = insertable;
				if (!this->isSolution() && mem.size() != 0) {
					this->matrix[mem[0]][mem[1]] = mem[3]; insertable = mem[2];
				}
			} else {
				std::vector<int> perpendicular;
				if (field['o'] == -1) {
					perpendicular = *this->getRow(field['x']);
				}else{
					perpendicular = this->getCol(field['y']);
				}
				std::set<int> TSet(perpendicular.begin(), perpendicular.end());
				std::set<int> TSetdifference;
				std::set_difference(pattern.begin(), pattern.end(), TSet.begin(), TSet.end(), std::inserter(TSetdifference, TSetdifference.begin()));
				std::set<int> intersect;
				std::set_intersection(difference.begin(), difference.end(), TSetdifference.begin(), TSetdifference.end(), std::inserter(intersect, intersect.begin()));
				insertable = *intersect.begin();
				mem.clear(); mem.push_back(field['x']); mem.push_back(field['y']); for (int n : intersect) mem.push_back(n);
			}
			this->matrix[field['x']][field['y']]=insertable;
		}
	}
};

//Visszaadja a következő legtelítettebb sort vagy oszlopot, ezel a következő ideálisan kitöltendő mezőt.
std::map<char, int> Puzzle::getNextField() {
	std::map<char, int> data;
	std::set<int> emptyFieldsSet(this->emptyFieldRegister.begin(), this->emptyFieldRegister.end());
	emptyFieldsSet.erase(0);
	int minimum = *emptyFieldsSet.begin();
	data['v'] = minimum;
	int position = this->find(&this->emptyFieldRegister, minimum);

	if (position < this->size) {
		std::vector<int>* row = this->getRow(position);
		int positionY = this->find(row, 0);
		data['x'] = position;
		data['y'] = positionY;
		data['o'] = 1;
	} else {
		data['y'] = position - static_cast<int>(this->size);
		std::vector<int> col = this->getCol(data['y']);
		int positionX = find(&col, 0);
		data['x'] = positionX;
		data['o'] = -1;
	}
	return data;
}

//Ha egy sorban vagy oszlopban ismétlődő elemek vannak (a 0-n kívül) akkor nincs megoldás.
bool Puzzle::isSolution() {
	bool isSolution = true;
	if (matrix.size() != 0) {
		for (size_t i = 0; i < this->size; i++) {
			std::map<int, int> checkRow;
			std::map<int, int> checkCol;
			for (size_t j = 0; j < this->size; j++) {
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
	}else{
		isSolution = false;
	}
	return isSolution;
};

//Feljegyzi az üres mezők számát soronként és oszloponként
void Puzzle::buildEmptyFieldRegister() {
	if (this->emptyFieldRegister.size() == 0 && matrix.size() != 0) {
		std::vector<int> columnsEmptyFields;
		for (size_t i = 0; i < this->size; i++) {
			int emptyFieldsInRow = 0, emptyFieldsInColumn = 0;
			for (size_t j = 0; j < this->size; j++) {
				if (this->matrix[i][j] == 0) emptyFieldsInRow++;
				if (this->matrix[j][i] == 0) emptyFieldsInColumn++;
			}
			this->emptyFieldRegister.push_back(emptyFieldsInRow);
			columnsEmptyFields.push_back(emptyFieldsInColumn);
		}
		this->emptyFieldRegister.insert(this->emptyFieldRegister.end(), columnsEmptyFields.begin(), columnsEmptyFields.end());
	}
};

//Szüveggé alakítja a puzzle-t.
std::string Puzzle::toString() {
	std::string outputString = "";
	if (matrix.size() != 0) {
		for (const std::vector<int> row : this->matrix) {
			for (const int field : row) {
				outputString += std::to_string(field) + " ";
			}
			outputString.replace(outputString.size() - 1, 1,  "\n");
		}
	}
	return outputString;
};

//Ha nincs üres mező akkor a megoldás elkészült.
bool Puzzle::solutionIsRedy() {
	int sumOfElems = std::accumulate(this->emptyFieldRegister.begin(), this->emptyFieldRegister.end(), 0);
	return sumOfElems != 0;
}

//Megkeres egy elemet egy vektorban
int Puzzle::find(std::vector<int>* vector, int item) {
	size_t i = 0;
	int x;
	while (i < vector->size() && (x = vector->at(i)) != item) i++;
	return static_cast<int>(i);
}

//Pointert ad vissza egy kért sorra
std::vector<int>* Puzzle::getRow(int i) {
	return &this->matrix[i];
}

//Pointert ad vissza egy kért oszlopra
std::vector<int> Puzzle::getCol(int j) {
	std::vector<int> col;
	for (size_t i = 0; i < this->size; i++) col.push_back(this->matrix[i][j]);
	return col;
}

//Új sort ad a puzzle-hez.
void Puzzle::addRow(std::vector<int> row) {
	this->matrix.push_back(row);
}

//sring konverzió int be whitespace-ek nélkül
int stringToInt(std::string str)
{
	std::stringstream stream(str);
	int number = 0;
	stream >> number;
	return number;
}

//A bemeneti fájl beolvasását és feldolgozását végzi.
std::vector<Puzzle*> fileReader(std::string inputFile) {
	std::vector<Puzzle*> puzzles;

	std::ifstream file("input.txt");
	if (!file.good()) std::cout << "The input file dosen't exist!" << std::endl;
	std::string str;
	std::getline(file, str);
	int puzzlesNumber = stringToInt(str);
	for (size_t i = 0; i < puzzlesNumber; i++)
	{
		str.clear();
		std::getline(file, str);
		int puzzleSize = stringToInt(str);
		puzzles.push_back(new Puzzle(puzzleSize));
		for (size_t j = 0; j < puzzleSize; j++)
		{
			std::getline(file, str);
			std::istringstream iss(str);
			std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
			std::vector<int> elements;
			for (size_t k = 0; k < puzzleSize; k++) elements.push_back(stringToInt(results[k]));
			puzzles[i]->addRow(elements);
		}
	}
	return puzzles;
}

//Az eredmények fájlba írását végzi
void fileWriter(std::vector<Puzzle*> puzzles, std::string outputFile) {
	std::ofstream myfile;
	myfile.open(outputFile);
	for (size_t i = 0; i < puzzles.size(); i++) myfile << puzzles[i]->toString();
	myfile.close();
}