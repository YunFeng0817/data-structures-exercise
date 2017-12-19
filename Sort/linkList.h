//
// Created by Fitz on 2017/12/7.
//

#ifndef SCORE_SYSTEM_LINKLIST_H
#define SCORE_SYSTEM_LINKLIST_H

template <typename Type>
class linkList {
public:
    int size;  //链表的长度
    struct cellElement
    {
        cellElement *next;
        Type data1,data2;
    };
    linkList();

    bool empty();  //判断链表是否为空

    bool insert(int place,Type d);  //往链表的指定位置插入元素,是在place值的后面插入一个元素，0 表示原本链表为空，插入一个新元素

    bool insert(int place,Type d1,Type d2);

    cellElement* inquire(int place);   //place是多少，查询的就是第几个元素

    bool pop(int place);   //删除第place个元素

private:
    cellElement* head;
};

#endif //SCORE_SYSTEM_LINKLIST_H
