/*
	Első beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.
	Készítette: Sándor Balázs
	Neptun: AZA6NL
*/

#include <iostream>
#include <string>
#include <thread>

void puzzleSolver(std::string s)
{
	std::cout << s << "\n";
}

int main()
{
	const int threadNumber = 5;
	std::thread threads [threadNumber];

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