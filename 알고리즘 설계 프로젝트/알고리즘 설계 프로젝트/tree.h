#pragma once
#include "stdafax.h"

struct treeNode : node {
	treeNode *left, *right, *parent;
	treeNode(char *name, int numName, char *preSubject, int numPreName,
		char* subjectNum, int isEssential, int isDesign, int isMajor, int credit, int grade);
	treeNode() {}
};



class Tree
{
public:
	Tree();
	~Tree();
	void treeInsert(treeNode *newNode);
	treeNode* treeInsertSub(treeNode *newNode, treeNode *&rootNode);
	void showTree(treeNode *temp);
	void readTree(treeNode *temp);
	void searchTree(treeNode *&x, char *subName);   //TREE에서 학수번호로 찾기
	void findTree(treeNode *temp);
	void findTree2(treeNode *temp);
	void subtake();
	int treeRanking(int size, double treeScore[], string name_table[]);
	void Ranking_find(treeNode* temp, double treeScore[], string name_table[]);
	int getSize_t();
	int getCredit_t();
	int getDesign_t();
	string getName_t();

private:

	treeNode *z;
	treeNode headNode;
	treeNode tailNode;
	int size;
	int Credit_sum_t = 0;
	int Design_sum_t = 0;
	string return_name;
};