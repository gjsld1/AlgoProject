#pragma once
#include "stdafax.h"
int User_grade;//유저의 학년
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
	subjectNums = new char[stringSize];//한줄로 나열한 data

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
	

	//************************************************************************여기서부터
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
	//************************************************************************여끼까지 아래더있어요

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
	int i, j;// m = strlen(subName), n = strlen(subjectNums);//strlen을 사용하게 되면 오류 발생
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
//************************************************************************여기함수 수정했어요! 이전코드는 주석으로 놧어요
void String::S_deletePreSub(int *deletePreIndex, int &Pre_counter){

	Pre_counter = 0;
	
	for (int i = 0; i < nodeSize; i++) {//사이즈만큼 확인한다
		if (stringNode[i].numPreName > 0) {//이 때 어떤 과목이 선이수가 존재한다고 했을 때,
			for (int j = 0; j < nodeSize; j++) {//다른 과목들과 비교하기 위해 돌린다
				if (stringNode[j].numName == stringNode[i].numPreName) {//과목명과 선이수과목의 수가 같다면,
					//같다면, 즉 어떤 과목의 선이수 과목이 수강해야 하는 과목의 목록에 있을 경우(선이수를 안들었다는 의미)
					if (!strncmp(stringNode[j].name, stringNode[i].preSubject, stringNode[j].numName))
						deletePreIndex[Pre_counter++] = i*7;
				}
			}
		}
	}
	deletePreIndex[Pre_counter] = -1;
}//****************************************************************************************************************여기까지 함수바꿨습니다.그리고 헤더파일 함수명도 확인해주세요!

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
	char *subName = new char[7];   //string을 char*로
								   //takeSubject에서 학수번호 한 개씩 불러오기
	for (int k = 0; k < subNum; k++) {//비교를 반복하여 자릅니다.
		getline(take, sub);//sub의 line을 가져옵니다.
		for (int i = 0; i < sub.length(); i++) {
			subName[i] = sub[i];
			//cout << subName[i];

		}
		index = searchBF(subjectNums, subName);   //BF or KMP or BM 사용 가능
													//여기에 삭제하는 것 구현
		if (stringNode[index/7].isDesign == 1) {//설계과목이라면
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
		//arrayNode[0].numPreName;//존재 여부가 필요
		if (stringNode[i].numPreName > 1) {
			rank += 2.3;
		}
		//arrayNode[0].isEssential;
		if (stringNode[i].isEssential == 1) {//필수 1 선택 0
			rank += 1.5;
		}
		//arrayNode[0].isDesign;
		if (stringNode[i].isDesign == 1) {//설계 1 비설계 0
			rank += 1.2;
		}
		//arrayNode[0].isMajor;
		if (stringNode[i].isMajor == 0) {//전공 3 MSC 2 기초소양 1 교양 0
			rank += 2.7;
		}
		else if (stringNode[i].isMajor == 1) {
			rank += 1.7;
		}
		else if (stringNode[i].isMajor == 2) {
			rank += 0.7;
		}

		//arrayNode[0].credit;
		if (stringNode[i].credit == 3) {//학점에 따라 가점 부여
			rank += 3;
		}
		else if (stringNode[i].credit == 2) {
			rank += 2;
		}
		else if (stringNode[i].credit == 1) {
			rank += 1;
		}
		//arrayNode[0].grade;
		if (abs(User_grade - stringNode[i].grade) == 0) {//학년이 같으면
			rank += 2.5;
		}
		else if (abs(User_grade - stringNode[i].grade) == 1) {//학년이 하나차이
			rank += 1.7;
		}
		else if (abs(User_grade - stringNode[i].grade) == 2) {//학년이 둘차이
			rank += 1;
		}
		score[i] = rank;
	}
	for (int i = 0; i < nodeSize; i++) {
		if (MAX < score[i]) {
			MAX = score[i];
			MAX_index = i;
		}
	}//정렬 알고리즘을 MAX값의 score 테이블을 정렬하여 높은 순서대로 출력하면 1, 2, 3순위까지 알 수 있다.
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