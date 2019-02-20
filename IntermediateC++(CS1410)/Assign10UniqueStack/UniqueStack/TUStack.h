#ifndef STACK_H
#define STACK_H

template<class T>
class TUStack {
public:
	TUStack();
	TUStack(int nSize);
	~TUStack();
	void push(T item);
	T pop();
	int size();
	int position();
	T & operator[](int i);
	bool isEmpty();
	bool isFull();
	class EmptyException { };;
	class FullException { };;
	class OutOfBounds { };;
private:
	T *item;
	int nSize;
	int top;

};

template<class T>
TUStack<T>::TUStack() {
	top = 0;
	nSize = 10;
	item = new int[10];		//default constructor size
}
//constructor
template<class T>
TUStack<T>::TUStack(int nSize){
	top = 0;
	this->nSize = nSize;
	if (nSize < 0) {
		throw OutOfBounds();
	}
	item = new T[nSize];
}
//destructor
template<class T>
TUStack<T>::~TUStack() {
	delete[] item;
}
template<class T>
//push item onto the stack
void TUStack<T>::push(T newItem) {
	if (isFull()) {
		throw FullException();
	}
	item[top] = newItem;
	top++;
}
//pop item from the stack
template<class T>
T TUStack<T>::pop() {
	if (isEmpty()) {
		throw EmptyException();
	}
	return item[--top];
}
//returns number of items in stack
template<class T>
int TUStack<T>::size() {
	return nSize;
}
//returns current position of the stack pointer
template<class T>
int TUStack<T>::position() {
	return *item;

}
//Overloads the [] operator so that it returns a copy of the item located at a specified index
template<class T>
T &TUStack<T>::operator[](int i){
	if (i < 0) {
		throw OutOfBounds();
	}
	else if (i>nSize) {
		throw OutOfBounds();
	}
	else {
		return item[i];
	}
}
template<class T>
bool TUStack<T>::isEmpty() {
	if (top == 0) return true;
	else return false;
}
template<class T>
bool TUStack<T>::isFull() {
	if (top == nSize) return true;
	else return false;
}
#endif
