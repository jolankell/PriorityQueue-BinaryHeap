
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "Process.h"
#include "PriorityQueue.h"


vector<string> split(const string& s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

vector<Process*> load(const string& filename) {
	vector<Process*> list;
	ifstream file(filename);

	string str;
	while (getline(file, str))	{
		vector<string> tokens = split(str, ',');
		list.push_back(new Process(tokens[0], stoi(tokens[1]), stoi(tokens[2]), static_cast<Process::PriorityLevel>(stoi(tokens[3]))));
	}

	return list;
}

bool compare(int first, int second)
{
	return (first > second);
}

bool compareProcess(Process* first, Process* second)
{
	return (first->getPriorityLevel() > second->getPriorityLevel());
}


int main() {

	//srand(static_cast<unsigned int> (time(nullptr))); // real random
	srand( 345 );		// for consistent test runs
	int random = 0;

	//Random Numbers
	PriorityQueue<int> pq( compare );					// Example using a Function 

	//PriorityQueue<int> pq( [](int first, int second)    // Example using Lambda Express 
	//	{
	//		return (first > second);
	//	} );

	for (int x = 0; x < 20; x++) {
		random = rand() % 100 + 1;			
		// cout << random << " " ;              // original
		cout << "enqueue: " << random << endl;
		pq.enqueue(random);
		//pq.print();   // added for debug
		//cout << endl; // added for debug
	}
	cout << endl;


	for (int x = 0; x < 20; x++)
		 cout << pq.dequeue() << " ";
	cout << endl << endl;

	//Process with Function Pointer
	vector<Process*> processes = load("ProcessList.txt");

	cout << "Processes as read from File\n";
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl ;		
	for (Process* process : processes) // access by reference to avoid copying
	{
		cout << (*process) << endl;    // displaying processing that are to be enqueue....debug information
	}
	cout << endl;

	//Example Process Queue with Function Pointer
	PriorityQueue<Process*> processq( &compareProcess );
	for (Process* process : processes) // access by reference to avoid copying
	{
		processq.enqueue(process);
	}
	cout << endl << endl;

	cout << "Start DEQUEUE processq " << endl;
		
	while (processq.length() > 0)
	{
		std::cout << processq.length() << " ";
		std::cout << *(processq.dequeue()) << " ";
		std::cout << std::endl;
	}


	//Example Process Queue with Lamda
	PriorityQueue<Process*> processqLambda( [](Process* first, Process* second)
		{
			return (first->getPriorityLevel() > second->getPriorityLevel());
		});


	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambda.enqueue(process);
	}
	cout << endl;

	std::cout << "Start DEQUEUE processqLambda " << endl;
	while (processqLambda.length() > 0)
	{
		std::cout << processqLambda.length() << " ";
		std::cout << *(processqLambda.dequeue()) << " ";
		std::cout << std::endl;
	}

	// Part 2 A prioritize by ID: ascending order

	// Part 2 B prioritize by PriorityLevel Reverse 

	// Part 2 C prioritize by Size Large to small

	// Part 2 D prioritize by Name as in Dictionary (shift to lower during comparison)

	// Part 2 E prioritize by Name Reverse Dictionary (shift to lower during comparison)

	// Part 2 F prioritize by PriorityLevel Critcal then High then ALL others equal(i.e.rough order they arrived)

	system("pause");
	return 0;
}
