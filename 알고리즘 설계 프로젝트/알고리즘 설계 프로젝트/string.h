#pragma once
#include "stdafax.h"



class String
{
public:
	String();
	~String();
	void showString();

	int searchBF(char *subjectNums, char *subName);   //string에서 과목찾아 인덱스 리턴, Brute-Force
	int searchKMP(char *subjectNums, char *subName);   //string에서 과목찾아 인덱스 리턴, KMP
	int searchBM(char *subjectNums, char *subName);   //string에서 과목찾아 인덱스 리턴, Boyer-Moore
	void S_deletePreSub(int *deletePreIndex, int &Pre_counter);//***************************************************이거이름바꿨습니다!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void deleteString(int index, int stringSize, char *subjectNums);
	void subtake(char *subjectNums);
	int stringRanking(int nodeSize);
	//-getter
	node* get_stringNode();
	int get_nodeSize();
	int get_credit();
	int get_design();
private:
	node * stringNode;     //string에서 과목을 저장할 배열
	char * subjectNums;    //string에서 과목을 탐색할 과목명 문자열
	int nodeSize;          //stringNode의 사이즈
	int stringSize;        //subjectNums의 사이즈
	int credit_sum = 0;
	int design_sum = 0;

};
