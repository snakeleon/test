//图书馆管理系统 For Dos
//Compile by Borland C++ 5.02
//无窗口介面的控制台程序
//Marked by じ心の隙間  QQ:26481904


#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const int Maxr=30;//最大读者数
const int Maxb=100;//书库最大存书
const int Maxbor=2;//读者最大借书2本


class Reader
{
    friend class Book;
    int tag;//读者删除标记
    int no;//读者号
    char name[20];//读者名
    int borbook[Maxbor];//所借书
public:
    char *getname()
    {
        return name;    //获取读者名
    }
    int gettag()
    {
        return tag;    //获取删除标记
    }
    int getno()
    {
        return no;    //获取读者号
    }
    void setname (char na[])//设置读者名
    {
        strcpy (name,na);
    }
    void delbook()
    {
        tag=1;    //设置删除标记1
    }
    void addreader (int n,char *na)//增加读者
    {
        tag=0;
        no=n;
        strcpy(name,na);
        for (int i=0; i<Maxbor; i++)
            borbook[i]=0;
    }
    void borrowbook(int bookid)//借书操作
    {
        int k=0;
        for (int i=0; i<Maxbor; i++)
        {
            if (borbook[i]==0)
            {
                borbook[i]=bookid;
                k++;
                cout<<"借书成功!"<<endl;
                break;
            }
        }
        if (k==0)cout<<"你已借够2本书,无法在借!"<<endl;
    }
    int retbook(int bookid)//还书操作
    {
        for (int i=0; i<Maxbor; i++)
        {
            if (borbook[i]==bookid)
            {
                borbook[i]=0;
                cout<<"还书成功!"<<endl;
                return 1;
            }
        }
        return 0;
    }
    void disp()//显示借书者信息
    {
        if (gettag()==0)
        {
            cout<<setw(15)<<no<<setw(15)<<name<<"借书编号:[";
            for (int i=0; i<Maxbor; i++)
                if (borbook[i]!=0)
                    cout<<borbook[i]<<"|";
            cout<<"]"<<endl;
        }
    }
};


/*....................................................................................*/


class Book//图书类
{
    int tag;//图书删除
    int no;//图书号
    char name[20];//书名
    int onshelf;//查找图书是否在架
public:
    char *getname()
    {
        return name ;    //
    }
    int getno()
    {
        return no;    //
    }
    int gettag()
    {
        return tag;    //
    }
    void setname(char na[])//
    {
        strcpy(name,na);
    }
    void delbook()
    {
        tag=1;    //删除图书
    }
    void addbook(int n,char *na)// 加书操作
    {
        tag=0;
        no=n;
        strcpy(name,na);
        onshelf=1;
    }
    int borrowbook()//借书操作
    {
        if (onshelf==1)
        {
            onshelf=0;
            return 1;
        }
        return 0;
    }
    void retbook()//还书操作
    {
        onshelf=1;
    }
    void disp()//显示图书信息
    {
        cout<<setw(6)<<"图书信息"<<setw(6)<<no<<setw(15)<<name<<setw(15)<<(onshelf==1?"在书架":"已借出")<<endl;
    }
};



/*....................................................................................*/



class RDatabase//读者信息库
{
    int top;//读者记录指针
    Reader read[Maxr];
public:
    RDatabase()
    {
        top=-1;
        fstream file;
        file.open("reader.txt",ios::in|ios::binary);//从磁盘的reader.txt文件中读取读者信息
        while (1)
        {
            if (!file) break;
            top++;
            file.read((char *)&read[top],sizeof(read[top]));
        }
        file.close();
        top++;
    }
    int addreader(int n,char *na)//添加读者
    {
        Reader *p=query(n);
        if (p==NULL)
        {
            read[top].addreader(n,na);
            top++;
            return 1;
        }
        return 0;
    }
    Reader * query (int readerid)
    {
        for (int i=0; i<top; i++)
            if (read[i].getno()==readerid&&read[i].gettag()==0)
            {
                return &read[i];
            }
        return NULL;
    }
    void disp()
    {
        for (int i=1; i<top; i++)
            read[i].disp();
    }
    void readerdata();
    ~RDatabase()//将读者信息写入reader.txt
    {
        fstream file;
        file.open("reader.txt",ios::out|ios::binary);
        for (int i=0; i<top; i++)
            file.write((char *)&read[i],sizeof(read[i]));
        file.close();
    }
};



/*....................................................................................*/



void RDatabase::readerdata()
{
    int choice=1;
    char rname[20];
    int readerid;
    Reader *r;
    while (choice!=0)
    {
        cout<<"读者管理:"<<endl;
        cout<<"1:新增读者"<<endl;
        cout<<"2:更改读者名"<<endl;
        cout<<"3:删除读者"<<endl;
        cout<<"4:查找读者"<<endl;
        cout<<"5:显示所有读者"<<endl;
        cout<<"0:退出"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"请输入新读者的编号"<<endl;
            cin>>readerid;
            cout<<"请输入新读者的姓名:"<<endl;
            cin>>rname;
            addreader(readerid,rname);
            break;
        case 2:
            cout<<"请输入你的读者编号:"<<endl;
            cin>>readerid;
            r=query(readerid);
            if (r==NULL)
            {
                cout<<"对不起!您的编号有误,请核实后在再输"<<endl;
                break;
            }
            cout<<"请输入你的新姓名:"<<endl;
            cin>>rname;
            r->setname(rname);
            break;
        case 3:
            cout<<"!!!想删除一个读者吗?输入你想删除的读者编号:"<<endl;
            cin>>readerid;
            r=query(readerid);
            if (r==NULL)
            {
                cout<<"该读者不存在,无须删除,请核实后再操作"<<endl;
                break;
            }
            r->delbook();
            break;
        case 4:
            cout<<"请输入你想查找的读者编号:";
            cin>>readerid;
            r=query(readerid);
            if (r==NULL)
            {
                cout<<"该读者不存在,无法取得相关信息:";
                break;
            }
            r->disp();
            break;
        case 5:
            disp();
            break;
        }
    }
};



/*....................................................................................*/



class BDatabase//图书库管理类
{
    int top;
    Book book[Maxb];
public:
    BDatabase()//构造函数
    {
        top=-1;
        fstream file;
        file.open("book.txt",ios::in|ios::binary);
        while (1)
        {
            if (!file) break;
            top++;
            file.read((char*)&book[top],sizeof(book[top]));
        }
        file.close();
        top++;
    }
    int addbook(int n,char *na)// 添加图书,加前先查找
    {
        Book *p=query(n);
        if (p==NULL)
        {
            book[top].addbook(n,na);
            top++;
            return 1;
        }
        return 0;
    }
    Book * query(int bookid)//查找图书
    {
        for (int i=0; i<top; i++)
            if (book[i].getno()==bookid&&book[i].gettag()==0)
                return &book[i];
        return NULL;
    }
    void bookdata();//图书维护
    void disp()
    {
        for (int i=0; i<top; i++)
            if (book[i].gettag()==0)
                book[i].disp();
    }
    ~BDatabase()//析构函数,将book[i]写入文件
    {
        fstream file("book.txt",ios::out|ios::binary);
        for (int i=0; i<top; i++)
            file.write((char *)&book[i],sizeof(book[i]));
        file.close();
    }
};


/*....................................................................................*/



void BDatabase::bookdata()//函数说明
{
    int choice=1;
    char bname[40];
    int bookid;
    Book *b;
    while (choice!=0)
    {
        cout<<"图书管理:"<<endl;
        cout<<"1:新增图书"<<endl;
        cout<<"2:更改图书名"<<endl;
        cout<<"3:删除图书"<<endl;
        cout<<"4:查找图书"<<endl;
        cout<<"5:显示所有图书"<<endl;
        cout<<"0:退出"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"输入你要新加图书编号:"<<endl;
            cin>>bookid;
            cout<<"输入新的图书名:"<<endl;
            cin>>bname;
            addbook(bookid,bname);
            break;
        case 2:
            cout<<"输入原图书编号:"<<endl;
            cin>>bookid;
            b=query(bookid);
            if (b==NULL)
            {
                cout<<"该书不存在"<<endl;
                break;
            }
            cout<<"输入新的书名:"<<endl;
            cin>>bname;
            b->setname(bname);
            break;
        case 3:
            cout<<"输入图书编号:"<<endl;
            cin>>bookid;
            b=query(bookid);
            if (b==NULL)
            {
                cout<<"该图书不存在"<<endl;
                break;
            }
            b->delbook();
            break;
        case 4:
            cout<<"输入图书编号:"<<endl;
            cin>>bookid;
            b=query(bookid);
            if (b==NULL)
            {
                cout<<"该图书不存在"<<endl;
                break;
            }
            b->disp();
            break;
        case 5:
            disp();
            break;
        }
    }
};


/*....................................................................................*/



int main()
{
    int choice=1;
    int bookid;
    int readerid;
    RDatabase ReaderDB;
    Reader *r;
    BDatabase BookDB;
    Book *b;
    while (choice!=0)
    {
        cout<<"1:借书:"<<"\n执行读者借书的操作"<<endl;
        cout<<"2:还书:"<<"\n执行读者还书的操作"<<endl;
        cout<<"3:图书管理:"<<"\n对图书进行新增,更改,删除,查找,显示的操作"<<endl;
        cout<<"4:读者管理:"<<"\n对读者进行新增,更改,删除,查找,显示的操作"<<endl;
        cout<<"0:离开:"<<"\n退出本操作到上一层"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"借书者编号:"<<endl;
            cin>>readerid;
            cout<<"图书编号:"<<endl;
            cin>>bookid;
            r=ReaderDB.query(readerid);
            b=BookDB.query(bookid);
            if (r==NULL)
            {
                cout<<"读者不存在,不能借书:"<<endl;
                break;
            }
            if (b==NULL)
            {
                cout<<"不存在图书.不能借书"<<endl;
                break;
            }
            if (b->borrowbook()==0)
            {
                cout<<"图书已借出"<<endl;
                break;
            }
            r->borrowbook(b->getno());
            break;
        case 2:
            cout<<"还书者编号"<<endl;
            cin>>readerid;
            cout<<"图书编号"<<endl;
            cin>>bookid;
            r=ReaderDB.query(readerid);
            if (r==NULL)
            {
                cout<<"不存在读者,不能还书"<<endl;
                break;
            }
            b=BookDB.query(bookid);
            if (b==NULL)
            {
                cout<<"不存在图书,无法还书"<<endl;
                break;
            }
            b->retbook();
            r->retbook(b->getno());
            break;
        case 3:
            BookDB.bookdata();
            break;
        case 4:
            ReaderDB.readerdata();
            break;
        }
    }
    return 0;
}
