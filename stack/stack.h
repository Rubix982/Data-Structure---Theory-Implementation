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
	ull rear;
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
	if ( ( rear + 1  ) == size ) {
		std::cout << "Stack is full.\n";
	} else {
		rear++;
		data[rear] = element;
	}
}

void Stack::pop() {
	if ( rear == -1 ) {
//		std::cout << "Stack is already empty.\n";
		return ;
	} else {
		rear--;
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
	return ( rear + 1 ) == size;
}

bool Stack::isEmpty() {
	return rear == -1;
}
	
Stack::~Stack() {
    delete[] data;
}

#endif