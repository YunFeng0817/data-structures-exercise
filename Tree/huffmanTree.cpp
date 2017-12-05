//
// Created by Fitz on 2017/11/29.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;
//用于确定数组建立时分配大小
#define codeNum 256
#define nullptr NULL
//这个函数用于从文件读取信息，flag=1表明读取一个未压缩文件，flag=2表明读取一个已经压缩过的文件，用于解压
void getContent(int flag,char* path);
//这个函数用于统计文章中每种字符的出现频数
void statistics();
//这个函数用于将压缩或者解压后的内容写入文件
void writeCode(int flag,char* path);
//用来存储输入文章的字符频数，以其对应的ascii码作为数组的下标
int character[codeNum+1];
//用来存储从文件读入的二进制的编码
string Article;
//用来存储从文件读入的二进制的编码
string binary;
//这个结构踢表示一个哈夫曼树的一个节点
struct CellElement
{
    int pority;   //编码节点的权重
    int pocessID; //编码的ID
};
//这个类表示小根堆的一个节点
class cellElement
{
public:
    int weight,lchild,rchild;
    cellElement()
    {
        weight=0;
        lchild=-1;
        rchild=-1;
    }
};

class heapmin
{
public:
    int size;
    int Maxlength;
    CellElement *Elements;
    heapmin(int length)
    {
        size=0;
        Maxlength=length;
        Elements=new CellElement[Maxlength];
    }

    bool empty()
    {
        if(size==0)
            return true;
        return false;
    }

    bool full()
    {
        return (size==Maxlength-1);
    }

    bool insert(int p,int ID)
    {
        int i=size+1;
        if(!full())
        {
            size++;
            while(i!=1&&p<=Elements[i/2].pority)
            {
                if(p<Elements[i/2].pority||(p==Elements[i/2].pority&&ID<Elements[i/2].pocessID))
                {
                    Elements[i].pority=Elements[i/2].pority;
                    Elements[i].pocessID=Elements[i/2].pocessID;
                    i=i/2;
                }
                else
                    break;
            }
            Elements[i].pocessID=ID;
            Elements[i].pority=p;
            return true;
        }
        return false;
    }

    CellElement top()
    {
        return Elements[1];
    }

    bool DeleteMin() {
        int parent = 1, child = 2;
        CellElement temp;
        if (!empty()) {
            temp = Elements[size];
            size--;
            while (child <= size) {
                if (child < size && Elements[child].pority > Elements[child + 1].pority)
                    child++;
                else if(child < size && Elements[child].pority == Elements[child + 1].pority&&Elements[child].pocessID>Elements[child + 1].pocessID)
                    child++;
                if (temp.pority < Elements[child].pority)
                    break;
                if(temp.pority==Elements[child].pority&&temp.pocessID<Elements[child].pocessID)
                    break;
                Elements[parent] = Elements[child];
                parent = child;
                child *= 2;
            }
            Elements[parent] = temp;
            return true;
        }
        return false;
    }
};
//建立了一个以codeNum+1大小的小根堆，用于森林权重的比较大小
heapmin sortedNum(codeNum+1);

class huffmanTree
{
public:
    int * frequency;
    string codeRule[codeNum+1],temp,encodeResult,decodeResult,encodeBinary,input;
    cellElement HT[2*codeNum-1];
    huffmanTree(int *temp)
    {
        frequency=temp;
    }
    //该函数根据传入的字符出现频率，建立哈夫曼树
    void establishTree()
    {
        for(int i=0;i<2*codeNum-1;i++)
        {
            HT[i].weight=0;
            HT[i].lchild=-1;
            HT[i].rchild=-1;
        }
        while(!sortedNum.empty())
            sortedNum.DeleteMin();
        for(int i=0;i<codeNum;i++)
        {
            HT[i].weight=frequency[i];
            sortedNum.insert(frequency[i],i);
        }
        int sum;
        for(int i=codeNum;i<2*codeNum-1;i++)
        {
            sum=0;
            HT[i].lchild=sortedNum.top().pocessID;
            sum+=sortedNum.top().pority;
            sortedNum.DeleteMin();
            HT[i].rchild=sortedNum.top().pocessID;
            sum+=sortedNum.top().pority;
            sortedNum.DeleteMin();
            HT[i].weight=sum;
            sortedNum.insert(HT[i].weight,i);
        }
    }

    //通过遍历哈夫曼树得到相应的编码规则
    void getCodeRule(int index)
    {
        if(index!=-1)
        {
            if(HT[index].lchild==-1&&HT[index].rchild==-1)
                codeRule[index]=temp;
            temp+='0';
            getCodeRule(HT[index].lchild);
            temp+='1';
            getCodeRule(HT[index].rchild);
            if(!temp.empty())
                temp.erase(temp.size()-1);
        }
        else
        {
            temp.erase(temp.size()-1);
        }
    }

    //该函数通过遍历存储原文章内容的字符串，将相应的ascii码替换为已经得到的对应01编码，并存入成员变量encodeResul中
    void encode()
    {
        encodeResult="";
        for(int i=0;i<Article.size();i++)
        {
            encodeResult+=codeRule[(unsigned char)(Article[i])];
        }
    }

    //该函数是将encode()函数得到的encodeResult通过位运算，每8位01编码存为一个字节的大小，达到压缩的目的
    void encodeBinaryAction()
    {
        encodeBinary="";
        char oneByte;
        int mod=8-(int)encodeResult.size()%8,temp,quotient=(int)encodeResult.size()/8;
        for(int i=0;i<((int)encodeResult.size()-8);i+=8)
        {
            oneByte=char(0xff);
            for(int j=7;j>=0;j--)
            {
                if(encodeResult[i-j+7]=='0') //i+7-j表示依次遍历 i+0,i+1,i+2,……i+7的元素
                    temp=0;
                else
                    temp=1;
                temp=(temp<<j)|(~(1<<j));
                oneByte=char(oneByte&temp);
            }
            encodeBinary+=oneByte;
        }
        oneByte=char(0xff);
        int k=7;
        for(int i=quotient*8;i<encodeResult.size();i++)
        {
            if(encodeResult[i]=='0')
                temp=0;
            else
                temp=1;
            temp=(temp<<k)|(~(1<<k));
            oneByte=char(oneByte&temp);
            k--;
        }
        for(int j=mod-1;j>=0;j--)
        {
            temp=0;
            temp=(temp<<j)|(~(1<<j));
            oneByte=char(oneByte&temp);
        }
        encodeBinary+=oneByte;
        encodeBinary+=(char)mod;
    }

    //该函数通过对01字符串和已经建立的哈夫曼树，得到解码后的原文件内容
    void decode()
    {
        decodeResult="";
        int index=2*codeNum-2;
        for(int i=0;i<input.size();i++)
        {
            if(input[i]=='0')
            {
                if(HT[index].lchild!=-1)
                {
                    index=HT[index].lchild;
                }
                if(HT[index].lchild==-1&&HT[index].rchild==-1)
                {
                    decodeResult+=char(index);
                    index=2*codeNum-2;
                }
            }
            else
            {
                if(HT[index].rchild!=-1)
                    index=HT[index].rchild;
                    if(HT[index].lchild==-1&&HT[index].rchild==-1)
                    {
                        decodeResult+=char(index);
                        index=2*codeNum-2;
                    }
            }
        }
    }

    //该函数通过对得到的压缩后的内容进行还原，将每一位的01信息编程一个01字符，放入到decodeResult中
    void decodeBinary()
    {
        input="";
        char onebyte;
        int temp;
        for(int i=0;i<binary.size()-1;i++)
        {
            onebyte=binary[i];
            for(int j=7;j>=0;j--)
            {
                temp=((1<<j)&onebyte)>>j;
                if(temp==1)
                    input+='1';
                else if(temp==0)
                    input+='0';
            }
        }
        temp=binary[binary.size()-1];
        for(int i=0;i<temp;i++)
            input.erase(input.size()-1);
    }

};

void getContent(int flag,char* path)  //这是统计英语文章中字符出现频率的函数
{
    string filePath;
    Article="";
    binary="";
    ifstream englishArticle;
    if(flag==1)
    {
        cout<<"请输入要压缩处理的文件的路径"<<endl<<">>>";
        cin>>filePath;
        englishArticle.open(filePath.c_str(),ios::binary);
    }
    else if(flag==2)
    {
        cout<<"请输入要解压的文件路径"<<endl<<">>>";
        cin>>filePath;
        englishArticle.open(filePath.c_str(),ios::binary);
    }
    else
        englishArticle.open(path,ios::binary);
    if(!englishArticle.is_open())
    {
        cout<<"打开文件失败,请输入有效路径"<<endl;
        exit(0);
    }
    if(flag==1||flag==3)
    {
        stringstream article;
        article<<englishArticle.rdbuf();  //此处有坑，<<的方向反了
        string test(article.str());
        Article=test;
    }
    else
    {
        int count;
        unsigned char temp;
        englishArticle.read((char*)&count, sizeof(int));
        for(int i=0;i<codeNum;i++)
            character[i]=0;
        for(int i=0;i<count;i++)
        {
            englishArticle.read((char*)&temp, sizeof(char));
            englishArticle.read((char*)&character[(int)temp], sizeof(int));
        }
        englishArticle.close();
        if(flag==2)
        {
            englishArticle.open(filePath.c_str(),ios::binary);
        }
        else
            englishArticle.open(path,ios::binary);
        stringstream article;
        article<<englishArticle.rdbuf();  //此处有坑，<<的方向反了
        string test(article.str());
        binary=test.substr(5*(count+1)-1);
    }
    englishArticle.close();
}

void statistics()
{
    for(int i=0;i<codeNum;i++)
    {
        character[i]=0;
    }
    for(int i=0;i<Article.size();i++)
    {
        character[(unsigned char)(Article[i])]++;
    }
}
//建立了一棵哈夫曼树
huffmanTree hft(character);

void writeCode(int flag,char* path)
{
    string filePath;
    ofstream outCode;
    if(flag==1)
    {
        cout<<"请输入压缩后文件的保存路径"<<endl<<">>>";
        cin>>filePath;
        outCode.open(filePath.c_str(),ios_base::binary);
    }
    else if(flag==2)
    {
        cout<<"请输入解压后文件的保存路径"<<endl<<">>>";
        cin>>filePath;
        outCode.open(filePath.c_str(),ios_base::binary);
    }
    else
        outCode.open(path,ios_base::binary);
    if(!outCode.is_open())
    {
        cout<<"输出文件无法打开"<<endl;
        exit(0);
    }
    if(flag==1||flag==3)
    {
        int count=0;
        for(int i=0;i<codeNum;i++)
        {
            if(character[i]!=0)
                count++;
        }
        outCode.write((char*)&count,sizeof(int));
        for(int i=0;i<codeNum;i++)
        {
            if(character[i]!=0)
            {
                outCode.write((char*)&i,sizeof(char));
                outCode.write((char*)&character[i], sizeof(int));
            }
        }
        outCode<<hft.encodeBinary;
        if(flag<3)
            cout<<"该压缩文件保存为  名称为  "+filePath+"  的文件"<<endl;
        else
            cout<<"该压缩文件保存为  名称为  "<<path<<"  的文件"<<endl;
    }
    else
    {
        outCode<<hft.decodeResult;
        if(flag<3)
            cout<<"解压后的文件保存为  名称为  "+filePath+"  的文件"<<endl;
        else
            cout<<"解压后的文件保存为  名称为  "<<path<<"  的文件"<<endl;
    }
    outCode.close();
}

void communicate()   //与用户交互的界面
{
    a:cout<<"您要压缩文件还是解压文件？(输入1 或 2)"<<endl<<"tips:输入其他任意的字符都可以结束程序"<<endl<<"1、压缩文件"<<endl<<"2、解压文件"<<endl<<">>>";
    int choice;
    cin>>choice;
    switch (choice)
    {
        case 1:
            getContent(1, nullptr);
            statistics();
            hft.establishTree();
            hft.getCodeRule(2*codeNum-2);
            hft.encode();
            hft.encodeBinaryAction();
            writeCode(1, nullptr);
            break;
        case 2:
            getContent(2, nullptr);
            hft.establishTree();
            hft.decodeBinary();
            hft.decode();
            writeCode(2, nullptr);
            break;
        default:
            cout<<"程序正常退出"<<endl;
            exit(0);
    }
    goto a;
}

int main(int argc,char *argv[])
{
    if(argc==1)
        communicate();
    else if(argc==4)
    {
        if(argv[1][0]=='-'&&!argv[1][2])
        {
            if(argv[1][1]=='c')
            {
                getContent(3,argv[2]);
                statistics();
                hft.establishTree();
                hft.getCodeRule(2*codeNum-2);
                hft.encode();
                hft.encodeBinaryAction();
                writeCode(3,argv[3]);
                exit(0);
            }
            else if(argv[1][1]=='d')
            {
                getContent(4,argv[2]);
                hft.establishTree();
                hft.decodeBinary();
                hft.decode();
                writeCode(4,argv[3]);
                exit(0);
            }
        }
    }
    cout<<"usage:-c <input file path> <ouput file path>"<<endl<<"tips:this is to encode your file"<<endl;
    cout<<"usage:-d <input file path> <output file path>"<<endl<<"tips:this is to decode yout file"<<endl;
    return 0;
}