//
// Created by Fitz on 2017/11/18.
//
#include <iostream>
#include <stack>
#include <queue>
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
            cout<<"error:  输入的字符串不一样长，不合法"<<endl;
            exit(0);
        }
        for(int i=0;i<length;i++)
        {
            if(mid.find(pre[i])==-1||pre.find(mid[i]))
            {
                cout<<"error:  输入的数据无法建立二叉树"<<endl;
                exit(0);
            }
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
//前序遍历递归
    void PreviousRecursive(cellElement *root)
    {
        if(root!=nullptr)
        {
            cout<<root->data<<" ";
            PreviousRecursive(root->lchild);
            PreviousRecursive(root->rchild);
        }
    }
//前序遍历非递归
    void PreviousNotRecursive(cellElement *root)
    {
        stack<cellElement*> trace;
        while(!trace.empty()||root)
        {
            if(root)
            {
                cout<<root->data<<" ";
                trace.push(root);
                root=root->lchild;
            }
            else
            {
                root=trace.top();
                trace.pop();
                root=root->rchild;
            }
        }
    }
//中序遍历递归
    void MidNotRecursive(cellElement *root)
    {
        stack<cellElement *> trace;
        while(root||!trace.empty())
        {
            if(root)
            {
                trace.push(root);
                root=root->lchild;
            }
            else
            {
                root=trace.top();
                cout<<root->data<<" ";
                trace.pop();
                root=root->rchild;
            }
        }
    }
//中序遍历非递归
    void MidRecursive(cellElement *root)
    {
        if(root!=nullptr)
        {
            MidRecursive(root->lchild);
            cout<<root->data<<" ";
            MidRecursive(root->rchild);
        }
    }
//后序遍历递归
    void BehindNotRecursive(cellElement *root)
    {
        stack<cellElement*> trace;
        int flag;
        cellElement *LastVisted;
        do
        {
            while(root)
            {
                trace.push(root);
                root=root->lchild;
            }
            flag=1;      //表示该相对根节点的所有左节点已经入栈，访问过了
            LastVisted= nullptr;
            while(flag==1&&!trace.empty())
            {
                root=trace.top();
                if(LastVisted==root->rchild)
                {
                    cout<<root->data<<" ";
                    trace.pop();
                    LastVisted=root;
                }
                else
                {
                    root=root->rchild;
                    flag=0;
                }
            }
        }while(!trace.empty());
    }
//后序遍历非递归
    void BehindRecursive(cellElement *root)
    {
        if(root!=nullptr)
        {
            BehindRecursive(root->lchild);
            BehindRecursive(root->rchild);
            cout<<root->data<<" ";
        }
    }
//层序遍历
    void FloorOrder(cellElement *root)
    {
        queue<cellElement*> floor;
        int len=0,newlen=0,count=0;
        while(count<length)
        {
            if(len==0&&newlen!=0)
            {
                len=newlen;
                newlen=0;
            }
            else if(newlen==0)
            {
                floor.push(root);
                len++;
            }
            while(len!=0)
            {
                if(floor.front()->lchild)
                {
                    floor.push(floor.front()->lchild);
                    newlen++;
                }
                if(floor.front()->rchild)
                {
                    floor.push(floor.front()->rchild);
                    newlen++;
                }
                root=floor.front();
                cout<<floor.front()->data<<" ";
                count++;
                floor.pop();
                len--;
            }
        }
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
    cout<<"前序遍历此二叉树的  递归  结果是："<<endl;
    bt.PreviousRecursive(bt.root);
    cout<<endl;
    cout<<"前序遍历此二叉树的  非递归  结果是："<<endl;
    bt.PreviousNotRecursive(bt.root);
    cout<<endl;
    cout<<"中序遍历此二叉树的  递归  结果是："<<endl;
    bt.MidRecursive(bt.root);
    cout<<endl;
    cout<<"中序遍历此二叉树的  非递归  结果是："<<endl;
    bt.MidNotRecursive(bt.root);
    cout<<endl;
    cout<<"后序遍历此二叉树的  递归  结果是："<<endl;
    bt.BehindRecursive(bt.root);
    cout<<endl;
    cout<<"后序遍历此二叉树的  非递归  结果是："<<endl;
    bt.BehindNotRecursive(bt.root);
    cout<<endl;
    cout<<"层序遍历此二叉树的结果是："<<endl;
    bt.FloorOrder(bt.root);
    cout<<endl;
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