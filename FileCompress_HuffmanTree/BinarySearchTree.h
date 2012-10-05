#include "allheader.h"

template <class T>
class BinarySearchTree;

template <class T>
class BinarySearchTreeNode
{
private:
	friend class BinarySearchTree<T>;
	BinarySearchTreeNode *leftChild;
	BinarySearchTreeNode *rightChild;
	T data;
public:
	BinarySearchTreeNode(T item=T(),BinarySearchTreeNode *l=NULL,BinarySearchTreeNode *r=NULL):
	  data(item),leftChild(l),rightChild(r)
	  {
	  
	  }
	~BinarySearchTreeNode()
	{
	
	}
	BinarySearchTreeNode* &Left(void)
	{
		return leftChild;
	}
	BinarySearchTreeNode* &Right(void)
	{
		return rightChild;
	}
	void printPreOrder() const
	{
		cout << data << " ";
		if(leftChild!=NULL)
			leftChild->printPreOrder();
		if(rightChild!=NULL)
			rightChild->printPreOrder();
	}
	void printPostOrder() const
	{
		if(leftChild!=NULL)
			leftChild->printPostOrder();
		if(rightChild!=NULL)
			rightChild->printPostOrder();	
		cout << data << " ";
	}
	void printInOrder() const 
	{
		if(leftChild!=NULL)
			leftChild->printInOrder();
		cout << data << " ";		
		if(rightChild!=NULL)
			rightChild->printInOrder();	
	}
	void printLevelOrder() const
	{
		queue<const BinarySearchTreeNode *> q;
		q.push(this);
		while(!q.empty())
		{
			const BinarySearchTreeNode *t=q.front();
			q.pop();
			cout << t->data << " ";
			if(t->leftChild!=NULL)
				q.push(t->leftChild);
			if(t->rightChild!=NULL)
				q.push(t->rightChild);
		}
	}
};

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
		root=new BinarySearchTreeNode();
	}
	BinarySearchTree(const T & item):root(new BinarySearchTreeNode<T>(item))
	{
	}
	~BinarySearchTree()
	{
		makeEmpty(root);
	}
	void makeEmpty(BinarySearchTreeNode<T> *&r)
	{
		if(r!=NULL)
		{
			makeEmpty(r->leftChild);
			makeEmpty(r->rightChild);
			delete r;
			r=NULL;
		}
	}
	bool isEmpty() const
	{
		return root==NULL;
	}
	void insert(const T & item)
	{
		insert(item,root);
	}
	void insert(const T &item,BinarySearchTreeNode<T> *&root)
	{
		if(root==NULL)
		{
			root=new BinarySearchTreeNode<T>;
			root->data=item;
		}
		else if(item<root->data)
		{
			insert(item,root->leftChild);
		}
		else
		{
			insert(item,root->rightChild);
		}
	}
	void printPreOrder() const
	{
		root->printPreOrder();
		cout << endl;
	}
	void printPostOrder() const
	{
		root->printPostOrder();
		cout <<endl;
	}
	void printInOrder() const
	{
		root->printInOrder();
		cout << endl;
	}
	void printLevelOrder() const
	{
		root->printLevelOrder();
		cout << endl;
	}
private:
	BinarySearchTreeNode<T> *root;
};