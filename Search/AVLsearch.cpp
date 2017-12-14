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
    //contain the message of the search result
    struct searchResult{
        node * tree;
        bool found;
    };
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
    searchResult search(int searchNum)
    {
        searchResult temp;
        if(searchNum==root->data)
        {
            temp.tree=root;
            temp.found=true;
            return temp;
        }
        else if(searchNum<root->data)
        {
            if(root->lchild==nullptr)
            {
                temp.tree=root;
                temp.tree=false;
                return temp;
            }
            else
            {
                return searchRecursive(searchNum,root->lchild);
            }
        }
        else
        {
            if(root->lchild==nullptr)
            {
                temp.tree=root;
                temp.found=false;
                return temp;
            }
            else
            {
                return searchRecursive(searchNum,root->rchild);
            }
        }
    }

    void insert(int insertNum)
    {
        searchResult result;
        result = search(insertNum);
        if(result.found)
            result.tree->sameNum++;
        else
        {

        }
    }
private:
    //this is for recursive search use and the other users can't use and see it and parameter is complex ,the search() is more easy for use
    searchResult searchRecursive(int searchNum,node* newTree)
    {
        searchResult temp;
        if(searchNum==newTree->data)
        {
            temp.tree=newTree;
            temp.found=true;
            return temp;
        }
        else if(searchNum<newTree->data)
        {
            if(newTree->lchild==nullptr)
            {
                temp.tree=newTree;
                temp.tree=false;
                return temp;
            }
            else
            {
                return searchRecursive(searchNum,newTree->lchild);
            }
        }
        else
        {
            if(newTree->lchild==nullptr)
            {
                temp.tree=newTree;
                temp.found=false;
                return temp;
            }
            else
            {
                return searchRecursive(searchNum,newTree->rchild);
            }
        }
    }
};

int main()
{
    return 0;
}
