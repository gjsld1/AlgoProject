#pragma once
#include "stdafax.h"



class String
{
public:
	String();
	~String();
	void showString();

	int searchBF(char *subjectNums, char *subName);   //string���� ����ã�� �ε��� ����, Brute-Force
	int searchKMP(char *subjectNums, char *subName);   //string���� ����ã�� �ε��� ����, KMP
	int searchBM(char *subjectNums, char *subName);   //string���� ����ã�� �ε��� ����, Boyer-Moore
	void S_deletePreSub(int *deletePreIndex, int &Pre_counter);//***************************************************�̰��̸��ٲ���ϴ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void deleteString(int index, int stringSize, char *subjectNums);
	void subtake(char *subjectNums);
	int stringRanking(int nodeSize);
	//-getter
	node* get_stringNode();
	int get_nodeSize();
	int get_credit();
	int get_design();
private:
	node * stringNode;     //string���� ������ ������ �迭
	char * subjectNums;    //string���� ������ Ž���� ����� ���ڿ�
	int nodeSize;          //stringNode�� ������
	int stringSize;        //subjectNums�� ������
	int credit_sum = 0;
	int design_sum = 0;

};
