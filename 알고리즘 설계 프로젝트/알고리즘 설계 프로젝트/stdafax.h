#pragma once
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct node //������ ����
{
	char* name;         //����� 
	int numName;        //�������� 
	char* preSubject;   //���̼������
	int numPreName;     //���̼���������
	char* subjectNum;   //7�ڸ�
	int isEssential;     //�ʼ� �Ǵ� ����  
	int isDesign;        //����
	int isMajor;         //����(0), MSC(1), ���ʼҾ�(2), ����(3)
	int credit;          //����

};

#include "array.h"
#include "tree.h"
#include "string.h"
