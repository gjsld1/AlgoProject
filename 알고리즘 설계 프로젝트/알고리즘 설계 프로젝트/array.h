#pragma once
#include "stdafax.h"


class Array 
{
public:
	Array();
	~Array();
	void showArray();
	//void deleteArray();
	//int searchArray();  //����� ���� ����°�, �����̸� ã�°� 

private:
	node* arrayNode;
	int size;

};
