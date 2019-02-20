#include <iostream>
#include <cstdlib>
#include <string>
#include<cstring>
#include<stack>

using namespace std;

class PrintJob {
public:
	PrintJob(){}
	PrintJob(string fname, int pg);
	//getter
	string getFName();
	//getter
	int getPgNum();
	//pointer to next object in linked list
	PrintJob*pNext;
private:
	string filename;
	int pageNum;
};
PrintJob::PrintJob(string f, int pg)
{
	filename = f;
	pageNum = pg;
}
//assigns filename value
string PrintJob::getFName() 
{
	return filename;
}
//assigns pageNum value
int PrintJob::getPgNum()
{
	return pageNum;
}

class PrintQueue {
public:
	PrintQueue() {pHead = NULL;}
	void enqueue(string filename, int page);
	PrintJob *insertFront(PrintJob *&ppHead, PrintJob task);
	PrintJob *insertOrdered(PrintJob *&ppHead, PrintJob task);
	PrintJob *dequeue();
	bool empty();
	void displayList(PrintJob *ppHead);
	void display();
private:
	//pointer to linked list header
	PrintJob *pHead;
};

void PrintQueue::enqueue(string filename, int page) 
{
	PrintJob task(filename, page);
	pHead = insertOrdered(pHead, task);
}
//Similar to Dan's in class code to create an ordered list
PrintJob *PrintQueue:: insertFront(PrintJob *& pHead, PrintJob task) 
{
	PrintJob * newPrintJob = new PrintJob(task);
	newPrintJob->pNext = pHead;
	return newPrintJob;
}
//Similar to Dan's in class code to create an ordered list
PrintJob*PrintQueue::insertOrdered(PrintJob *& pHead, PrintJob task) 
{
	//If queue is empty, set the current value to the header
	if (!pHead)return insertFront(pHead, task);
	//if current header value for pageNum is greater than the objects pageNum being added,
	//push the new objects pageNum to the header
	if (pHead->getPgNum() > task.getPgNum()) { return insertFront(pHead, task); }
	//else add it to the queue.
	pHead->pNext = insertOrdered((pHead->pNext), task);
	return pHead;
}

PrintJob*PrintQueue::dequeue()
{
	if (!pHead) { cout << "Empty Queue" << endl; return 0; }
	//declare a temp value to hold a new pHead
	PrintJob *temp1;
	temp1 = pHead;
	//Set pHead to the next value;
	pHead = pHead->pNext;
	return temp1;
}
//Checks to see if the queue is empty
bool PrintQueue::empty() 
{
	if (!pHead)return true;
	else return false;
}
//Similar to Dan's printList in class code
//Changed the name to displayList so it wasn't confused with
//all the other classes and functions with Print in the title
void PrintQueue:: displayList(PrintJob * pHead) 
{
	//If empty print nothing
	if (!pHead) { return; }
	//Print contents of item in linked list then point to next item
	cout <<"Filename: "<< pHead->getFName() << endl;
	cout << "Number of Pages: " << pHead->getPgNum() << endl;
	displayList((pHead->pNext));
	return;
}
void PrintQueue::display() 
{
	//Calls displayList without passing parameters
	displayList(pHead);
}
int main() {
	PrintJob j1;
	PrintQueue q1;
	//Check to see if the empty function works
	if (q1.empty() == true) {
		cout << "Empty Queue" << endl;
	}
	else
	{
		cout<<"Queue is not Empty" << endl;
	}
	cout << endl << endl;
	q1.enqueue("File 1", (50));
	q1.display();
	cout << endl;
	if (q1.empty() == true) {
		cout << "Empty Queue" << endl;
	}
	else
	{
		cout << "Queue is not Empty" << endl;
	}
	cout << endl << endl;
	q1.enqueue("File 2", (5));
	q1.enqueue("File 3", (25));
	q1.enqueue("File 4", (2));
	q1.enqueue("File 5", (52));
	q1.enqueue("File 6", (252));
	q1.display();
	cout << endl << endl;
	
	q1.dequeue();
	cout << "Dequeue test 1, 1 dequeued, 5 remaining" << endl;
	q1.display();
	cout << endl;
	q1.dequeue();
	q1.dequeue();
	q1.dequeue();
	cout << "Dequeue test 2, 4 total dequeued, 2 remaining" << endl;
	q1.display();
	//Empty Queue
	q1.dequeue();
	q1.dequeue();
	cout << endl;
	if (q1.empty() == true) {
		cout << "Empty Queue" << endl;
	}
	else
	{
		cout << "Queue is not Empty" << endl;
	}
	
	return 0;
}