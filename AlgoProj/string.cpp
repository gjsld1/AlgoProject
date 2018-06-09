//
//  string.cpp
//  AlgoProj
//
//  Created by 신예지 on 2018. 6. 8..
//  Copyright © 2018년 신예지. All rights reserved.
//

#pragma once
#include "stdafx.h"

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

int String::searchBF(char *subjectNums, char *subName) {
    int i, j, m = strlen(subName), n = strlen(subjectNums);
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (subjectNums[i + j] != subName[j]) { break; }
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

void String::subtake(char *subjectNums) {
    string sub;
    int subNum;
    ifstream take("takeSubject.txt");
    getline(take, sub);
    subNum = stoi(sub);
    
    char *subName = new char[7];   //string을 char*로
    //takeSubject에서 학수번호 한 개씩 불러오기
    for (int k = 0; k < subNum; k++) {
        getline(take, sub);
        for (int i = 0; i < sub.length(); i++) subName[i] = sub[i];
        searchBF(subName,subjectNums);   //BF or KMP or BM 사용 가능
        //여기에 삭제하는 것 구현
    }
}
