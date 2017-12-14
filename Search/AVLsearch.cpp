//
// Created by Fitz on 2017/12/14.
//
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#define nullptr NULL

class node{
public:
    int balancedFactor;  //AVL的平衡因子
    int data;
    int sameNum;  //表示与该节点有相同关键字的个数
    node *lchild , *rchild;
    node()
    {
        lchild = nullptr;
        rchild = nullptr;
        data=-1;
        sameNum=0;
        balancedFactor=0;
    }
};

class AVL{
public:
    node *root;
    int size;
    AVL()
    {
        root=new node;
        size=0;
    }

    //test if the AVL tree is empty if so , return true
    bool empty()
    {
        return !size;
    }

    //search the specific data
    node* search(int searchNum)
    {
        if(searchNum==root->data)
            return root;
        else if(searchNum<root->data)
            return searchRecursive(searchNum,root->lchild);
        else
            return searchRecursive(searchNum,root->rchild);
    }


private:
    //this is for recursive search use and the other users can't use and see it and parameter is complex ,the search() is more easy for use
    node* searchRecursive(int searchNum,node* newTree)
    {
        if(searchNum==root->data)
            return newTree;
        else if(searchNum<root->data)
            return searchRecursive(searchNum,root->lchild);
        else
            return searchRecursive(searchNum,root->rchild);
    }
};

int main()
{
    return 0;
}
