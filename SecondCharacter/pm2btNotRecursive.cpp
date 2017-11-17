//
// Created by Fitz on 2017/11/16.
//

#include <iostream>
#include<stack>
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
    stack <cellElement *> trace;
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
        root=create();
    }
    cellElement *create()
    {
        bool flag=true;
        char temp;
        cellElement *root1=new cellElement;

        for(int i=0;i<length;i++)
        {
            root1->data=pre[i];
            if(mid.find(pre[i])==0||mid.find(pre[i])==length-1)
            {
                root1->lchild=nullptr;
                root1->rchild= nullptr;
                root1=trace.top();
                trace.pop();
                if(mid.find(pre[i])==length-1)
                {
                    root1=trace.top();
                    trace.pop();
                }
            }
            if(i!=length-1&&mid.find(pre[i+1])<mid.find(pre[i]))
            {
                root1->lchild=new cellElement;
                trace.push(root1);
                root1=root1->lchild;
                flag=true;
            }
            if(i!=length-1&&mid.find(pre[i+1])>mid.find(pre[i]))
            {
                if(flag)
                {
                    flag=!flag;
                    if(mid.find(pre[i])!=0)
                        root1->lchild=nullptr;
                }
                else
                {
                    root1->lchild=nullptr;
                    root1->rchild=nullptr;
                    trace.pop();
                    root1=trace.top();
                    trace.pop();
                }
                root1->rchild=new cellElement;
                trace.push(root1);
                root1=root1->rchild;
            }
        }
        return root1;
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
hidbeafjcg
 */