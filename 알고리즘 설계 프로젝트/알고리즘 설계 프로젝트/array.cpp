#pragma once
#include "stdafax.h"

using namespace std;

int userGrade;//유저의 학년

Array::Array()
{
	string tempLine = ""; 
	int tempLen = 0;
	
	ifstream input2("subject.txt");//전체 이수 과목을 입력받기
	
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

	//************************************************************************여기서부터
	int *deletePreIndex;
	deletePreIndex = new int[this->size];
	int deletePreSize = 0;

	deletePreSub(deletePreIndex, deletePreSize);
	
	
	for(int i = deletePreSize - 1; i >= 0; i--)
	{
		deleteArray(deletePreIndex[i], size);
		size--;
	}
	//************************************************************************여끼까지 아래더있어요
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
		cout << "과목명     : ";
		for (j = 0; j < arrayNode[i].numName; j++)
			cout << arrayNode[i].name[j];
		cout << endl << "선이수과목 : ";
		for (j = 0; j < arrayNode[i].numPreName; j++)
			cout << arrayNode[i].preSubject[j];
		cout << endl << "학수번호   : ";
		for (j = 0; j < 7; j++)
			cout << arrayNode[i].subjectNum[j];
		cout << endl<< (arrayNode[i].isEssential?"필수":"선택");
		cout << endl << (arrayNode[i].isDesign ? "설계" : "");
		cout<<endl<< ((arrayNode[i].isMajor==0) ?"전공":
			((arrayNode[i].isMajor == 1) ? "MSC" : ((arrayNode[i].isMajor == 2) ? "기초소양" : "교양")));
		cout << endl << arrayNode[i].credit << "학점\n";
		cout << arrayNode[i].grade << "학년\n" << endl;
		

	}
}
void Array::deleteArray(int index, int size) {
	arrayNode[index] = arrayNode[size-1];
}

//************************************************************************여기함수 수정했어요! 이전코드는 주석으로 놧어요
void Array::deletePreSub(int *deletePreIndex, int &Pre_counter) {
	
	Pre_counter = 0;

	for (int i = 0; i < size; i++) {//사이즈만큼 확인한다
		if (arrayNode[i].numPreName > 0) {//이 때 어떤 과목이 선이수가 존재한다고 했을 때,
			for (int j = 0; j < size; j++) {//다른 과목들과 비교하기 위해 돌린다
				if (arrayNode[j].numName == arrayNode[i].numPreName) {//과목명과 선이수과목의 수가 같다면,
					//같다면, 즉 어떤 과목의 선이수 과목이 수강해야 하는 과목의 목록에 있을 경우(선이수를 안들었다는 의미)
					if(!strncmp(arrayNode[j].name, arrayNode[i].preSubject, arrayNode[j].numName))
						deletePreIndex[Pre_counter++] = i;
				}
			}
		}
	}
	deletePreIndex[Pre_counter] = -1;
}//****************************************************************************************************************여기까지 함수바꿨습니다.그리고 헤더파일 함수명도 확인해주세요!

int Array::searchArray(char *subName) {
	//들은 과목 학수번호 array에서 찾기
	int tmp_index = 0;
	int counter = 0;
	for (int x = 0; x < size; x++) {//목록을 서칭
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
}//이미 이수한 과목이므로 과목 목록에 반드시 존재하므로 못찾을 경우 존재 x
void Array::subtake() {
	string sub;
	int subNum;
	int index = -1;
	ifstream take("takeSubject.txt");//이미 들은 과목을 읽어오기
	getline(take, sub);
	subNum = stoi(sub);//이수한 과목 수를 입력받기
	getline(take, sub);
	userGrade = stoi(sub);
	char *subName = new char[7];   //string을 char*로
								   //takeSubject에서 학수번호 한 개씩 불러오기
	for (int k = 0; k < subNum; k++) {
		getline(take, sub);
		for (int i = 0; i < sub.length(); i++) {
			subName[i] = sub[i];
		}
		index = searchArray(subName);//i 인덱스 반환.
		//여기에 구현
		if (arrayNode[index].isDesign == 1) {//설계과목이라면
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
		//arrayNode[0].numPreName;//존재 여부가 필요
		if (arrayNode[i].numPreName > 1) {
			rank += 2.3;
		}
		//arrayNode[0].isEssential;
		if (arrayNode[i].isEssential == 1) {//필수 1 선택 0
			rank += 1.5;
		}
		//arrayNode[0].isDesign;
		if (arrayNode[i].isDesign == 1) {//설계 1 비설계 0
			rank += 1.2;
		}
		//arrayNode[0].isMajor;
		if (arrayNode[i].isMajor == 0) {//전공 3 MSC 2 기초소양 1 교양 0
			rank += 2.7;
		}
		else if (arrayNode[i].isMajor == 1) {
			rank += 1.7;
		}
		else if (arrayNode[i].isMajor == 2) {
			rank += 0.7;
		}

		//arrayNode[0].credit;
		if (arrayNode[i].credit == 3) {//학점에 따라 가점 부여
			rank += 3;
		}
		else if (arrayNode[i].credit == 2) {
			rank += 2;
		}
		else if (arrayNode[i].credit == 1) {
			rank += 1;
		}
		//arrayNode[0].grade;
		
		if (abs(userGrade - arrayNode[i].grade) == 0) {//학년이 같으면
			rank += 2.5;
		}
		else if (abs(userGrade - arrayNode[i].grade) == 1) {//학년이 하나차이
			rank += 1.7;
		}
		else if (abs(userGrade - arrayNode[i].grade) == 2) {//학년이 둘차이
			rank += 1;
		}
		
		score[i] = rank;
		
	}
	for (int i = 0; i < size; i++) {
		if (MAX < score[i]) {
			MAX = score[i];
			MAX_index = i;
		}
	}//정렬 알고리즘을 MAX값의 score 테이블을 정렬하여 높은 순서대로 출력하면 1, 2, 3순위까지 알 수 있다.
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
