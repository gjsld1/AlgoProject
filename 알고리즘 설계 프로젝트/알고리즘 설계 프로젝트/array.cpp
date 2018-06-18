#pragma once
#include "stdafax.h"

using namespace std;

int userGrade;//������ �г�

Array::Array()
{
	string tempLine = ""; 
	int tempLen = 0;
	
	ifstream input2("subject.txt");//��ü �̼� ������ �Է¹ޱ�
	
	getline(input2, tempLine);
	this->size = stoi(tempLine);
	arrayNode = new node[size];

	for (int i = 0; i < size; i++)
	{
		getline(input2, tempLine);
		tempLen = tempLine.length();
		arrayNode[i].name = new char[tempLen];
		strncpy(arrayNode[i].name, tempLine.c_str(), tempLen);
		arrayNode[i].numName = tempLen;

		getline(input2, tempLine);
		if (tempLine == "")arrayNode[i].numPreName = 0;
		else
		{
			tempLen = tempLine.length();
			arrayNode[i].preSubject = new char[tempLen];
			strncpy(arrayNode[i].preSubject, tempLine.c_str(), tempLen);
			arrayNode[i].numPreName = tempLen;
		}

		getline(input2, tempLine);
		arrayNode[i].subjectNum = new char[7];
		strncpy(arrayNode[i].subjectNum, tempLine.c_str(), 7);

		getline(input2, tempLine);
		arrayNode[i].isEssential = stoi(tempLine);

		getline(input2, tempLine);
		arrayNode[i].isDesign = stoi(tempLine);

		getline(input2, tempLine);
		arrayNode[i].isMajor = stoi(tempLine);

		getline(input2, tempLine);
		arrayNode[i].credit = stoi(tempLine);

		getline(input2, tempLine);
		arrayNode[i].grade = stoi(tempLine);

	}
	
	input2.close();
	
	subtake();

	//************************************************************************���⼭����
	int *deletePreIndex;
	deletePreIndex = new int[this->size];
	int deletePreSize = 0;

	deletePreSub(deletePreIndex, deletePreSize);
	
	
	for(int i = deletePreSize - 1; i >= 0; i--)
	{
		deleteArray(deletePreIndex[i], size);
		size--;
	}
	//************************************************************************�������� �Ʒ����־��
	//showArray();
}

Array::~Array()
{
	delete []arrayNode;
}

void Array::showArray()
{
	int j, i;
	for (i = 0; i < size; i++)
	{
		cout << (i+1) << endl;
		cout << "�����     : ";
		for (j = 0; j < arrayNode[i].numName; j++)
			cout << arrayNode[i].name[j];
		cout << endl << "���̼����� : ";
		for (j = 0; j < arrayNode[i].numPreName; j++)
			cout << arrayNode[i].preSubject[j];
		cout << endl << "�м���ȣ   : ";
		for (j = 0; j < 7; j++)
			cout << arrayNode[i].subjectNum[j];
		cout << endl<< (arrayNode[i].isEssential?"�ʼ�":"����");
		cout << endl << (arrayNode[i].isDesign ? "����" : "");
		cout<<endl<< ((arrayNode[i].isMajor==0) ?"����":
			((arrayNode[i].isMajor == 1) ? "MSC" : ((arrayNode[i].isMajor == 2) ? "���ʼҾ�" : "����")));
		cout << endl << arrayNode[i].credit << "����\n";
		cout << arrayNode[i].grade << "�г�\n" << endl;
		

	}
}
void Array::deleteArray(int index, int size) {
	arrayNode[index] = arrayNode[size-1];
}

//************************************************************************�����Լ� �����߾��! �����ڵ�� �ּ����� �J���
void Array::deletePreSub(int *deletePreIndex, int &Pre_counter) {
	
	Pre_counter = 0;

	for (int i = 0; i < size; i++) {//�����ŭ Ȯ���Ѵ�
		if (arrayNode[i].numPreName > 0) {//�� �� � ������ ���̼��� �����Ѵٰ� ���� ��,
			for (int j = 0; j < size; j++) {//�ٸ� ������ ���ϱ� ���� ������
				if (arrayNode[j].numName == arrayNode[i].numPreName) {//������ ���̼������� ���� ���ٸ�,
					//���ٸ�, �� � ������ ���̼� ������ �����ؾ� �ϴ� ������ ��Ͽ� ���� ���(���̼��� �ȵ���ٴ� �ǹ�)
					if(!strncmp(arrayNode[j].name, arrayNode[i].preSubject, arrayNode[j].numName))
						deletePreIndex[Pre_counter++] = i;
				}
			}
		}
	}
	deletePreIndex[Pre_counter] = -1;
}//****************************************************************************************************************������� �Լ��ٲ���ϴ�.�׸��� ������� �Լ��� Ȯ�����ּ���!

int Array::searchArray(char *subName) {
	//���� ���� �м���ȣ array���� ã��
	int tmp_index = 0;
	int counter = 0;
	for (int x = 0; x < size; x++) {//����� ��Ī
		for (int y = 0; y < 7; y++) {
			if (arrayNode[x].subjectNum[y] == subName[y]) {
				counter++;
			}
		}
		if (counter == 7) {
			tmp_index = x;
		}
		counter = 0;
	}
	return tmp_index;
}//�̹� �̼��� �����̹Ƿ� ���� ��Ͽ� �ݵ�� �����ϹǷ� ��ã�� ��� ���� x
void Array::subtake() {
	string sub;
	int subNum;
	int index = -1;
	ifstream take("takeSubject.txt");//�̹� ���� ������ �о����
	getline(take, sub);
	subNum = stoi(sub);//�̼��� ���� ���� �Է¹ޱ�
	getline(take, sub);
	userGrade = stoi(sub);
	char *subName = new char[7];   //string�� char*��
								   //takeSubject���� �м���ȣ �� ���� �ҷ�����
	for (int k = 0; k < subNum; k++) {
		getline(take, sub);
		for (int i = 0; i < sub.length(); i++) {
			subName[i] = sub[i];
		}
		index = searchArray(subName);//i �ε��� ��ȯ.
		//���⿡ ����
		if (arrayNode[index].isDesign == 1) {//��������̶��
			Design_sum += arrayNode[index].credit;
			Credit_sum += arrayNode[index].credit;
		}
		else {
			Credit_sum += arrayNode[index].credit;
		}
		deleteArray(index, size);
		size--;
	}
}
int Array::arrayRanking(int size) {
	double MAX = 0;
	int MAX_index = 0;
	double *score = new double[size];
	for (int i = 0; i < size; i++) {
		double rank = 0;
		//arrayNode[0].name;
		//arrayNode[0].preSubject;
		//arrayNode[0].numPreName;//���� ���ΰ� �ʿ�
		if (arrayNode[i].numPreName > 1) {
			rank += 2.3;
		}
		//arrayNode[0].isEssential;
		if (arrayNode[i].isEssential == 1) {//�ʼ� 1 ���� 0
			rank += 1.5;
		}
		//arrayNode[0].isDesign;
		if (arrayNode[i].isDesign == 1) {//���� 1 �񼳰� 0
			rank += 1.2;
		}
		//arrayNode[0].isMajor;
		if (arrayNode[i].isMajor == 0) {//���� 3 MSC 2 ���ʼҾ� 1 ���� 0
			rank += 2.7;
		}
		else if (arrayNode[i].isMajor == 1) {
			rank += 1.7;
		}
		else if (arrayNode[i].isMajor == 2) {
			rank += 0.7;
		}

		//arrayNode[0].credit;
		if (arrayNode[i].credit == 3) {//������ ���� ���� �ο�
			rank += 3;
		}
		else if (arrayNode[i].credit == 2) {
			rank += 2;
		}
		else if (arrayNode[i].credit == 1) {
			rank += 1;
		}
		//arrayNode[0].grade;
		
		if (abs(userGrade - arrayNode[i].grade) == 0) {//�г��� ������
			rank += 2.5;
		}
		else if (abs(userGrade - arrayNode[i].grade) == 1) {//�г��� �ϳ�����
			rank += 1.7;
		}
		else if (abs(userGrade - arrayNode[i].grade) == 2) {//�г��� ������
			rank += 1;
		}
		
		score[i] = rank;
		
	}
	for (int i = 0; i < size; i++) {
		if (MAX < score[i]) {
			MAX = score[i];
			MAX_index = i;
		}
	}//���� �˰����� MAX���� score ���̺��� �����Ͽ� ���� ������� ����ϸ� 1, 2, 3�������� �� �� �ִ�.
	return MAX_index;
}
int Array::getSize() {
	return size;
}
node* Array::get_arrayNode() {
	return arrayNode;
}
int Array::getCredit() {
	return Credit_sum;
}
int Array::getDesign() {
	return Design_sum;
}
