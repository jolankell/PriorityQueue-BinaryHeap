#pragma once
#include <string>
#include <iostream>
using namespace std;

class Process
{	

public:
	enum class PriorityLevel
	{
		Critical,				// 0   Note this may not reflect reality
		High, 
		Mediumn,		
		Low						// 3  		
	};

	Process(string name, int processID, int size, PriorityLevel level);
	~Process();

	int getID() const;
	int getSize() const;
	string getName() const;
	PriorityLevel getPriorityLevel() const;
	friend ostream& operator<<(ostream& os, const Process& p);
	friend bool operator< (const Process &c1, const Process &c2);

private:
	std::string name;
	int processID;
	int size = 0;
	PriorityLevel prioritylevel;

};

