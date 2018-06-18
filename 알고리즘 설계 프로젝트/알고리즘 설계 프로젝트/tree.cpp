#pragma once
#include "stdafax.h"

#define MAX 100
int User_Grade;
char* tmp;
char* deleteSN;
char deleteSub[MAX][7];
int tmp_num;
int g = 0;
int index = 0;
int S_index = 0;
int p = 1;
int subNum2 = 0;
int cnt = 0;
string C="";
string D="";
treeNode::treeNode(char *name, int numName, char *preSubject, int numPreName,
	char* subjectNum, int isEssential, int isDesign, int isMajor, int credit, int grade)
{
	this->numName = numName;
	this->numPreName = numPreName;
	this->isEssential = isEssential;
	this->isDesign = isDesign;
	this->isMajor = isMajor;
	this->credit = credit;
	this->grade = grade;

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

Tree::Tree()
{
	z = &tailNode;
	z->left = z;
	z->right = z;
	headNode.right = z;


	string tempLine = "";
	
	ifstream input3("subject.txt");

	getline(input3, tempLine);
	this->size = stoi(tempLine);
	

	for (int i = 0; i < size; i++)
	{
		char *nameTemp, *preNameTemp, *numTemp;
		int nameNumTemp, preNameNumTemp;
		int essential, design, major, credit, grade;

		getline(input3, tempLine);
		nameNumTemp = tempLine.length();

		nameTemp = new char[nameNumTemp];
		strncpy(nameTemp, tempLine.c_str(), nameNumTemp);


		getline(input3, tempLine);
		if (tempLine == "")
		{
			preNameNumTemp = 0; preNameTemp = 0;
		}
		else
		{
			preNameNumTemp = tempLine.length();
			preNameTemp = new char[preNameNumTemp];
			strncpy(preNameTemp, tempLine.c_str(), preNameNumTemp);
		}

		getline(input3, tempLine);
		numTemp = new char[7];
		strncpy(numTemp, tempLine.c_str(), 7);

		getline(input3, tempLine);
		essential = stoi(tempLine);

		getline(input3, tempLine);
		design = stoi(tempLine);

		getline(input3, tempLine);
		major = stoi(tempLine);

		getline(input3, tempLine);
		credit = stoi(tempLine);

		getline(input3, tempLine);
		grade = stoi(tempLine);


		treeNode *newNode;
		newNode = new treeNode(nameTemp, nameNumTemp, preNameTemp, preNameNumTemp, numTemp,
			essential, design, major, credit, grade);

		newNode->right = z;
		newNode->left = z;
		newNode -> parent = z;
		
		treeInsert(newNode);
	}
	input3.close();
	subtake();
	g = 1;
	findTree(headNode.right);
	///////////////////////////////////////////
	for (int j = 0; j < index; j++) {
		searchTree(headNode.right, deleteSub[j]);
		size--;
	}
	int return_index = 0;
	double *treeScore = new double[size];
	string *name_table = new string[size];
	Ranking_find(headNode.right, treeScore, name_table);
	return_index = treeRanking(size, treeScore, name_table);
	return_name = name_table[return_index];
	//showTree(headNode.right);
}

Tree::~Tree()
{
}

void Tree::treeInsert(treeNode *newNode)
{
	treeInsertSub(newNode, headNode.right);
}
treeNode* Tree::treeInsertSub(treeNode *newNode, treeNode *&rootNode)
{
	if (rootNode == z)
	{
		rootNode = newNode;
	}
	else
	{
		if (strncmp(rootNode->subjectNum, newNode->subjectNum, 7) > 0) {
			treeNode *lchild = treeInsertSub(newNode, rootNode->left);
			rootNode->left = lchild;
			lchild->parent = rootNode;
		}
		else  if (strncmp(rootNode->subjectNum, newNode->subjectNum, 7) < 0) {//학수번호를 비교하여 차순으로 insert
			treeNode *rchild = treeInsertSub(newNode, rootNode->right);
			rootNode->right = rchild;
			rchild->parent = rootNode;
		}
	}
	return rootNode;
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

void Tree::findTree(treeNode *temp)
{
	if (temp != z)
	{
		findTree(temp->left);
		
		if (temp->numPreName > 1) {//선이수 교과목을 가지고 있다
			tmp = temp->preSubject;//존재하면 지워야하기 때문에 해당과목의 선이수 명을 일단 가져온 후 비교해야 한다.
			tmp_num = temp->numPreName;
			deleteSN = temp->subjectNum;
			findTree2(headNode.right);
		}
		findTree(temp->right);
	}
}
void Tree::findTree2(treeNode *temp)
{
	if (temp != z)
	{
		findTree2(temp->left);
		if (temp->numName == tmp_num) {//선이수의 과목명과 어떤 과목의 이름의 길이가 같을 때//이름과 과목명을 비교해서 같은지 확인
			for (int r = 0; r < tmp_num; r++) {
				C += temp->name[r];
				D += tmp[r];
			}
			if (C.compare(D) == 0) {
				for (int t = 0; t < 7; t++) {
					deleteSub[index][t] = deleteSN[t];
				}
				index++;
			}
			C = "";
			D = "";
		}
		/////////////////////////////
		findTree2(temp->right);
	}
}
void  Tree::readTree(treeNode *temp)
{
	int j;
	cout << p++ << endl;
		cout << "과목명     : ";
		for (j = 0; j < temp->numName; j++)
			cout << temp->name[j];
		cout << endl << "선이수과목 : ";
		for (j = 0; j <  temp->numPreName; j++)
			cout << temp->preSubject[j];
		cout << endl << "학수번호   : ";
		for (j = 0; j < 7; j++)
			cout << temp->subjectNum[j];
		cout <<endl << (temp->isEssential ? "필수" : "선택");
		cout << endl << (temp->isDesign ? "설계" : "");
		cout << endl << ((temp->isMajor == 0) ? "전공" :
			((temp->isMajor == 1) ? "MSC" : ((temp->isMajor == 2) ? "기초소양" : "교양")));
		cout << endl << temp->credit << "학점\n";
		cout << temp->grade << "학년\n" << endl;


}

void Tree::searchTree(treeNode *&src, char *subName) {
	
	treeNode* x = src;
	string A;
	treeNode *removal = new treeNode;
	if (x == z) {
		return;
	}
	else if (strncmp(subName, x->subjectNum, 7) > 0) {
		searchTree(x->right, subName);
		return;
	}
	else if (strncmp(subName, x->subjectNum, 7) < 0) {
		searchTree(x->left, subName);
		return;
	}
	else {
		//학점 변수들 추가 위치
		if (cnt != subNum2) {
			if (x->isDesign == 1) {
				Credit_sum_t += x->credit;
				Design_sum_t += x->credit;
			}
			else {
				Credit_sum_t += x->credit;
			}
		}

		if (x->left == z && x->right == z) {//둘 다 자식이 없을 때
			if (x->parent->left == x) {
				x->parent->left = z;
			}
			else {
				x->parent->right = z;
			}
			delete x;
		}
		else if (x->left == z) {//오른쪽 자식
			if(headNode.right == x){
				headNode.right = x->right;
			}
			else {
				if (x->parent->left == x) {
					x->right->parent = x->parent;
					x->parent->left = x->right;
				}
				else {
					x->right->parent = x->parent;
					x->parent->right = x->right;
				}
			}
			delete x;
		}
		else if (x->right == z) {//왼쪽 자식
			if (headNode.right == x) {
				headNode.right = x->left;
			}
			else {
				if (x->parent->left == x) {
					x->left->parent = x->parent;
					x->parent->left = x->left;
				}
				else {
					x->left->parent = x->parent;
					x->parent->right = x->left;
				}
			}
			delete x;
		}
		else {//양쪽자식
			removal = x->right;
			while (removal->left != z) {
				removal = removal->left;
			}
			if (headNode.right == x) {
				if (removal->parent == x) {
					headNode.right = removal;
					removal->left = x->left;
					x->left->parent = removal;
					delete x;
				}
				else {
					if (removal->right == z) {
						removal->parent->left = z;
						removal->left = x->left;
						x->left->parent = removal;
						removal->right = x->right;
						x->right->parent = removal;
						headNode.right = removal;
						delete x;
					}
					else {
						removal->right->parent = removal->parent;
						removal->parent->left = removal->right;
						removal->left = x->left;
						x->left->parent = removal;
						removal->right = x->right;
						x->right->parent = removal;
						headNode.right = removal;
						delete x;
					}
				}
			}
			else {
				if (removal->parent == x) {
					removal->parent = x->parent;
					removal->left = x->left;
					x->left->parent = removal;
					if (x->parent->left == x) {
						x->parent->left = removal;
					}
					else {
						x->parent->right = removal;
					}
					delete x;
				}
				else {
					if (removal->right == z) {
						removal->parent->left = z;
						removal->left = x->left;
						x->left->parent = removal;
						removal->right = x->right;
						x->right->parent = removal;
						removal->parent = x->parent;
						if (x->parent->left == x) {
							x->parent->left = removal;
						}
						else {
							x->parent->right = removal;
						}
					}
					else {
						removal->right->parent = removal->parent;
						removal->parent->left = removal->right;
						removal->left = x->left;
						x->left->parent = removal;
						removal->right = x->right;
						x->right->parent = removal;
						removal->parent = x->parent;
						if (x->parent->left == x) {
							x->parent->left = removal;
						}
						else {
							x->parent->right = removal;
						}
					}
				}
			}
			///////////////////////////////////////
		}
		return;
	}
}

///////////////////////////////////
///////////////////////////////////
void Tree::subtake() {
	string sub;
	int subNum;
	ifstream take("takeSubject.txt");
	getline(take, sub);
	subNum = stoi(sub);
	subNum2 = subNum;
	getline(take, sub);
	User_Grade = stoi(sub);
	char *subName = new char[7];   //string을 char*로
								   //takeSubject에서 학수번호 한 개씩 불러오기
	for (int k = 0; k < subNum; k++) {
		getline(take, sub);
		for (int i = 0; i < sub.length(); i++) subName[i] = sub[i];
		searchTree(headNode.right, subName);//search에 delete기능 추가 함
		cnt++;
		size--;
		//여기에 삭제하는 것 구현
	}
}
void Tree::Ranking_find(treeNode* temp, double treeScore[], string name_table[]) {
	double rank = 0;
	string A;
	if (temp != z)
	{
		Ranking_find(temp->left, treeScore, name_table);
		////////////////////
		for (int i = 0; i < temp->numName; i++) {
			A += temp->name[i];
		}
		if (temp->numPreName > 1) {
			rank += 2.3;
		}
		if (temp->isEssential == 1) {//필수 1 선택 0
			rank += 1.5;
		}
		if (temp->isDesign == 1) {//설계 1 비설계 0
			rank += 1.2;
		}
		if (temp->isMajor == 0) {//전공 3 MSC 2 기초소양 1 교양 0
			rank += 2.7;
		}
		else if (temp->isMajor == 1) {
			rank += 1.7;
		}
		else if (temp->isMajor == 2) {
			rank += 0.7;
		}
		if (temp->credit == 3) {//학점에 따라 가점 부여
			rank += 3;
		}
		else if (temp->credit == 2) {
			rank += 2;
		}
		else if (temp->credit == 1) {
			rank += 1;
		}
		if (abs(User_Grade - temp->grade) == 0) {//학년이 같으면
			rank += 2.5;
		}
		else if (abs(User_Grade - temp->grade) == 1) {//학년이 하나차이
			rank += 1.7;
		}
		else if (abs(User_Grade - temp->grade) == 2) {//학년이 둘차이
			rank += 1;
		}
		treeScore[S_index] = rank;
		name_table[S_index] = A;
		S_index++;
		////////////////////
		Ranking_find(temp->right, treeScore, name_table);
	}
}
int Tree::treeRanking(int size, double treeScore[], string name_table[]) {
	double max = 0;
	int max_index = 0;
	for (int i = 0; i < size; i++) {
		if (max < treeScore[i]) {
			max = treeScore[i];
			max_index = i;
		}
	}
	return max_index;
}
int Tree::getSize_t() {
	return size;
}
int Tree::getCredit_t() {
	return Credit_sum_t;
}
int Tree::getDesign_t() {
	return Design_sum_t;
}
string Tree::getName_t() {
	return return_name;
}