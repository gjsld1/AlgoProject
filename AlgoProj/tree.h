//
//  tree.hpp
//  AlgoProj
//
//  Created by 신예지 on 2018. 6. 8..
//  Copyright © 2018년 신예지. All rights reserved.
//

#pragma once
#include "stdafx.h"

struct treeNode : node {
    treeNode *left, *right;
    treeNode(char *name, int numName, char *preSubject, int numPreName,
             char* subjectNum, int isEssential, int isDesign, int isMajor, int credit);
    treeNode() {}
};

class Tree
{
public:
    Tree();
    ~Tree();
    void treeInsert(treeNode *newNode);
    void treeInsertSub(treeNode *newNode, treeNode *&rootNode);
    void showTree(treeNode *temp);
    void readTree(treeNode *temp);
    void searchTree(char *subName);   //TREE에서 학수번호로 찾기
    void subtake();
    
private:
    treeNode * z;
    treeNode headNode;
    treeNode tailNode;
    int size;
};
