
#include <iostream>
#include <stdexcept>
#include "QueueADT.h"

using namespace std;

template <typename E> 
class PriorityQueue :  Queue<E> {
private:

	E *items;
	unsigned int count = 0; // number of items
	unsigned int size = 10; // size of the array, starts at 10

	bool(*compareFunction)(E, E);

	// Protect assignment
	void operator =(const PriorityQueue&) 
	{
	
	}; 

	// Protect copy constructor
	PriorityQueue(const PriorityQueue&)
	{
	
	}; 

	// Intialization helper method
	void init() 
	{  
		this->items = new E[size]();
		this->count = 0;
	}

	void removeall() { // Return link nodes to free store
		
	}

	// bubbles up the queue until property is restored
	// index is the place where the new item was added 
	void enqueueSorter(const E& it, int index) {
		
		bool swap = compareFunction(items[index / 2], items[index]);

		if (swap == true) {

			E temp = items[index / 2];
			items[index / 2] = it;
			items[index] = temp;

			if ((index / 2) != 1) {
				enqueueSorter(it, (index / 2));
			}
		}
	}

public:
	
	// takes a function pointer to a compare function
	// as a Parameter
	PriorityQueue( bool(*func)(E, E) )
	{
		compareFunction = func;
		init();
	
	} 

	// Print queue contents
	// uses a copy of the queue called printQueue to
	// print in order using dequeue without messing with 
	// current queues data
	void print()
	{
		/*for (int i = 1; i <= count; ++i) {
			cout << items[i] << " ";
		}*/

		PriorityQueue <E> printQueue(compareFunction);

		for (int i = 1; i <= count; i++) {
			printQueue.enqueue(items[i]);
		}

		cout << endl;

		while (printQueue.count != 0) {
			cout << *printQueue.dequeue() << endl;
		}

		cout << endl;

	}

	// Base destructor
	 ~PriorityQueue() 
	 {
		delete items;
	 } 

	// Reinitialize the queue. The user is responsible for
	// reclaiming the storage used by the queue elements.
	 void clear()
	 {
		 delete items;
		 size = 10;
		 count = 0;
		 items = new E[size];
	 } 

	// Place an element at the position 
	// based on its prioity of the queue.
	// it: The element being enqueued.
	 void enqueue(const E& it)	 {
		
		 if (count == 0) {
			 items[1] = it;
			 count++;
		 }
		 else {
			 int indexOfInsertion = count + 1;
			 if (indexOfInsertion >= size) {
				 size += 10;
				 E* temp = new E[size];
				 for (int i = 1; i <= count; i++) {
					 temp[i] = items[i];
				 }
				 delete items; items = temp;
			 }
			 items[indexOfInsertion] = it;
			 count++;
			 enqueueSorter(it, indexOfInsertion);
		 }
	 }

	// Remove and return element at the front of the queue.
	// Return: The element at the front of the queue.
	 E dequeue() {

		 E returnItem = items[1];
		 E temp;
		 bool done = false;
		 int direction = 0;
		 int index = 1;
		 int left, right;
		 
		 items[1] = items[count];
		 items[count] = nullptr;
		 count--;

		 while (done == false) {

			 left = index * 2; right = (index * 2) + 1;

			 if (left <= count && right <= count) {

				if (compareFunction(items[left], items[right]) == true) {
					direction = right;
				}
				else {
					direction = left;
				}
			 }

			 else if (left <= count && right > count) {
				 direction = left;
			 }

			 else if (left > count && right <= count) {
				 direction = right;
			 }

			 else if (left > this->count && right > this->count) {
				 done = true; continue;
			 }

			 if (compareFunction(items[index], items[direction]) == true) {
				 temp = items[index];
				 items[index] = items[direction];
				 items[direction] = temp;
				 index = direction;
				 continue;
			 }
			 else {
				 done = true;
			 }
		 }
		 return returnItem;
	 }

	// Return: A copy of the front element.
	 const E& frontValue() const
	 {
		 return items[1];
		
	 }

	// Return: The number of elements in the queue.
	 int length() const
	 {
		 return count;
	 }
};