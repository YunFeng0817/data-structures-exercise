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
#define LH 1
#define EH 0
#define RH -1
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
        {
            if(root->lchild)
                return searchRecursive(searchNum,root->lchild);
            else
                return nullptr;
        }
        else
        {
            if(root->rchild)
                return searchRecursive(searchNum,root->rchild);
            else
                return nullptr;
        }
    }


private:
    //this is for recursive search use and the other users can't use and see it and parameter is complex ,the search() is more easy for use
    node* searchRecursive(int searchNum,node* newTree)
    {
        if(searchNum==root->data)
            return newTree;
        else if(searchNum<root->data)
        {
            if(newTree->lchild)
                return searchRecursive(searchNum,root->lchild);
        }
        else
        {
            if(newTree->rchild)
                return searchRecursive(searchNum,root->rchild);
            else
                return nullptr;
        }
    }
};

int main()
{
    return 0;
}
