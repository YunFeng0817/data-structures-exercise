//
// Created by Fitz on 2017/10/31.
//

#include <iostream>
#include <math.h>
using namespace std;

string operation = "+-*/()#";

//这个二维数组用来描述算术的优先级
                            /*    +      -      *    /    (     )     #    */
bool pority[7][7]={     /* + */{false,true,true,true,true,false,false},
                        /* - */{false,true,true,true,true,false,false},
                        /* * */{false,false,false,false,true,true,true,},
                        /* / */{false,false,false,false,true,false,false},
                        /* ( */{true,true,true,true,true,true,true},
                        /* ) */{false,false,false,false,false,false,false},
                        /* # */{true,true,true,true,true,true,true}};

typedef union charOrDouble{
    double num;
    char op;
}charOrDouble;


typedef struct cellElement{
    cellElement *next;
    charOrDouble data;
    bool ifIDouble;
}cellElement;

//这个类是基本的由指针构成的栈结构
class stack
{
public:
    cellElement *head=new cellElement;
    int length=0;

    stack(){
        length=0;
        head->next=NULL;
    }

    void push(charOrDouble temp,bool ifINT)
    {
        cellElement *cell = new cellElement;
        if(length==0)
        {
            head->next=cell;
            cell->next=NULL;
        }
        else{
            cell->next=head->next;
            head->next=cell;
        }
        cell->data = temp;
        cell->ifIDouble=ifINT;
        length++;
        return;
    }

    charOrDouble pop() //在调用pop()前要判断是否为空
    {
        charOrDouble x;
        cellElement *temp = head->next;
        head->next = temp->next;
        x = temp->data;
        delete(temp);
        length--;
        return x;
    }

    bool Empty()
    {
        if(head->next==NULL)
            return true;
        else
            return false;
    }

    cellElement * top()
    {
        if(Empty())
            return NULL;
        else
            return (head->next);
    }

};

//这个类是用于将中缀表达式转化为后缀表达式
class mid2tail:stack
{
public:
    stack max;
    stack OpChar;

    void push(char temp)
    {
        charOrDouble x;
        x.op = temp;
        OpChar.push(x, false);
        if(max.Empty())
        {
            max.push(x,false);
        }
        else if(pority[operation.find((*max.top()).data.op)][operation.find(x.op)])
        {
            max.push(x,false);
        }
        else;
    }

    char pop()
    {
        char x;
        charOrDouble temp;
        temp=OpChar.pop();
        x=temp.op;
        if(!max.Empty()&&(*max.top()).data.op==temp.op)
            max.pop();
        return x;
    }
};



string Input;
stack transition;
charOrDouble tran;
stack tail1,tail2,tail3,result;
mid2tail str;

//这个函数是用来将中缀表达式转换为后缀表达式
//这个函数用来检查输入是否符合规范
void CheckInput(){
    stack ForCheck;
    for(int i=0;i<Input.length();i++)
    {
        if(i!=0&&Input[i]=='-'&&Input[i-1]!='('&&Input[i-1]!='+'&&Input[i-1]!='-'&&Input[i-1]<'0'&&Input[i-1]>'9')
        {
            cout<<"error!!!: 负号的输入不正确，请重新输入"<<endl;
            exit(0);
        }
        if(Input[i]=='(')
        {
            tran.op=Input[i];
            ForCheck.push(tran,false);
        }
        if(Input[i]==')')
        {
            if(ForCheck.Empty())
            {
                cout<<"error!!!:  您的输入缺少至少一个 ) ，请重新输入"<<endl;
                exit(0);
            }
            else
            {
                ForCheck.pop();
            }
        }
    }
    if(!ForCheck.Empty())
    {
        cout<<"warning!!!:您的输入多出了至少一个 ( ,计算结果可能有误"<<endl;
    }
    return ;
}

void mid2post()
{
    double sum;
    char temp3;
    for(int i=0;i<=Input.length();i++)
    {
        if(Input[0]=='-'&&i==0)
        {
            tran.num=0;
            tail1.push(tran, true);
        }
        if((Input[i]>='0'&&Input[i]<='9'&&i!=Input.length()))
        {
            tran.num=int(Input[i]-'0');
            transition.push(tran,true);
        }
        else if(Input[i]=='.')  //判断浮点数的情况
        {
            tran.op='.';
            transition.push(tran,false);
        }
        else
        {
            if(!transition.Empty())
            {
                sum=0;
                int temp1 = transition.length;
                int temp2=-1;
                for(int j=1;j<=temp1;j++)
                {
                    if(transition.top()->ifIDouble)
                    {
                        if(temp2!=-1)
                            sum+=transition.pop().num*(int)pow(10,j-2);
                        else
                            sum+=transition.pop().num*(int)pow(10,j-1);
                    }
                    else
                    {
                        temp2=j;
                        transition.pop();
                    }
                }
                if(temp2!=-1)
                    sum=sum/(int)pow(10,temp2-1);
                tran.num=sum;
                tail1.push(tran,true);
            }
            if((str.max.Empty()||pority[operation.find(str.max.top()->data.op)][operation.find(Input[i])])&&i!=Input.length())
            {
                if(Input[i]=='-')//用来判断单运算符的情况
                {
                    if(!str.OpChar.Empty()&&!str.OpChar.top()->ifIDouble&&(str.OpChar.top()->data.op=='('||str.OpChar.top()->data.op=='+'||str.OpChar.top()->data.op=='-'))
                    {
                        tran.num=0;
                        tail1.push(tran,true);
                        str.push(Input[i]);
                        continue;
                    }
                }
                if(Input[i]==')')//用来判断有）的情况
                {
                    do
                    {
                        temp3=str.pop();
                        if(temp3!='(')
                        {
                            tran.op=temp3;
                            tail1.push(tran, false);
                        }
                    }while(temp3!='(');
                    continue;
                }
                str.push(Input[i]);
            }
            else{
                if(Input[i]==')')
                {
                    do
                    {
                        temp3=str.pop();
                        if(temp3!='(')
                        {
                            tran.op=temp3;
                            tail1.push(tran, false);
                        }
                    }while(temp3!='(');
                    continue;
                }
                if(i==Input.length()) //在字符串录入结束后，一次性将所有的字符出栈
                {
                    int temp2=str.OpChar.length;
                    for(int i=0;i<temp2;i++)
                    {
                        tran.op=str.pop();
                        if(tran.op!='(')
                            tail1.push(tran,false);
                    }
                    continue;
                }
                while(!str.OpChar.Empty()&&pority[operation.find(Input[i])][operation.find(str.max.top()->data.op)])
                {
                    tran.op=str.pop();
                    tail1.push(tran,false);
                }
                str.push(Input[i]);
            }
        }
    }
}

void mid2result()
{
    double temp1,temp2,temp3,r;
    char TempChar;
    temp1 = tail2.length;
    for(int i=0;i<temp1;i++)
    {
        if(tail2.top()->ifIDouble)
        {
            tran = tail2.pop();
            result.push(tran,true);
        }
        else
        {
            TempChar=tail2.pop().op;
            tran=result.pop();
            temp2=tran.num;
            tran=result.pop();
            temp3=tran.num;
            switch(TempChar)
            {
                case '+':
                    r=temp2+temp3;
                    break;
                case '-':
                    r=temp3-temp2;
                    break;
                case '*':
                    r=temp2*temp3;
                    break;
                case '/':
                    if(temp3==0)
                    {
                        cout<<"除数不能为0"<<endl;
                        exit(0);
                    }
                    r=temp2/temp3;
                    break;
                default:
                    cout<<"出现非法操作符"<<endl;
                    exit(0);
            }
            tran.num=r;
            result.push(tran,true);
        }
    }
}

int main()
{
    cin>>Input;
    CheckInput();
    mid2post();
    int temp = tail1.length;
    for(int i=0;i<temp;i++)  //将tail1的倒序转换为正序
    {
        bool ifDouble=tail1.top()->ifIDouble;
        tran=tail1.pop();
        tail2.push(tran,ifDouble);
        tail3.push(tran,ifDouble);
    }
    for(int i=0;i<temp;i++)  //just for test
    {
        if(tail3.top()->ifIDouble)
            cout<<tail3.pop().num<<" ";
        else
            cout<<tail3.pop().op<<" ";
    }
    cout<<endl;
    mid2result();
    cout<<result.pop().num<<endl;
    return 0;
}