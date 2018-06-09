#pragma once
#include "stdafax.h"

struct treeNode : node {
	treeNode *left, *right;	
	treeNode(char *name, int numName, char *preSubject, int numPreName,
		char* subjectNum, int isEssential, int isDesign, int isMajor, int credit);
	treeNode() {}
};



class Tree
{
public:
	Tree();
	~Tree();
	void treeInsert(treeNode *newNode);
	void treeInsertSub(treeNode *newNode, treeNode *&rootNode);
	void showTree(treeNode *temp);
	void readTree(treeNode *temp);

private:

	treeNode *z;
	treeNode headNode;
	treeNode tailNode;
	int size;
};