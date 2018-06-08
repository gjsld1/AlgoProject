#pragma once
#include "stdafax.h"


class Array 
{
public:
	Array();
	~Array();
	void showArray();
	//void deleteArray();
	//int searchArray();  //들었던 과목 지우는거, 과목이름 찾는거 

private:
	node* arrayNode;
	int size;

};
