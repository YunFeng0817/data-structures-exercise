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

    //通过中序遍历建立的搜索树来得到排序后的结果
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

    //单次向左旋转
    void leftRotate(node** tree)
    {
        node *newNode;
        newNode=(**tree).rchild;
        (**tree).rchild=newNode->lchild;
        newNode->lchild=*tree;
        *tree=newNode;
    }

    //单次向右旋转
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
        node* l=tree->lchild,*lr=l->rchild;    //l表示tree的左子树 lr表示左子树的右子树
        switch(l->balancedFactor)             //根据l的平衡因子来判断  是LL旋转还是LR旋转的方式来调节树的平衡
        {
            case LH:
                rightRotate(&tree);       //是左子树的左子树导致不平衡，是LL的旋转方式
                tree->balancedFactor=l->balancedFactor=EH;
                break;
            case RH:
                switch(lr->balancedFactor)   //调节tree和l的平衡因子
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
                leftRotate(&l);    //是LR的情况
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
                tree->balancedFactor=r->balancedFactor=EH;     //是RR的情况
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
                tree->rchild=r;   //是RL的旋转调节平衡方式
                leftRotate(&tree);
        }
        return tree;
    }

    void insert(int insertNum)
    {
        size++;
        bool addFloor=false;
        if(root->data==infinite)    //在第一次插入节点时，需要特殊处理
        {
            root->data=insertNum;
            return ;
        }
        if(root->data==insertNum)   //如果有相同的关键字，就在该节点的记录重复的数据上加一
        {
            root->sameNum++;
            return ;
        }
        else if(insertNum<root->data)
        {
            root->lchild=insertRecursive(root->lchild,insertNum,&addFloor);
            if(addFloor)
            {
                switch (root->balancedFactor)        //addFloor  是表示插入新节点导致层数增加，根据原来的状态来判断现在的平衡因子
                {
                    case LH:    //原本左子树比右子树高，需要作左平衡处理
                        root=leftBalanced(root);
                        addFloor=false;
                        break;
                    case EH:   //原本左、右子树等高，现因左子树增高而使树增高
                        root->balancedFactor=LH;
                        addFloor=true;
                        break;
                    case RH:   //原本右子树比左子树高，现左、右子树等高
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
                    case LH:    //原本左子树比右子树高，现左、右子树等高
                        root->balancedFactor=EH;
                        addFloor=false;
                        break;
                    case EH:    //原本左、右子树等高，现因右子树增高而使树增高
                        root->balancedFactor=RH;
                        addFloor=true;
                        break;
                    case RH:   //原本右子树比左子树高，需要作右平衡处理
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
        if(searchNum==newTree->data)
            return newTree;
        else if(searchNum<newTree->data)
        {
            if(newTree->lchild)
                return searchRecursive(searchNum,newTree->lchild);
        }
        else
        {
            if(newTree->rchild)
                return searchRecursive(searchNum,newTree->rchild);
            else
                return nullptr;
        }
    }

    //这个函数用于递归调用，与上面public属性的区别在于上面的函数传入的参数更少，更符合restful api 的设计
    node* insertRecursive(node *tree,int insertNum,bool *addFloor)
    {
        if(!tree)   //如果是空，表示搜索树中没有该节点
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
    cout<<atree.search(4)->data<<endl;
    cout<<"mid sequence results are:"<<endl;
    atree.MidRecursive(atree.root);
    return 0;
}
//13 12 10 6 4 11 2 8 7 5 3 1 9 13
//1,5,3,7,6,2,4,8,9,0
//21 12 10 6 4 11 2 8 7 5 3 1 9 13 102 3 14 45 23 455 65 12 4 56 546 1 45 6