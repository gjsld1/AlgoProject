#pragma once
#include "stdafax.h"
#include "array.h"
#include <windows.h>

int main()
{
	system("mode con cols=60 lines=60");
	string user;   //T����� �̸�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "�������б� ��ǻ�Ͱ��� �ð�ǥ" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "USER �̸��� �Է��ϼ��� : ";
	cin >> user;


	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	String subjectStr;
	int str_index;
	int Str_creditSum = subjectStr.get_credit();
	int Str_designSum = subjectStr.get_design();
	string Str_result;
	int temp = subjectStr.get_nodeSize();
	str_index = subjectStr.stringRanking(subjectStr.get_nodeSize());//�ε����� ��ȯ
	for (int i = 0; i < subjectStr.get_stringNode()[str_index].numName; i++) {
		Str_result += subjectStr.get_stringNode()[str_index].name[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "<�ڷᱸ�� String ���>" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << user << "���� ���� ���� ��õ ���� : ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << Str_result << endl;
	cout << user << "�� ������ �� ���� : " << Str_creditSum << endl;
	cout << user << "�� ������ ���� ���� : " << Str_designSum << endl;
	cout << endl << endl;



	Array subjectArr;
	int arr_index;
	int Arr_creditSum = subjectArr.getCredit();
	int Arr_designSum = subjectArr.getDesign();
	string Arr_result;
	arr_index = subjectArr.arrayRanking(subjectArr.getSize());//�ε����� ��ȯ
	for (int i = 0; i < subjectArr.get_arrayNode()[arr_index].numName; i++) {
		Arr_result += subjectArr.get_arrayNode()[arr_index].name[i];
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "<�ڷᱸ�� Array ���>" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << user << "���� ���� ���� ��õ ���� : ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << Arr_result << endl;
	cout << user << "�� ������ �� ���� : " << Arr_creditSum << endl;
	cout << user << "�� ������ ���� ���� : " << Arr_designSum << endl;
	cout << endl << endl;




	Tree subjectTree;
	string Tree_result = subjectTree.getName_t();
	int Tree_creditSum;
	Tree_creditSum = subjectTree.getCredit_t();
	int Tree_designSum;
	Tree_designSum = subjectTree.getDesign_t();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "<�ڷᱸ�� Tree ���>" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << user << "���� ���� ���� ��õ ���� : ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << Tree_result << endl;
	cout << user << "�� ������ �� ���� : " << Tree_creditSum << endl;
	cout << user << "�� ������ ���� ���� : " << Tree_designSum << endl;

}