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
    cellElement *previous = head;
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

    cellElement* loate(int id){
        if(head==NULL){
            //cout<<"数据还未录入，无法查询！"<<endl;
            return NULL;   //此处注意意外情况
        }
        else{
            cellElement *p = previous;
            while (p->next!=NULL){
                if(p->id==id)
                {
                    return p;
                }
                previous = p;
                p=p->next;
            }
            if(p->next==NULL){
                //cout<<"找不到此商品！"<<endl;
                return NULL;
            }
        }
    }

    void Delete(int id){
        cellElement *temp = this->loate(id);
        if(temp==NULL){
            return;
        }
        else{
            cellElement *p;
            p = previous->next;
            if(p->next==NULL){
                previous->next=NULL;
            }
            else{
                previous->next=p->next;
            }
            free(p);
        }
    }

    void modify(int id,int AddAmount){
        cellElement *p = this->loate(id);
        if(p==NULL){
            if(AddAmount<0) {
                cout<<"该物品没有库存了，无法提货！"<<endl;
                return;
            }
            string a,b;
            int price;
            cout<<"请补充该商品的信息"<<endl<<"请输入该商品的名称："<<endl;
            cin>>a;
            cout<<"请输入该商品的品牌："<<endl;
            cin>>b;
            cout<<"请输入该商品的价格："<<endl;
            cin>>price;
            this->insert(id,a,b,price,AddAmount);
        }
        if(p->amount+AddAmount<0){
            cout<<"库存不足，无法提出如此多的货物！"<<endl;
            return;
        }
        p->amount+=AddAmount;
        cout<<"数据更新成功！"<<endl;
        return;
    }

    void empty()
    {
        cellElement *p = head;
        cellElement *temp;
        while(p->next!=NULL){
            if(p==head){
                p = NULL;
                continue;
            }
            temp = p->next;
            free(p);
            p = temp;
        }
        free(p);
        return;
    }

};

int main()
{
    string a;
    printf("sa");
}