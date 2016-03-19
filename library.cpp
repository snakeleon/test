//ͼ��ݹ���ϵͳ For Dos
//Compile by Borland C++ 5.02
//�޴��ڽ���Ŀ���̨����
//Marked by ���Ĥ�϶�g  QQ:26481904


#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const int Maxr=30;//��������
const int Maxb=100;//���������
const int Maxbor=2;//����������2��


class Reader
{
    friend class Book;
    int tag;//����ɾ�����
    int no;//���ߺ�
    char name[20];//������
    int borbook[Maxbor];//������
public:
    char *getname()
    {
        return name;    //��ȡ������
    }
    int gettag()
    {
        return tag;    //��ȡɾ�����
    }
    int getno()
    {
        return no;    //��ȡ���ߺ�
    }
    void setname (char na[])//���ö�����
    {
        strcpy (name,na);
    }
    void delbook()
    {
        tag=1;    //����ɾ�����1
    }
    void addreader (int n,char *na)//���Ӷ���
    {
        tag=0;
        no=n;
        strcpy(name,na);
        for (int i=0; i<Maxbor; i++)
            borbook[i]=0;
    }
    void borrowbook(int bookid)//�������
    {
        int k=0;
        for (int i=0; i<Maxbor; i++)
        {
            if (borbook[i]==0)
            {
                borbook[i]=bookid;
                k++;
                cout<<"����ɹ�!"<<endl;
                break;
            }
        }
        if (k==0)cout<<"���ѽ蹻2����,�޷��ڽ�!"<<endl;
    }
    int retbook(int bookid)//�������
    {
        for (int i=0; i<Maxbor; i++)
        {
            if (borbook[i]==bookid)
            {
                borbook[i]=0;
                cout<<"����ɹ�!"<<endl;
                return 1;
            }
        }
        return 0;
    }
    void disp()//��ʾ��������Ϣ
    {
        if (gettag()==0)
        {
            cout<<setw(15)<<no<<setw(15)<<name<<"������:[";
            for (int i=0; i<Maxbor; i++)
                if (borbook[i]!=0)
                    cout<<borbook[i]<<"|";
            cout<<"]"<<endl;
        }
    }
};


/*....................................................................................*/


class Book//ͼ����
{
    int tag;//ͼ��ɾ��
    int no;//ͼ���
    char name[20];//����
    int onshelf;//����ͼ���Ƿ��ڼ�
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
        tag=1;    //ɾ��ͼ��
    }
    void addbook(int n,char *na)// �������
    {
        tag=0;
        no=n;
        strcpy(name,na);
        onshelf=1;
    }
    int borrowbook()//�������
    {
        if (onshelf==1)
        {
            onshelf=0;
            return 1;
        }
        return 0;
    }
    void retbook()//�������
    {
        onshelf=1;
    }
    void disp()//��ʾͼ����Ϣ
    {
        cout<<setw(6)<<"ͼ����Ϣ"<<setw(6)<<no<<setw(15)<<name<<setw(15)<<(onshelf==1?"�����":"�ѽ��")<<endl;
    }
};



/*....................................................................................*/



class RDatabase//������Ϣ��
{
    int top;//���߼�¼ָ��
    Reader read[Maxr];
public:
    RDatabase()
    {
        top=-1;
        fstream file;
        file.open("reader.txt",ios::in|ios::binary);//�Ӵ��̵�reader.txt�ļ��ж�ȡ������Ϣ
        while (1)
        {
            if (!file) break;
            top++;
            file.read((char *)&read[top],sizeof(read[top]));
        }
        file.close();
        top++;
    }
    int addreader(int n,char *na)//��Ӷ���
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
    ~RDatabase()//��������Ϣд��reader.txt
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
        cout<<"���߹���:"<<endl;
        cout<<"1:��������"<<endl;
        cout<<"2:���Ķ�����"<<endl;
        cout<<"3:ɾ������"<<endl;
        cout<<"4:���Ҷ���"<<endl;
        cout<<"5:��ʾ���ж���"<<endl;
        cout<<"0:�˳�"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"�������¶��ߵı��"<<endl;
            cin>>readerid;
            cout<<"�������¶��ߵ�����:"<<endl;
            cin>>rname;
            addreader(readerid,rname);
            break;
        case 2:
            cout<<"��������Ķ��߱��:"<<endl;
            cin>>readerid;
            r=query(readerid);
            if (r==NULL)
            {
                cout<<"�Բ���!���ı������,���ʵ��������"<<endl;
                break;
            }
            cout<<"���������������:"<<endl;
            cin>>rname;
            r->setname(rname);
            break;
        case 3:
            cout<<"!!!��ɾ��һ��������?��������ɾ���Ķ��߱��:"<<endl;
            cin>>readerid;
            r=query(readerid);
            if (r==NULL)
            {
                cout<<"�ö��߲�����,����ɾ��,���ʵ���ٲ���"<<endl;
                break;
            }
            r->delbook();
            break;
        case 4:
            cout<<"������������ҵĶ��߱��:";
            cin>>readerid;
            r=query(readerid);
            if (r==NULL)
            {
                cout<<"�ö��߲�����,�޷�ȡ�������Ϣ:";
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



class BDatabase//ͼ��������
{
    int top;
    Book book[Maxb];
public:
    BDatabase()//���캯��
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
    int addbook(int n,char *na)// ���ͼ��,��ǰ�Ȳ���
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
    Book * query(int bookid)//����ͼ��
    {
        for (int i=0; i<top; i++)
            if (book[i].getno()==bookid&&book[i].gettag()==0)
                return &book[i];
        return NULL;
    }
    void bookdata();//ͼ��ά��
    void disp()
    {
        for (int i=0; i<top; i++)
            if (book[i].gettag()==0)
                book[i].disp();
    }
    ~BDatabase()//��������,��book[i]д���ļ�
    {
        fstream file("book.txt",ios::out|ios::binary);
        for (int i=0; i<top; i++)
            file.write((char *)&book[i],sizeof(book[i]));
        file.close();
    }
};


/*....................................................................................*/



void BDatabase::bookdata()//����˵��
{
    int choice=1;
    char bname[40];
    int bookid;
    Book *b;
    while (choice!=0)
    {
        cout<<"ͼ�����:"<<endl;
        cout<<"1:����ͼ��"<<endl;
        cout<<"2:����ͼ����"<<endl;
        cout<<"3:ɾ��ͼ��"<<endl;
        cout<<"4:����ͼ��"<<endl;
        cout<<"5:��ʾ����ͼ��"<<endl;
        cout<<"0:�˳�"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"������Ҫ�¼�ͼ����:"<<endl;
            cin>>bookid;
            cout<<"�����µ�ͼ����:"<<endl;
            cin>>bname;
            addbook(bookid,bname);
            break;
        case 2:
            cout<<"����ԭͼ����:"<<endl;
            cin>>bookid;
            b=query(bookid);
            if (b==NULL)
            {
                cout<<"���鲻����"<<endl;
                break;
            }
            cout<<"�����µ�����:"<<endl;
            cin>>bname;
            b->setname(bname);
            break;
        case 3:
            cout<<"����ͼ����:"<<endl;
            cin>>bookid;
            b=query(bookid);
            if (b==NULL)
            {
                cout<<"��ͼ�鲻����"<<endl;
                break;
            }
            b->delbook();
            break;
        case 4:
            cout<<"����ͼ����:"<<endl;
            cin>>bookid;
            b=query(bookid);
            if (b==NULL)
            {
                cout<<"��ͼ�鲻����"<<endl;
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
        cout<<"1:����:"<<"\nִ�ж��߽���Ĳ���"<<endl;
        cout<<"2:����:"<<"\nִ�ж��߻���Ĳ���"<<endl;
        cout<<"3:ͼ�����:"<<"\n��ͼ���������,����,ɾ��,����,��ʾ�Ĳ���"<<endl;
        cout<<"4:���߹���:"<<"\n�Զ��߽�������,����,ɾ��,����,��ʾ�Ĳ���"<<endl;
        cout<<"0:�뿪:"<<"\n�˳�����������һ��"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"�����߱��:"<<endl;
            cin>>readerid;
            cout<<"ͼ����:"<<endl;
            cin>>bookid;
            r=ReaderDB.query(readerid);
            b=BookDB.query(bookid);
            if (r==NULL)
            {
                cout<<"���߲�����,���ܽ���:"<<endl;
                break;
            }
            if (b==NULL)
            {
                cout<<"������ͼ��.���ܽ���"<<endl;
                break;
            }
            if (b->borrowbook()==0)
            {
                cout<<"ͼ���ѽ��"<<endl;
                break;
            }
            r->borrowbook(b->getno());
            break;
        case 2:
            cout<<"�����߱��"<<endl;
            cin>>readerid;
            cout<<"ͼ����"<<endl;
            cin>>bookid;
            r=ReaderDB.query(readerid);
            if (r==NULL)
            {
                cout<<"�����ڶ���,���ܻ���"<<endl;
                break;
            }
            b=BookDB.query(bookid);
            if (b==NULL)
            {
                cout<<"������ͼ��,�޷�����"<<endl;
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
