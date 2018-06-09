//
//  array.hpp
//  AlgoProj
//
//  Created by 신예지 on 2018. 6. 8..
//  Copyright © 2018년 신예지. All rights reserved.
//

#pragma once
#include "stdafx.h"


class Array
{
public:
    Array();
    ~Array();
    void showArray();
    //void deleteArray();
    int searchArray(char *subName);
    void subtake();
    
private:
    node * arrayNode;
    int size;
    
};
