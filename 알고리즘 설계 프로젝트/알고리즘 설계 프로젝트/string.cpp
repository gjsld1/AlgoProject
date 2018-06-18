#pragma once
#include "stdafax.h"
int User_grade;//������ �г�
String::String()
{
	string tempLine = "";
	int tempLen = 0;
	int stringIndex = 0;

	ifstream input1("subject.txt");
	
	getline(input1, tempLine);
	this->nodeSize = stoi(tempLine);
	stringNode = new node[nodeSize];

	stringSize = 7 * nodeSize;
	subjectNums = new char[stringSize];//���ٷ� ������ data

	for (int i = 0; i < nodeSize; i++)
	{
		getline(input1, tempLine);
		tempLen = tempLine.length();
		stringNode[i].name = new char[tempLen];
		strncpy(stringNode[i].name, tempLine.c_str(), tempLen);
		stringNode[i].numName = tempLen;

		getline(input1, tempLine);
		if (tempLine == "")stringNode[i].numPreName = 0;
		else
		{
			tempLen = tempLine.length();
			stringNode[i].preSubject = new char[tempLen];
			strncpy(stringNode[i].preSubject, tempLine.c_str(), tempLen);
			stringNode[i].numPreName = tempLen;
		}

		getline(input1, tempLine);
		stringNode[i].subjectNum = new char[7];
		strncpy(stringNode[i].subjectNum, tempLine.c_str(), 7);

		for (int k = 0; k < 7; k++)
			subjectNums[stringIndex++] = stringNode[i].subjectNum[k];

		getline(input1, tempLine);
		stringNode[i].isEssential = stoi(tempLine);

		getline(input1, tempLine);
		stringNode[i].isDesign = stoi(tempLine);

		getline(input1, tempLine);
		stringNode[i].isMajor = stoi(tempLine);

		getline(input1, tempLine);
		stringNode[i].credit = stoi(tempLine);

		getline(input1, tempLine);
		stringNode[i].grade = stoi(tempLine);

	}
	
	input1.close();
	subtake(subjectNums);
	

	//************************************************************************���⼭����
	int *deletePreIndex;
	deletePreIndex = new int[this->nodeSize];
	int deletePreSize = 0;

	S_deletePreSub(deletePreIndex, deletePreSize);

	for (int i = deletePreSize - 1; i >= 0; i--)
	{
		deleteString(deletePreIndex[i], stringSize, subjectNums);
		stringSize -= 7;
		nodeSize -= 1;
	}
	//************************************************************************�������� �Ʒ����־��

	//showString();

}
String::~String()
{
	delete[]stringNode;
	delete[]subjectNums;
 }

void String::showString()
{
	for (int i = 0; i < stringSize; i++) {
		cout << subjectNums[i];
	}
	cout << endl;
}

int String::searchBF(char *subjectNums, char *subName) {
	int i, j;// m = strlen(subName), n = strlen(subjectNums);//strlen�� ����ϰ� �Ǹ� ���� �߻�
	int m = 7;
	int n = stringSize;
	for (i = 0; i <= n - m; i++) {
		for (j = 0; j < m; j++) {
			if (subjectNums[i+j] != subName[j]) {
				break;
			}
		}
		if (j == m) {
			return i;
		}
	}
	return -1;
}

int *SP;
void initSP(char *subName) {
	int i, j, m = strlen(subName);
	SP = new int[m];
	SP[0] = -1;
	for (i = 1, j = -1; i <= m - 1; i++) {
		while ((j >= 0) && (subName[j + 1] != subName[i])) { j = SP[j]; }
		if (subName[j + 1] == subName[i]) { j++; }
		SP[i] = j;
	}
}
int String::searchKMP(char *subjectNums, char *subName) {
	int i, j, m = strlen(subName), n = strlen(subjectNums);
	initSP(subName);
	for (i = 0, j = -1; i <= n - 1; i++) {
		while ((j >= 0) && (subName[j + 1] != subjectNums[i])) { j = SP[j]; }
		if (subName[j + 1] == subjectNums[i]) { j++; }
		if (j == m - 1) {
			j = SP[j];
			return i - m + 1;
		}
	}
	return -1;
}

int *skip;
const int alphabet_count = 26;
int *lp = new int[alphabet_count];
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}
int index(char index) {
	return index - '0';
}
void LastPos(char *subName) {
	for (int i = 0; i<alphabet_count; i++) lp[i] = -1;
	for (int i = 0; i<strlen(subName); i++) lp[index(subName[i])] = i;
}
void GoodSuffix(char *subName) {
	int i, k;
	int m = strlen(subName);
	char *r_p = new char[m];
	for (i = 0; i<m; i++) {
		r_p[m - i - 1] = subName[i];
	}
	initSP(r_p);
	for (i = -1; i <= m - 1; i++) skip[i] = m - 1 - SP[m - 1];
	for (k = 0; k <= m - 1; k++) {
		i = m - 1 - SP[k] - 1;
		if (skip[i]>k - SP[k]) skip[i] = k - SP[k];
	}
}
int String::searchBM(char *subName, char *subjectNums) {
	int i, j;
	int m = strlen(subName), n = strlen(subjectNums);
	skip = new int[m];
	LastPos(subName);
	GoodSuffix(subName);
	j = 0;
	while (j <= n - m) {
		for (i = m - 1; i >= 0 && subName[i] == subjectNums[j + i]; i--);
		if (i == -1) {
			return j;
			j = j + skip[-1];
		}
		else {
			j = j + max(skip[i], i - lp[index(subjectNums[j + i])]);
		}
	}
	return -1;
}
//************************************************************************�����Լ� �����߾��! �����ڵ�� �ּ����� �J���
void String::S_deletePreSub(int *deletePreIndex, int &Pre_counter){

	Pre_counter = 0;
	
	for (int i = 0; i < nodeSize; i++) {//�����ŭ Ȯ���Ѵ�
		if (stringNode[i].numPreName > 0) {//�� �� � ������ ���̼��� �����Ѵٰ� ���� ��,
			for (int j = 0; j < nodeSize; j++) {//�ٸ� ������ ���ϱ� ���� ������
				if (stringNode[j].numName == stringNode[i].numPreName) {//������ ���̼������� ���� ���ٸ�,
					//���ٸ�, �� � ������ ���̼� ������ �����ؾ� �ϴ� ������ ��Ͽ� ���� ���(���̼��� �ȵ���ٴ� �ǹ�)
					if (!strncmp(stringNode[j].name, stringNode[i].preSubject, stringNode[j].numName))
						deletePreIndex[Pre_counter++] = i*7;
				}
			}
		}
	}
	deletePreIndex[Pre_counter] = -1;
}//****************************************************************************************************************������� �Լ��ٲ���ϴ�.�׸��� ������� �Լ��� Ȯ�����ּ���!

void String::deleteString(int index, int stringSize, char *subjectNums) {
	for (int k = 0; k < 7; k++) {
		subjectNums[index + k] = subjectNums[stringSize - 7 + k];
	}
		stringNode[index/7] = stringNode[nodeSize - 1];
}
void String::subtake(char *subjectNums) {
	string sub;
	int subNum;
	ifstream take("takeSubject.txt");
	getline(take, sub);
	subNum = stoi(sub);
	getline(take, sub);
	User_grade = stoi(sub);
	int index = -1;
	char *subName = new char[7];   //string�� char*��
								   //takeSubject���� �м���ȣ �� ���� �ҷ�����
	for (int k = 0; k < subNum; k++) {//�񱳸� �ݺ��Ͽ� �ڸ��ϴ�.
		getline(take, sub);//sub�� line�� �����ɴϴ�.
		for (int i = 0; i < sub.length(); i++) {
			subName[i] = sub[i];
			//cout << subName[i];

		}
		index = searchBF(subjectNums, subName);   //BF or KMP or BM ��� ����
													//���⿡ �����ϴ� �� ����
		if (stringNode[index/7].isDesign == 1) {//��������̶��
			design_sum += stringNode[index/7].credit;
			credit_sum += stringNode[index/7].credit;
		}
		else {
			credit_sum += stringNode[index/7].credit;
		}
		deleteString(index, stringSize, subjectNums);
		stringSize -= 7;
		nodeSize -= 1;
	}
}
int String::stringRanking(int nodeSize) {
	double MAX = 0;
	int MAX_index = 0;
	double *score = new double[nodeSize];
	for (int i = 0; i < nodeSize; i++) {
		double rank = 0;
		//arrayNode[0].name;
		//arrayNode[0].preSubject;
		//arrayNode[0].numPreName;//���� ���ΰ� �ʿ�
		if (stringNode[i].numPreName > 1) {
			rank += 2.3;
		}
		//arrayNode[0].isEssential;
		if (stringNode[i].isEssential == 1) {//�ʼ� 1 ���� 0
			rank += 1.5;
		}
		//arrayNode[0].isDesign;
		if (stringNode[i].isDesign == 1) {//���� 1 �񼳰� 0
			rank += 1.2;
		}
		//arrayNode[0].isMajor;
		if (stringNode[i].isMajor == 0) {//���� 3 MSC 2 ���ʼҾ� 1 ���� 0
			rank += 2.7;
		}
		else if (stringNode[i].isMajor == 1) {
			rank += 1.7;
		}
		else if (stringNode[i].isMajor == 2) {
			rank += 0.7;
		}

		//arrayNode[0].credit;
		if (stringNode[i].credit == 3) {//������ ���� ���� �ο�
			rank += 3;
		}
		else if (stringNode[i].credit == 2) {
			rank += 2;
		}
		else if (stringNode[i].credit == 1) {
			rank += 1;
		}
		//arrayNode[0].grade;
		if (abs(User_grade - stringNode[i].grade) == 0) {//�г��� ������
			rank += 2.5;
		}
		else if (abs(User_grade - stringNode[i].grade) == 1) {//�г��� �ϳ�����
			rank += 1.7;
		}
		else if (abs(User_grade - stringNode[i].grade) == 2) {//�г��� ������
			rank += 1;
		}
		score[i] = rank;
	}
	for (int i = 0; i < nodeSize; i++) {
		if (MAX < score[i]) {
			MAX = score[i];
			MAX_index = i;
		}
	}//���� �˰����� MAX���� score ���̺��� �����Ͽ� ���� ������� ����ϸ� 1, 2, 3�������� �� �� �ִ�.
	return MAX_index;
}
int String::get_nodeSize() {
	return nodeSize;
}
node* String::get_stringNode() {
	return stringNode;
}
int String::get_credit() {
	return credit_sum;
}
int String::get_design() {
	return design_sum;
}