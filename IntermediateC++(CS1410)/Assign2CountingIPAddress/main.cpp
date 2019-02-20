#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class IPRecord {
private:
	unsigned int m_IP;      // IP address as a 32-bit unsighed int
	unsigned int m_freq;    // frequency of the IP

public:
	IPRecord() { m_IP = 0; m_freq = 0; }

	void setIP(int IP) { m_IP = IP; }
	void incFrequency() { m_freq++; }

	unsigned int getIP() { return m_IP; }
	unsigned int getFrequency() { return m_freq; }
};

int binarySearch(IPRecord *pTable, int size, unsigned int IP)
{
	int first = 0,								//First array element
		last = size - 1,						//Last array element
		middle,									//Midpoint of search
		position = -1;							//Position of search value
	bool found = false;							//Flag

	while (!found&&first <= last)
	{
		middle = (first + last) / 2;			//Calculate midpoint
		if (pTable[middle].getIP() == IP)		//If value is found at mid
		{
			found = true;					
			position = middle;
		}
		else if (pTable[middle].getIP() > IP)		//If value is in lower half
			last = middle - 1;
		else
												//If value is in upper half
			first = middle + 1;
	}
	return position;

	// TODO: Task 1 - 5 points. 
	// Lookup IPRecord with the given IP
}

int insert(IPRecord *pTable, int& rSize, unsigned int IP) {
	// TODO: Task 2 - 10 points. 
	// Create an IPRecord for the given IP and insert it in the proper location 
	// to keep array pTable sorted increasingly by IPs.
	IPRecord rec;
	rec.setIP(IP);
	rec.incFrequency();

	rSize++;
	for (int i = rSize - 1; i > 0; i--) {
		if (IP < pTable[i - 1].getIP()) {
			pTable[i] = pTable[i - 1];
		}
		else {
			pTable[i] = rec;
			break;
		}
	}
	return -1;
}

int sortFrequency(IPRecord *pTable, int size)
{
	// TODO: Task 3 - 5 points. 
	// Sort the IP table by frequency descendingly
	int min;
	for (int i = 0; i < size; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			if (pTable[j].getFrequency() < pTable[min].getFrequency()) {
				min = j;
			}
		}
		if (pTable[i].getFrequency() > pTable[min].getFrequency()) {
			IPRecord temp = pTable[i];
			pTable[i] = pTable[min];
			pTable[min] = temp;
		}
	}
	return 1;
	
}


int main() {
	IPRecord *myIPTable;    // dynamic array to store all IPRecords
	int maxSize;            // allocated size of myIPTable, i.e. number of distinct IPs 
	int size = 0;           // the current size of myIPTable, i.e. number of distinct IPs seen so far    

	ifstream fi("input.txt"); // open input file

	fi >> maxSize;            // read table size;

	myIPTable = new IPRecord[maxSize]; // allocate memory

	unsigned ip;
	while (fi >> ip) {     // reading IP addresses from input file until the end
		int pos = binarySearch(myIPTable, size, ip);    // looking up this IP in the table
		if (pos >= 0)
			myIPTable[pos].incFrequency();      // if found: increase its frequency
		else
			insert(myIPTable, size, ip);        // if not found: insert as a new IPRecord
	}

	fi.close();            // close input file

	sortFrequency(myIPTable, size); // sort IPRecords by frequency descendingly

	ofstream fo("output.txt"); // open output file

	for (int i = 0; i < size; i++) // print each IPRecord in one line
		fo << myIPTable[i].getIP() << ' ' << myIPTable[i].getFrequency() << endl;

	fo.close();         // close output file

	delete[] myIPTable; // de-allocate memory;
}
