//
// Created by Fitz on 2017/11/29.
//
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define codeNum 256
void getArticle();
void statistics();
int character[codeNum+1];
string Article;

struct CellElement
{
    int pority;   //编码节点的权重
    int pocessID; //编码的ID
};

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

heapmin sortedNum(codeNum+1);

class huffmanTree
{
public:
    int * frequency,root;
    string codeRule[codeNum+1],temp,encodeResult,decodeResult,encodeBinary;
    cellElement HT[2*codeNum-1];
    huffmanTree(int *temp)
    {
        frequency=temp;
    }

    void establishTree()
    {
        //初始化小根堆
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
        root=sortedNum.top().pocessID;
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
            if(temp.size()!=0)
                temp.erase(temp.size()-1);
        }
        else
        {
            temp.erase(temp.size()-1);
        }
    }

    void encode()
    {
        for(int i=0;i<Article.size();i++)
        {
            encodeResult+=codeRule[(unsigned char)(Article[i])];
        }
        cout<<"test"<<endl;
    }

    void encodeBinaryAction()
    {
        char oneByte;
        int mod=(int)encodeResult.size()%8,temp,quotient=(int)encodeResult.size()/8;
        for(int i=0;i<encodeResult.size();i+=8)
        {
            oneByte=0xff;
            for(int j=7;j>=0;j--)
            {
                if(encodeResult[i]=='0')
                    temp=0;
                else
                    temp=1;
                temp=temp<<j|((unsigned(1))>>(8-j));
                oneByte=oneByte&temp;
            }
            encodeBinary+=oneByte;
        }
        oneByte=char(0xff);
        for(int i=quotient*8;i<encodeResult.size();i++)
        {
            for(int j=7;j>=0;j--)
            {
                if(j>=mod)
                {
                    if(encodeResult[i]=='0')
                        temp=0;
                    else
                        temp=1;
                }
                else
                    temp=0;
                temp=temp<<j|((unsigned(1))>>(8-j));
                oneByte=char(oneByte&temp);
            }
        }
        encodeBinary+=oneByte;
        encodeBinary+=(char)mod;
    }

    void decode(string input)
    {
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

};

void getArticle()  //这是统计英语文章中字符出现频率的函数
{
    string filePath;
    cout<<"请输入要压缩处理的英文文章的路径"<<endl;
    cin>>filePath;
    ifstream englishArticle(filePath,ios::binary);
    if(!englishArticle.is_open())
    {
        cout<<"打开文件失败,请输入有效路径"<<endl;
        exit(0);
    }
    stringstream article;
    article<<englishArticle.rdbuf();  //此处有坑，<<的方向反了
    string test(article.str());
    Article=test;
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

huffmanTree hft(character);

void writeCode(int flag)
{
    ofstream outCode;
    outCode.open("data.dat",ios::binary);
    if(!outCode.is_open())
    {
        cout<<"输出文件无法打开"<<endl;
        exit(0);
    }
    if(flag==1)
        outCode<<hft.encodeResult<<endl;
    else if(flag==2)
        outCode<<hft.decodeResult;
    outCode.close();
}

int main()
{
    getArticle();
    statistics();
    hft.establishTree();
    hft.getCodeRule(2*codeNum-2);
    hft.encode();
    //hft.encodeBinaryAction();
    writeCode(1);
    getArticle();
    hft.decode(Article);
    writeCode(2);
    return 0;
}
