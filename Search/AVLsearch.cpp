//
// Created by Fitz on 2017/12/14.
//
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#define nullptr NULL


class AVL{
#define LH 1
#define EH 0
#define RH -1
public:
    class node{
#define infinite 0x0fffffff
    public:
        int balancedFactor;  //AVL的平衡因子
        int data;
        int sameNum;  //表示与该节点有相同关键字的个数
        node *lchild , *rchild;
        node()
        {
            lchild = nullptr;
            rchild = nullptr;
            data=infinite;
            sameNum=1;
            balancedFactor=0;
        }
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

    void PreviousRecursive(node *root)
    {
        if(root!=nullptr)
        {
            cout<<root->data<<" ";
            PreviousRecursive(root->lchild);
            PreviousRecursive(root->rchild);
        }
    }

    void MidRecursive(node *root)
    {
        if(root!=nullptr)
        {
            MidRecursive(root->lchild);
            cout<<root->data<<" ";
            MidRecursive(root->rchild);
        }
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

    void leftRotate(node** tree)
    {
        node *newNode;
        newNode=(**tree).rchild;
        (**tree).rchild=newNode->lchild;
        newNode->lchild=*tree;
        *tree=newNode;
    }

    void rightRotate(node** tree)
    {
        node *newNode;
        newNode=(**tree).lchild;
        (**tree).lchild=newNode->rchild;
        newNode->rchild=*tree;
        *tree=newNode;
    }

    node* leftBalanced(node* tree)
    {
        node* l=tree->lchild,*lr=l->rchild;
        switch(l->balancedFactor)
        {
            case LH:
                rightRotate(&tree);
                tree->balancedFactor=l->balancedFactor=EH;
                break;
            case RH:
                switch(lr->balancedFactor)
                {
                    case LH:
                        l->balancedFactor=EH;
                        tree->balancedFactor=RH;
                        break;
                    case EH:
                        l->balancedFactor=tree->balancedFactor=EH;
                        break;
                    case RH:
                        l->balancedFactor=LH;
                        tree->balancedFactor=EH;
                        break;
                }
                lr->balancedFactor=EH;
                leftRotate(&l);
                tree->lchild=l;
                rightRotate(&tree);

        }
        return tree;
    }

    node* rightBalanced(node* tree)
    {
        node *r=tree->rchild,*rl=r->lchild;
        switch(r->balancedFactor)
        {
            case RH:
                leftRotate(&tree);
                tree->balancedFactor=r->balancedFactor=EH;
                break;
            case LH:
                switch(rl->balancedFactor)
                {
                    case LH:
                        tree->balancedFactor=EH;
                        r->balancedFactor=RH;
                    break;
                    case EH:
                        tree->balancedFactor=r->balancedFactor=EH;
                    break;
                    case RH:
                        tree->balancedFactor=LH;
                        r->balancedFactor=EH;
                    break;
                }
                rl->balancedFactor=EH;
                rightRotate(&r);
                tree->rchild=r;
                leftRotate(&tree);
        }
        return tree;
    }

    void insert(int insertNum)
    {
        size++;
        bool addFloor=false;
        if(root->data==infinite)
        {
            root->data=insertNum;
            return ;
        }
        if(root->data==insertNum)
        {
            root->sameNum++;
            return ;
        }
        else if(insertNum<root->data)
        {
            root->lchild=insertRecursive(root->lchild,insertNum,&addFloor);
            if(addFloor)
            {
                switch (root->balancedFactor)
                {
                    case LH:
                        root=leftBalanced(root);
                        addFloor=false;
                        break;
                    case EH:
                        root->balancedFactor=LH;
                        addFloor=true;
                        break;
                    case RH:
                        root->balancedFactor=EH;
                        addFloor=false;
                        break;
                }
            }
        }
        else
        {
            root->rchild=insertRecursive(root->rchild,insertNum,&addFloor);
            if(addFloor)
            {
                switch(root->balancedFactor)
                {
                    case LH:
                        root->balancedFactor=EH;
                        addFloor=false;
                        break;
                    case EH:
                        root->balancedFactor=RH;
                        addFloor=true;
                        break;
                    case RH:
                        root=rightBalanced(root);
                        addFloor=false;
                        break;
                }
            }
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

    node* insertRecursive(node *tree,int insertNum,bool *addFloor)
    {
        if(!tree)
        {
            tree = new node;
            tree->data=insertNum;
            *addFloor=true;
            return tree;
        }
        if(tree->data==insertNum)
        {
            tree->sameNum++;
            *addFloor=false;
        }
        else if(insertNum<tree->data)
        {
            tree->lchild=insertRecursive(tree->lchild,insertNum,addFloor);
            if(*addFloor)
            {
                switch (tree->balancedFactor)
                {
                    case LH:
                        tree=leftBalanced(tree);
                        *addFloor=false;
                        break;
                    case EH:
                        tree->balancedFactor=LH;
                        *addFloor=true;
                        break;
                    case RH:
                        tree->balancedFactor=EH;
                        *addFloor=false;
                        break;
                }
            }
        }
        else
        {
            tree->rchild=insertRecursive(tree->rchild,insertNum,addFloor);
            if(*addFloor)
            {
                switch(tree->balancedFactor)
                {
                    case LH:
                        tree->balancedFactor=EH;
                        *addFloor=false;
                        break;
                    case EH:
                        tree->balancedFactor=RH;
                        *addFloor=true;
                        break;
                    case RH:
                        tree=rightBalanced(tree);
                        *addFloor=false;
                        break;
                }
            }
        }
        return tree;
    }
};

int main()
{
    AVL atree;
    int n,a;
    cout<<"input the number of the num"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a;
        atree.insert(a);
    }
    cout<<"mid sequence results are:"<<endl;
    atree.MidRecursive(atree.root);
    return 0;
}
//13 12 10 6 4 11 2 8 7 5 3 1 9 13
//1,5,3,7,6,2,4,8,9,0
//21 12 10 6 4 11 2 8 7 5 3 1 9 13 102 3 14 45 23 455 65 12 4 56 546 1 45 6