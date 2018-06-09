//
//  string.hpp
//  AlgoProj
//
//  Created by 신예지 on 2018. 6. 8..
//  Copyright © 2018년 신예지. All rights reserved.
//

#pragma once
#include "stdafx.h"

class String
{
public:
    String();
    ~String();
    void showString();
    
    int searchBF(char *subjectNums, char *subName);   //string에서 과목찾아 인덱스 리턴, Brute-Force
    int searchKMP(char *subjectNums, char *subName);   //string에서 과목찾아 인덱스 리턴, KMP
    int searchBM(char *subjectNums, char *subName);   //string에서 과목찾아 인덱스 리턴, Boyer-Moore
    //찾기 실패하면 모두 -1 반환
    void subtake(char *subjectNums);
    
private:
    node * stringNode;     //string에서 과목을 저장할 배열
    char * subjectNums;    //string에서 과목을 탐색할 과목명 문자열
    int nodeSize;          //stringNode의 사이즈
    int stringSize;        //subjectNums의 사이즈
    
};
