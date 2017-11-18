//
// Created by Fitz on 2017/11/16.
//

#include <iostream>
using namespace std;

struct cellElement{
    char data;
    cellElement *lchild,*rchild;
};

class BinaryTree
{
public:
    string pre,mid;
    cellElement *root;
    int length;
    BinaryTree(string a,string b)
    {
        pre=a;
        mid=b;
        if(a.length()!=b.length())
        {
            cout<<"输入的字符串不一样长，不合法"<<endl;
            exit(0);
        }
        length=a.length();
        root=create(mid[0],mid[length-1]);
    }
    cellElement * create(char a,char b)
    {
        static int i=0;
        int temp;
        cellElement *root=new cellElement;

        temp=mid.find((char)pre[i]);
        root->data=pre[i];
        if(a==b)
        {
            root->rchild=nullptr;
            root->lchild=nullptr;
            return root;
        }
        if(temp-1>=mid.find(a))
        {
            i++;
            root->lchild=create(a,mid[temp-1]);
        }
        else
        {
            root->lchild=nullptr;
        }
        if(temp+1<=mid.find(b))
        {
            i++;
            root->rchild=create(mid[temp+1],b);
        }
        else
        {
            root->rchild=nullptr;
        }
        return root;
    }

    void LayoutBehind(cellElement *root)
    {
        if(root==nullptr)
        {
            return;
        }
        LayoutBehind(root->lchild);
        LayoutBehind(root->rchild);
        cout<<root->data<<endl;
        delete(root);
        return;
    }
};

int main()
{
    string pre,mid;
    cout<<">>>请输入一个前序遍历的二叉树字符串"<<endl;
    cin>>pre;
    cout<<">>>请输入一个中序遍历的二叉树字符串"<<endl;
    cin>>mid;
    BinaryTree bt(pre,mid);
    bt.LayoutBehind(bt.root);
    return 0;
}
/*
abdhiecfjg
hdibeafjcg

abdhiejkcflmgno
hdibjekalfmcngo

abcdfgehi
bafdgchei

 */