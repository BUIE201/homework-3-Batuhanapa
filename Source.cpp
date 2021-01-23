#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;

	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}

// My Study 

int FindMaximumBranch(Node* pRoot,int BranchSum,int* Max, Node* pFind){
	BranchSum += pRoot->i;

	if (pRoot->pRight)
		FindMaximumBranch(pRoot->pRight, BranchSum,Max,pFind);
	if(pRoot->pLeft)
		FindMaximumBranch(pRoot->pLeft, BranchSum,Max,pFind);
	if (!(pRoot->pRight && pRoot->pLeft)) {
		if (BranchSum > * Max) {
			*Max = BranchSum;
			pFind->i = pRoot->i;
		}
	}
	return pFind->i;
};

vector<int> FindAndInsert(Node* pRoot, int A, vector<int> temp) {
	if (pRoot->i == A) {
		temp.push_back(pRoot->i);
	}
	else if (A < pRoot->i) {
		temp.push_back(pRoot->i);
		temp = FindAndInsert(pRoot->pLeft,A,temp);
	}
	else {
		temp.push_back(pRoot->i);
		temp = FindAndInsert(pRoot->pRight, A, temp);
	}

	return temp;

}

void PrintMaximumBranch(Node* pRoot) {
	int* Max = new int(INT_MIN);
	Node* pFind = new Node(0);
	vector<int>vmax;

vmax = FindAndInsert(pRoot,FindMaximumBranch(pRoot, 0, Max, pFind),vmax);
cout << "Branch with the largest sum is: ";
for (auto a : vmax)
cout << a << " ";

cout << " -> SUM = "<<*Max ;
	delete Max;
	delete pFind;
}


// My Study

void main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}
	PrintTree(pRoot, 1);
	PrintMaximumBranch(pRoot);

}