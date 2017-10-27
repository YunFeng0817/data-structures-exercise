//coding=utf-8
// Created by Fitz on 2017/10/27.
//
#include <iostream>
#include <stdio.h>
using namespace std;
typedef struct cellElement{
    cellElement *next;
    string name;
    string brand;   //表示品牌
    int id,price ,amount;
}cellElement;

class chain{
    cellElement *head=NULL;

    void insert(int id,string n,string b,int price,int a)
    {
        if(head==NULL){
            cellElement *p = (cellElement *)malloc(sizeof(cellElement));
            if(p==NULL){
                cout<<"空间不足，无法申请到空间！"<<endl;
                return;
            }
            head = p;
            p->id=id;
            p->next=NULL;
            p->name=n;
            p->brand=b;
            p->price=price;
            p->amount=a;

            //此处未判断传入的参数是否为空
        }

        else{
            cellElement *pr=head;
            cellElement *p=pr->next;
            while(p->next!=NULL)
            {
                if(p->price>=price)
                {
                    cellElement *temp = (cellElement *)malloc(sizeof(cellElement));
                    if(temp==NULL){
                        cout<<"空间不足，无法申请到空间！"<<endl;
                        return;
                    }
                    temp->id=id;
                    temp->next=p;
                    temp->name=n;
                    temp->brand=b;
                    temp->price=price;
                    temp->amount=a;
                    pr->next=temp;
                    return ;
                }
                pr=p;
                p=p->next;
            }
            if(p->next==NULL)
            {
                cellElement *temp = (cellElement *)malloc(sizeof(cellElement));
                if(temp==NULL){
                    cout<<"空间不足，无法申请到空间！"<<endl;
                    return;
                }
                temp->id=id;
                temp->next=p;
                temp->name=n;
                temp->brand=b;
                temp->price=price;
                temp->amount=a;
                temp->next=NULL;
                p->next=temp;
            }
        }
    }

    cellElement loate(int id){
        if(head==NULL){
            cout<<"数据还未录入，无法查询！"<<endl;
            return;
        }
        else{
            cellElement *p = head;
            while (p->next!=NULL){
                if(p->id==id)
                {
                    return *p;
                }
                p=p->next;
            }
            if(p->next==NULL){
                cout<<"找不到此商品！"<<endl;
            }
        }
    }

};

int main()
{
    string a;
    printf("sa");
}