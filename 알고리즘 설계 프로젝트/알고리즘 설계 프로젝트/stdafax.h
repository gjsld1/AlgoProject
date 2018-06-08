#pragma once
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct node //과목의 정보
{
	char* name;         //과목명 
	int numName;        //과목명길이 
	char* preSubject;   //선이수과목명
	int numPreName;     //선이수과목명길이
	char* subjectNum;   //7자리
	int isEssential;     //필수 또는 선택  
	int isDesign;        //설계
	int isMajor;         //전공(0), MSC(1), 기초소양(2), 교양(3)
	int credit;          //학점

};

#include "array.h"
#include "tree.h"
#include "string.h"
