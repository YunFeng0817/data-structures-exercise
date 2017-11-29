//
// Created by Fitz on 2017/11/29.
//
#include <iostream>
#include <fstream>
using namespace std;

int character[257];

void statistics()  //这是统计英语文章中字符出现频率的函数
{
    for(int i=0;i<=255;i++)
        character[i]=0;
    string filePath;
    char temp;
    cout<<"请输入要压缩处理的英文文章的路径"<<endl;
    cin>>filePath;
    ifstream englishArticle(filePath,ios::in);
    if(!englishArticle.is_open())
    {
        cout<<"打开文件失败,请输入有效路径"<<endl;
        exit(0);
    }
    while(!englishArticle.eof())
    {
        cin>>temp;
        character[int(temp)]++;
    }
    englishArticle.close();
}

int main()
{
    statistics();
    return 0;
}
