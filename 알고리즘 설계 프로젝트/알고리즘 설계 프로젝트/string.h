#pragma once
#include "stdafax.h"



class String
{
public:
	String();
	~String();
	void showString();


private:
	node * stringNode;     //string���� ������ ������ �迭
	char * subjectNums;    //string���� ������ Ž���� ����� ���ڿ�
	int nodeSize;          //stringNode�� ������
	int stringSize;        //subjectNums�� ������


};
