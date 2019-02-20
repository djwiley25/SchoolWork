#include "Node.cpp"
#include "Tree.cpp"
#include<iostream>
#include<fstream>
#include<string>



int main()
{
	ifstream inf;
	ofstream outf;
	outf.open("prog2Out.txt");
	inf.open("prog2In.txt");
	//assert(inf);
	//assert(outf);
	const int SIZE = 12;
	Tree t[SIZE];
	for (int i = 0; i < SIZE; i++)
      t[i].buildFromPrefix(inf);
	for (int i = 0; i < SIZE; i++){
		cout << "Tree" << i << "\n" << t[i].printTree();
		//outf << "Tree" << i << "\n" << t[i].printTree();
		//cout << "FRINGE " <<t[i].fringe() << endl;
	}
	//if (t[0].findWord("dins") == NULL) cout << "dins not found\n";
	//if (t[0].findWord("tone") == NULL) cout << "tone not found\n";
	//t[0].upCase();
	//cout << t[0].printTree();
	//if (t[0].findWord("guck") == NULL) cout << "guck not found\n";
	//if (t[0].findWord("TONE") == NULL) cout << "TONE not found\n";

	//t[7].makeEmpty();
	//cout << "empty tree fringe " << t[7].fringe() << endl;

	//for (int i = 0; i < SIZE; i++){
	//	cout << "NodesInLevel 2 of tree" << i << " " << t[i].nodesInLevel(2) << endl;
	//}
	//cout << " TREE 3\n" <<  t[3].printTree();
	//cout << " TREE 10\n" << t[10].printTree();
	//t[3] = t[10].clone();
	//t[3].upCase();
	//cout << " TREE 3 cloned\n" << t[3].printTree();
	//cout << " TREE 10\n" << t[10].printTree();

	//for (int i = 0; i < SIZE; i++)
	//	for (int j = i + 1; j < SIZE; j++)
	//		if (t[i].isIsomorphic( t[j])) cout << "Two trees are isomorphic Tree:" << i << " Tree:" << j << endl;
	//cout << "Common Ancestor of lade and gunk " << t[2].commonAncestor("lade", "gunk") << endl;
	//cout << "Common Ancestor of luce and gunk " << t[1].commonAncestor("luce", "gunk") << endl;
	//cout << "Common Ancestor of lick and dene " << t[1].commonAncestor("lick", "dene") << endl;
	//cout << "Common Ancestor of lick and muck " << t[1].commonAncestor("lick", "muck") << endl;
	//char c;
	//cin >> c;
	//outf.close();
}

