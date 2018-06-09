#pragma once
#include "stdafax.h"

String::String()
{
	string tempLine = "";
	int tempLen = 0;
	int stringIndex = 0;

	ifstream input1("subject.txt");

	getline(input1, tempLine);
	this->nodeSize = stoi(tempLine);
	stringNode = new node[nodeSize];

	stringSize = 7 * nodeSize + 1;
	subjectNums = new char[stringSize];

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

	}
	input1.close();
	//showString();


}
String::~String()
{
	delete[]stringNode;
	delete[]subjectNums;
 }

void String::showString()
{
	for (int i = 0; i < stringSize; i++)
		cout << subjectNums[i];
}
