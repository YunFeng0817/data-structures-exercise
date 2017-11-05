//
// Created by Fitz on 2017/11/5.
//
#include<iostream>
using namespace std;
typedef struct cellElement{
    cellElement *link;
    int coef,exp;
}cellElement;

cellElement * attach(int c,int e,cellElement *d)
{
    cellElement *p = new cellElement;
    if(d!=NULL)
        d->link=p;
    p->link=NULL;
    p->coef=c;
    p->exp=e;
    return p;
}

cellElement * padd(cellElement *a,cellElement *b)
{
    cellElement *p,*q,*d,*c,*del1,*del2;
    c=new cellElement;
    d=c;
    int temp;
    p=a;
    q=b;
    while(p!=NULL&&q!=NULL)
    {
        if(p->exp==q->exp)
        {
            temp=p->coef+q->coef;
            if(temp)
            {
                d=attach(temp,p->exp,d);
            }
            del2=q->link;
            q->link=NULL;
            delete(q);
            q=del2;
            del2=p->link;
            delete(p);
            p=del2;
        }
        else if(p->exp>q->exp)
        {
            d=attach(p->coef,p->exp,d);
            del1=p;
            p=p->link;
            delete(del1);
        }
        else
        {
            d=attach(q->coef,q->exp,d);
            del2=q;
            q=q->link;
            delete(del2);
        }
    }
    while(p!=NULL)
    {
        d=attach(p->coef,p->exp,d);
        del1=p->link;
        delete(p);
        p=del1;
    }
    while(q!=NULL)
    {
        d=attach(q->coef,q->exp,d);
        del2=q->link;
        delete(q);
        q=del2;
    }
    d->link=NULL;
    p=c;
    c=c->link;
    delete(p);
    return c;
}

cellElement * mult(cellElement *a,cellElement *b)
{
    cellElement *p,*q,*result1,*result2,*index,*del;
    int c,e;
    p=a;
    result1=NULL;
    result2=NULL;
    while(p!=NULL)
    {
        q=b;
        result2=NULL;
        index=result2;
        while(q!=NULL)
        {
            c=p->coef*q->coef;
            e=p->exp+q->exp;
            if(c)
            {
                index=attach(c,e,index);
                q=q->link;
            }
            if(index!=NULL&&result2==NULL)
            {
                result2=index;
            }
        }
//        del=result2;
//        while(result2!=NULL)
//        {
//            cout<<"result2->coef   result2->exp  "<<result2->coef<<"\t"<<result2->exp<<endl;
//            result2=result2->link;
//        }
//        result2=del;
        if(result1==NULL)
        {
            result1=result2;
        }
        else
        {
            result1=padd(result1,result2);
        }
        del=p;
        p=p->link;
        delete(del);
    }
    return result1;
}

void insert(int c,int e,cellElement *head)
{
    if(head->link==NULL){
        cellElement *p = new cellElement;
        head->link = p;
        p->coef=c;
        p->exp=e;
        p->link=NULL;
        return;
        //此处未判断传入的参数是否为空
    }

    else{
        cellElement *pr=head;
        cellElement *p=pr->link;
        while(p!=NULL)
        {
            if(p->exp<e)
            {
                cellElement *temp = new cellElement;
                temp->exp=e;
                temp->coef=c;
                temp->link = pr->link;
                pr->link = temp;
                return;
            }
            else if(p->exp==e)
            {
                p->coef+=c;
                return;
            }
            pr=p;
            p=p->link;
        }
        cellElement *temp = new cellElement;
        temp->exp=e;
        temp->coef=c;
        temp->link=NULL;
        pr->link=temp;
    }
}


int main()
{
    int a,b;
    cellElement *input1=new cellElement,*input2=new cellElement,*result;
    input1->link=NULL;
    input2->link=NULL;
    cout<<"请输入第一个多项式的值：（输入 0 0 时结束第一个多项式的输入）"<<endl;
    cin>>a;
    cin>>b;
    do
    {
        insert(a,b,input1);
        cin>>a;
        cin>>b;
    }while(a!=0&&b!=0);
    input1=input1->link;
//    while(input1!=NULL)
//    {
//        cout<<input1->coef<<"\t"<<input1->exp<<endl;
//        input1=input1->link;
//    }
    cout<<"请输入第二个多项式的值：（输入 0 0 时结束第二个多项式的输入）"<<endl;
    cin>>a>>b;
    do
    {
        insert(a,b,input2);
        cin>>a;
        cin>>b;
    }while(a!=0&&b!=0);
    input2=input2->link;
    result=mult(input1,input2);
    while(result!=NULL)
    {
        cout<<result->coef<<"\t"<<result->exp<<endl;
        result=result->link;
    }
    return 0;
}

/*
4 3
5 2
7 1
0 0
2 4
1 1
1 1
0 0
 */