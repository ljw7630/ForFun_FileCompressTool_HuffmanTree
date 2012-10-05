#include "allheader.h"

class HuffmanTree;
class compare;
const int maxi=270;

class HuffmanNode
{
	friend class HuffmanTree;
	friend class compare;
private:
	int value;
	int weight;
	HuffmanNode *left;
	HuffmanNode *right;
	HuffmanNode *parent;
public:
	HuffmanNode(int v,int w,HuffmanNode *p=NULL,HuffmanNode *l=NULL,HuffmanNode *r=NULL)
	{
		value=v;
		weight=w;
		parent=p;
		left=l;
		right=r;
	}
	void getCompressCode(map<int,string> &ma,string k)
	{
		if(value!=-1)
		{
			ma[value]=k;
			return;
		}
		if(left!=NULL)
			left->getCompressCode(ma,k+"0");
		if(right!=NULL)
			right->getCompressCode(ma,k+"1");
	}
};

class compare
{
public:
	bool operator()(HuffmanNode *&a,HuffmanNode *&b) const
	{
		return a->weight>b->weight;
	}
};

class HuffmanTree
{
	friend class HuffmanNode;
public:
	HuffmanNode *root;
	map<int,string>result;
	map<string,int>rev;
	bool visit[maxi];
	int countchar;
	void BuildTree(string fileName)
	{
		map<char,int>ma;
		memset(visit,false,sizeof(visit));
		priority_queue<HuffmanNode *,vector<HuffmanNode *>,compare>pq;
		GetCount(fileName,ma,visit);
		makeHuffmanTree(pq,ma,visit);
	}
	void GetCount(string fileName,map<char,int>&ma,bool *visit)
	{
		ifstream is(fileName.c_str());
		countchar=0;
		if(is.is_open())
		{
			while(!is.eof())
			{
				char ch=is.get();
				ma[ch]++;
				countchar++;
				visit[ch]=true;
			}
		}
	}
	void makeHuffmanTree(priority_queue<HuffmanNode *,vector<HuffmanNode *>,compare> &pq
		,map<char,int> &ma,bool *visit)
	{
		for(int i=0;i<maxi;++i)
		{
			if(visit[i])
			{
				HuffmanNode *newnode=new HuffmanNode(i,ma[i]);
				pq.push(newnode);
			}
		}
		if(pq.size()==1)
		{
			root=pq.top();
			pq.pop();
		}
		else
		{
			while(pq.size()>1)
			{
				HuffmanNode *n1=pq.top();pq.pop();
				HuffmanNode *n2=pq.top();pq.pop();
				HuffmanNode *res=new HuffmanNode(-1,n1->weight+n2->weight,NULL,n1,n2);
				n1->parent=n2->parent=res;
				pq.push(res);
			}
			root=pq.top();pq.pop();
		}
		ma.clear();
		result.clear();
		root->getCompressCode(result,"");
	}
	void print()
	{
		for(map<int,string>::iterator itr=result.begin();itr!=result.end();++itr)
		{
			bitset<8*sizeof(int)>bit((*itr).second);
			cout << "char " << (char) (*itr).first << " element " <<bit << endl;
		}
	}
	void Compress(string source,string dest)
	{
		BuildTree(source);
		ifstream is(source.c_str(),ios::in|ios::binary);
		ofstream os(dest.c_str(),ios::out|ios::binary);
		writeEncodingTable(os,dest);
		for(map<int,string>::iterator itr=result.begin();itr!=result.end();++itr)
		{
			writeBit(is,os,itr->second);
		}
		is.close();
		os.close();
	}
	void unCompress(string source,string dest)
	{
		ifstream is(source.c_str(),ios::in|ios::binary);
		ofstream os(dest.c_str(),ios::out|ios::binary);
		readEncodingTable(is,source);
		recover(is,os);
		is.close();
		os.close();
	}
	void writeEncodingTable(ofstream &os,string fileName)
	{
		os<<countchar<<'\n';
		for(map<int,string>::iterator itr=result.begin();itr!=result.end();++itr)
		{
			os << (char)(*itr).first<< (*itr).second<<'\n';
		}
		os << '\0' << 0 << '\n';
	}
	void writeBit(ifstream &is,ofstream &os,string val)
	{
		char ch;
		char input=0;
		string str;
		int index=0;
		int mask=0;
		while(!is.eof())
		{
			is.get(ch);
			str=result[ch];
			for(int i=0;i<str.size();++i)
			{
				if(str[i]=='1')
					mask=1;
				else
					mask=0;
				input<<=1;
				input=input|mask;
				index++;
				if(index==8)
				{
					os.write(&input,sizeof(char));
					input=0;
					index=0;
				}
			}
		}
		if(index!=0)
		{
			input = input << (8-index);
			os.write(&input,sizeof(char));
		}
	}
	void readEncodingTable(ifstream &is,string source)
	{
		rev.clear();
		char ch,nl;
		string str;
		is>>countchar;
		is.get(nl);
		while(!is.eof())
		{
			is.get(ch);
			is>>str;
			is.get(nl);
			if(ch=='\0'&&str=="0")
				break;
			rev[str]=ch;  // reverse
		}
	}
	void recover(ifstream &is,ofstream &os)
	{
		string str="",tstr;
		char ch;
		string temp;
		bool flag=false;
		while(!is.eof())
		{
			is.read(&ch,sizeof(ch));
			bitset<sizeof(ch)*8>bs(ch);
			tstr=bs.to_string();
			str+=tstr;
			for(int i=1;i<=str.size();++i)
			{
				temp=str.substr(0,i);
				map<string,int>::iterator itr=rev.find(temp);
				if(itr!=rev.end())
				{
					os << (char)itr->second;
					countchar--;
					if(countchar==1)
					{
						flag=true;
						break;
					}
					str=str.substr(i,str.size()-i);
					i=0;
				}
			}
			if(flag)
				break;
			//tstr="";
		}
	}
};