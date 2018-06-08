#pragma once
#include "stdafax.h"

struct treeNode : node {
	treeNode *left, *right;	
	treeNode(char *name, int numName, char *preSubject, int numPreName,
		char* subjectNum, int isEssential, int isDesign, int isMajor, int credit)
	{
		this->numName = numName;
		this->numPreName = numPreName;
		this->isEssential = isEssential;
		this->isDesign = isDesign;
		this->isMajor = isMajor;
		this->credit = credit;

		this->name = new char[numName];
		for (int i = 0; i < numName; i++)
			this->name[i] = name[i];

		this->preSubject = new char[numPreName];
		for (int i = 0; i < numPreName; i++)
			this->preSubject[i] = preSubject[i];

		this->subjectNum = new char[7];
		for (int i = 0; i < 7; i++)
			this->subjectNum[i] = subjectNum[i];
	}
	treeNode() {}
};



class Tree
{
public:
	Tree();
	~Tree();
	void treeInsert(treeNode newNode);
	void showTree(treeNode *temp);
	void readTree(treeNode *temp);

private:

	treeNode *z;
	treeNode headNode;
	treeNode tailNode;
	int size;
};