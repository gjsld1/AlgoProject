#pragma once
#include "stdafax.h"



class String
{
public:
	String();
	~String();
	void showString();


private:
	node * stringNode;     //string에서 과목을 저장할 배열
	char * subjectNums;    //string에서 과목을 탐색할 과목명 문자열
	int nodeSize;          //stringNode의 사이즈
	int stringSize;        //subjectNums의 사이즈


};
