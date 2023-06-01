#pragma once
#include <iostream>

template <class T>
class SmartStack
{
private:
	unsigned int size;
	int top;
	T * mas;

public:
	// Constructors
	SmartStack(unsigned int max_size);
	// Methods
	bool push(T val);
	T pop();
	T take();
	bool is_empty();
	// Operators
	T operator -- ();
	bool operator << (T val);
};


// Constructor 1
// Gets the value of dynamic array's size
template <class T>
SmartStack<T>::SmartStack(unsigned int max_size)
{
	this->size = max_size;
	this->mas = new T[this->size];
	this->top = -1;
}


// Method puts new value to the top of stack (if possible)
template <class T>
bool SmartStack<T>::push(T val)
{
	if (top == size - 1) {
		std::cout << "ERROR: Stack overflow!" << std::endl;
		return false;
	}
	mas[++top] = val;
	return true;
}


// Method gets top value and removes it from the stack
template <class T>
T SmartStack<T>::pop()
{
	T temp = this->take();
	top--;
	return temp;
}

// Method gets top value
template <class T>
T SmartStack<T>::take()
{
	if (top == -1) {
		std::cout << "ERROR: Stack is empty!" << std::endl;
		throw "Stack is empty!";
	}
	return mas[top];
}



// Returns true if stack is empty, else: false
template <class T>
bool SmartStack<T>::is_empty()
{
	if (top == -1) return true;
	else return false;
}


// Operator -- overload  (= pop)
template <class T>
T SmartStack<T>::operator--()
{
	return this->pop();
}


// Operator << overload (= push)
template <class T>
bool SmartStack<T>::operator<<(T val)
{
	return this->push(val);
}
