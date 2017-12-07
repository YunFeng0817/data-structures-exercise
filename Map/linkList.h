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

    bool insert(int place,Type d);  //往链表的指定位置插入元素

    bool insert(int place,Type d1,Type d2);

    cellElement* inquire(int place);

    bool pop(int place);

private:
    cellElement* head;
};

#endif //SCORE_SYSTEM_LINKLIST_H
