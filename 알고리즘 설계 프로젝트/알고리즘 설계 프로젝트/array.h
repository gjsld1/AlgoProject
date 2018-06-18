#pragma once
#include "stdafax.h"


class Array 
{
public:
	Array();
	~Array();
	void showArray();
	void deleteArray(int index, int size);
	int searchArray(char *subName);
	void subtake();
	int arrayRanking(int size);
	void deletePreSub(int *deletePreIndex, int &Pre_counter);//***************************************************이거이름바꿨습니다!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//-getter
	node* get_arrayNode();
	int getCredit();
	int getDesign();
	int getSize();
	int size;
private:
	node* arrayNode;
	//int size;
	int Credit_sum = 0;
	int Design_sum = 0;

};
