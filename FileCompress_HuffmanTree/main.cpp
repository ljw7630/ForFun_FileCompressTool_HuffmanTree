#include "allheader.h"
#include "HuffmanTree.h"
int main(int args,char )
{
	//srand(time(NULL));
	//BinarySearchTree<int> br(20);
	//for(int i=0;i<10;++i)
	//	br.insert(rand()%40);
	//cout << "preOrder" << endl;
	//br.printPreOrder();
	//cout << "PostOrder" << endl;
	//br.printPostOrder();
	//cout << "InOrder"  << endl;
	//br.printInOrder();
	//cout << "LevelOrder" << endl;
	//br.printLevelOrder();
	HuffmanTree ht;
	//ht.BuildTree("future.txt");
	//ht.print();
	ht.Compress("in.txt","out.txt");
	ht.unCompress("out.txt","newfile.txt");
	system("pause");
	return 0;
}