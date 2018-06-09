//
//  array.cpp
//  AlgoProj
//
//  Created by 신예지 on 2018. 6. 8..
//  Copyright © 2018년 신예지. All rights reserved.
//

#pragma once
#include "stdafx.h"

using namespace std;


Array::Array()
{
    string tempLine = "";
    int tempLen = 0;
    
    ifstream input2("subject.txt");
    
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
        
    }
    
    input2.close();
    
    //showArray();
}

Array::~Array()
{
    delete[]arrayNode;
}

void Array::showArray()
{
    int j, i;
    for (i = 0; i < size; i++)
    {
        cout << (i + 1) << endl;
        cout << "과목명     : ";
        for (j = 0; j < arrayNode[i].numName; j++)
            cout << arrayNode[i].name[j];
        cout << endl << "선이수과목 : ";
        for (j = 0; j < arrayNode[i].numPreName; j++)
            cout << arrayNode[i].preSubject[j];
        cout << endl << "학수번호   : ";
        for (j = 0; j < 7; j++)
            cout << arrayNode[i].subjectNum[j];
        cout << endl << (arrayNode[i].isEssential ? "필수" : "선택");
        cout << endl << (arrayNode[i].isDesign ? "설계" : "");
        cout << endl << ((arrayNode[i].isMajor == 0) ? "전공" :
                         ((arrayNode[i].isMajor == 1) ? "MSC" : ((arrayNode[i].isMajor == 2) ? "기초소양" : "교양")));
        cout << endl << arrayNode[i].credit << "학점\n" << endl;
    }
}

int Array::searchArray(char *subName) {
    for (int i = 0; i < size; i++) {
        if (arrayNode[i].subjectNum == subName) return i;
    }
}
