#pragma once
#include "stdafax.h"

Tree::Tree()
{
	z = &tailNode;
	z->left = z;
	z->right = z;
	headNode.right = z;


	string tempLine = "";
	
	ifstream input("subject.txt");

	getline(input, tempLine);
	this->size = stoi(tempLine);
	

	for (int i = 0; i < size; i++)
	{
		char *nameTemp, *preNameTemp, *numTemp;
		int nameNumTemp, preNameNumTemp;
		int essential, design, major, credit;

		getline(input, tempLine);
		nameNumTemp = tempLine.length();

		nameTemp = new char[nameNumTemp];
		strncpy(nameTemp, tempLine.c_str(), nameNumTemp);
		

		getline(input, tempLine);
		if (tempLine == "") 
		{
			preNameNumTemp = 0; preNameTemp =0;
		}
		else
		{
			preNameNumTemp = tempLine.length();
			preNameTemp = new char[preNameNumTemp];
			strncpy(preNameTemp, tempLine.c_str(), preNameNumTemp);
		}

		getline(input, tempLine);
		numTemp = new char[7];
		strncpy(numTemp, tempLine.c_str(), 7);

		getline(input, tempLine);
		essential = stoi(tempLine);

		getline(input, tempLine);
		design = stoi(tempLine);

		getline(input, tempLine);
		major = stoi(tempLine);

		getline(input, tempLine);
		credit = stoi(tempLine);

		for (int i = 0; i < 7; i++)
			cout << numTemp[i];
		cout << endl;

		treeNode newNode(nameTemp, nameNumTemp, preNameTemp, preNameNumTemp, numTemp,
			essential, design, major, credit);
		//treeNode *insertNode = &newNode;
		
		newNode.right = z;
		newNode.left = z;
		treeInsert(newNode);
		//insertNode->right = z;
		//insertNode->left = z;
		//treeInsert(insertNode);
	}
	showTree(headNode.right);
}

Tree::~Tree()
{
}

void Tree::treeInsert(treeNode newNode)
{
	treeNode *tempNode;
	tempNode = headNode.right;

	if (headNode.right == z)
	{
		headNode.right = &newNode;
	}
	else
	{
	    for (int i = 0; i < 7; i++)
			cout << headNode.right->subjectNum[i];
		for (int i = 0; i < 7; i++)
			cout << newNode.subjectNum[i];

		while (tempNode != z)
		{
			if (strncmp(tempNode->subjectNum, newNode.subjectNum, 7) < 0)
				tempNode = tempNode->left;
			else  if (strncmp(tempNode->subjectNum, newNode.subjectNum, 7) > 0)
				tempNode = tempNode->right;
		}
		tempNode = &newNode;

	}

}

void Tree::showTree(treeNode *temp)
{
	if (temp != z)
	{
		showTree(temp->left);
		readTree(temp);
		showTree(temp->right);
		
	}
}

void  Tree::readTree(treeNode *temp)
{
	int j;
		cout << "과목명     : ";
		for (j = 0; j < temp->numName; j++)
			cout << temp->name[j];
		cout << endl << "선이수과목 : ";
		for (j = 0; j <  temp->numPreName; j++)
			cout << temp->preSubject[j];
		cout << endl << "학수번호   : ";
		for (j = 0; j < 7; j++)
			cout << temp->subjectNum[j];
		cout << endl << (temp->isEssential ? "필수" : "선택");
		cout << endl << (temp->isDesign ? "설계" : "");
		cout << endl << ((temp->isMajor == 0) ? "전공" :
			((temp->isMajor == 1) ? "MSC" : ((temp->isMajor == 2) ? "기초소양" : "교양")));
		cout << endl << temp->credit << "학점\n" << endl;


}