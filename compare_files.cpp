#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    string str1, str2;
    ifstream file1, file2;
    int row=0;
    if(argc == 3)
    {
        file1.open(argv[1]);
        file2.open(argv[2]);
    }
    else
    {
        cout<<"help:usage: cmp [file 1] [file 2]"<<endl;
        return 0;
    }

    if(!file1.is_open() || !file2.is_open())
    {
        cout<<"Open file error!"<<endl;
        return 0;
    }

    while(!file1.eof() && !file2.eof())
    {
        row++;
        getline(file1,str1);
        getline(file2,str2);
        if(str1 == str2)
            continue;
        else
        {
            cout<<"some characters are different in this line:"<<row<<endl;
            file1.close();
            file2.close();
            return 0;
        }
    }

    if(!file1.eof() || !file2.eof())
        cout<<argv[1]<<" and "<<argv[2]<<"have different line number"<<endl;
    else
        cout<<"two files are nothing different"<<endl;
    return 0;
}