//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "linkList.h"

using namespace std;
#define Max 60000000   //需要排序数组的最大范围
#define bucketNum 5    //桶的个数
#define madix 1000      //基数排序中基数的大小
#define MaxRandom 10000000     //生成随机数时最大随机范围的定义
int randomNum1[Max], randomNum2[Max], randomNum3[Max], randomNum4[Max];    //分别用于四种排序
int temp1[Max + 1];   //用于计数排序的辅助数组
int temp2[Max + 1];   //用于计数排序的辅助数组
linkList<int> bucket[bucketNum];   //桶内的链表结构，使用方法详见 linkList.h

//桶排序的函数，num接收一个数组，length表示数组的长度
void bucketSort(int num[], int length) {
    int flag;
    //在每个桶内使用的是插入排序法
    for (int i = 0; i < length; i++) {
        if (bucket[num[i] >> 1].size == 0)  //如果原来链表为空，就插入一个新元素
            bucket[num[i] >> 1].insert(0, num[i]);
        else {
            flag = 0;
            for (int j = 1; j <= bucket[num[i] >> 1].size; j++) {    //从链表的开头遍历找到新节点合适的插入位置
                if (bucket[num[i] >> 1].inquire(j)->data1 > num[i]) {
                    bucket[num[i] >> 1].insert(j - 1, num[i]);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                bucket[num[i] >> 1].insert(bucket[num[i] >> 1].size, num[i]);
        }
    }
    int count = 0;
    //按照桶的顺序遍历每个桶，将桶内的有序元素赋给要排序的数组，同时释放内存
    for (int i = 0; i < bucketNum; i++) {
        for (int j = 1; j <= bucket[i].size; j++) {
            num[count] = bucket[i].inquire(j)->data1;
            bucket[i].pop(j);    //释放内存，防止内存泄漏
            count++;
        }
    }
}

//一种计数排序的省内存，效率高，但是不能用于基数排序的版本
void countSortEasy(int num[], int length, int maxNum) {
    memset(temp1, 0, sizeof(int) * (maxNum + 1));
    for (int i = 0; i < length; i++)
        temp1[num[i]]++;
    int c = 0;
    for (int i = 0; i <= maxNum; i++) {
        for (int j = 0; j < temp1[i]; j++) {
            num[c] = i;
            c++;
        }
    }
}

//这种是空间消耗较大，效率相对较低的版本，但是可以用于多关键词比较
void countSortComplex(int num[], int length, int maxNum) {
    int better1, better2, better3;   //用于循环展开的优化方式
    memset(temp1, 0, sizeof(int) * (maxNum + 1));
    for (int i = 0; i < length; i++)
        temp1[num[i]]++;
    int x;
    //这个函数本来是迭代的循环，根据计算机系统的原理，我使用3x1循环展开的方式来优化效率，提高并行执行的能力，可以达到提升效率的目的
    for (x = 0; x < length - 4; x += 3) {
        better1 = temp1[x] + temp1[x + 1];
        better2 = temp1[x] + (temp1[x + 1] + temp1[x + 2]);
        temp1[x + 1] = better1;
        better3 = better1 + (temp1[x + 2] + temp1[x + 3]);
        temp1[x + 2] = better2;
        temp1[x + 3] = better3;
    }
    //处理不能整除的剩余部分
    for (; x <= maxNum - 1; x++) {
        temp1[x + 1] = temp1[x] + temp1[x + 1];
    }

    //这是不用循环展开优化的版本
//    for(int i=0;i<maxNum-1;i++)
//    {
//        temp1[i+1]=temp1[i]+temp1[i+1];
//    }

    //定位排序后的元素位置
    for (int i = length - 1; i >= 0; i--) {
        temp2[temp1[num[i]] - 1] = num[i];
        temp1[num[i]]--;
    }
    //将修改后的值赋给需要排序的数组
    for (int i = 0; i < length; i++) {
        num[i] = temp2[i];
    }
}

//基数排序的实现  ，内部使用了计数排序的复杂版本
void madixSort(int num[], int length, int max) {
//    原本用来寻找传入数组的最大值
//    int max=num[0];
//    for(int i=0;i<length-1;i++)
//    {
//        if(max<num[i+1])
//            max=num[i+1];
//    }
    int temp = 1;
    int stash;   //这里存储一个常用值，来优化效率
    memset(temp1, 0, sizeof(int) * (max + 1));
    //循环，依次按照个位，十位……排序
    while (max / temp) {
        //接下来的都是计数排序的内容
        //按照某位,  暂存数组存的是该位出现的次数
        for (int i = 0; i < length; i++)
            temp1[(num[i] / temp) % madix]++;
        //暂存数组temp1  中存储小于下标值的出现次数
        for (int i = 0; i < madix; i++) {
            temp1[i + 1] = temp1[i] + temp1[i + 1];
        }
        //定位按照某位排序后关键字存储的位置，暂存于 temp2中
        for (int i = length - 1; i >= 0; i--) {
            stash = (num[i] / temp) % madix;   //存储的是num[i]的某位的值
            temp2[temp1[stash] - 1] = num[i];
            temp1[stash]--;
        }
        memset(temp1, 0, sizeof(int) * (max + 1));//初始化，避免下次循环出现Bug
        //将temp2的内容复制到num数组中
        for (int i = 0; i < length; i++) {
            num[i] = temp2[i];
        }
        temp *= madix;
    }
}

int main() {
    int temp;
    for (int i = 0; i < Max; i++) {
//        temp = rand() % MaxRandom;
        temp=Max-i;
        randomNum1[i] = temp;
        randomNum2[i] = temp;
        randomNum3[i] = temp;
        randomNum4[i] = temp;
    }
    double time;
    time = clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //从大到小排序
//    qsort(randomNum1,Max, sizeof(int),cmp);   //从小到大排序
    sort(randomNum1, &randomNum1[Max]);
    time = clock() - time;
    cout << "排序随机数的数据规模是" << Max << endl << "STL快排的用时为：\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    countSortComplex(randomNum2, Max, Max);
    time = clock() - time;
    cout << "计数排序（可用于基数排序，多占内存版本）的数据规模是" << Max << endl << "用时为：\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    countSortEasy(randomNum3, Max, Max);
    time = clock() - time;
    cout << "计数排序(省内存版本)的数据规模是" << Max << endl << "用时为：\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    madixSort(randomNum4, Max, Max);
    time = clock() - time;
    cout << "基数排序的数据规模是" << Max << endl << "用时为：\t";
    cout << time / 1000 << "s" << endl;
    for (int i = 0; i < Max; i++) {
        if (randomNum1[i] != randomNum2[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
        if (randomNum1[i] != randomNum3[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
        if (randomNum1[i] != randomNum4[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
    }
    return 0;
}
