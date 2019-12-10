#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef unsigned long long ull;

class Stack {
private:
	
	int * data;
	ull rear, frontInd;
	ull size;
	
public:
	
	Stack(ull dataSize);
	
	void push(int element);
	void pop();
	int front();
	bool isFull();
	bool isEmpty();
	
	~Stack();
	
};

Stack::Stack(ull dataSize)	:	size(dataSize) {
	data = new int[dataSize];
	rear = -1;
}
	
void Stack::push(int element) {

    rear++;
    rear %= size;
    data[rear] = element;

}

void Stack::pop() {
	if ( rear == -1 ) {
		return ;
	} else if ( rear == 0 ) {
		rear = size - 1; 

	}
}

int Stack::front() {
	if ( rear == - 1) {
		return -1;
	} else {
		return data[rear];
	}
}

bool Stack::isFull() {
	return ( (rear == size - 1 && frontInd == 0) || ( frontInd == rear + 1) );
}

bool Stack::isEmpty() {
	return rear == -1;
}
	
Stack::~Stack() {
    delete[] data;
}

#endif