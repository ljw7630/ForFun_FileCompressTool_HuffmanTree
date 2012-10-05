#include "allheader.h"
#include "HuffmanTree.h"
int main(int args,char *argv[])
{
	HuffmanTree ht;
	if(argv[1])
	{
		if(strcmp(argv[1],"-c")==0)
		{
			ht.Compress(argv[2],argv[3]);
		}
		else if(strcmp(argv[1],"-d")==0)
		{
			ht.unCompress(argv[2],argv[3]);
		}
	}
	return 0;
}