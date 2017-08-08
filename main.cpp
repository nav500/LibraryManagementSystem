#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class student
{
    int sno, cls;               //Scholar number, student's class
    char name[30];            //Student's name
public:
    void enter();
    void show();
    int get_sno();
    void modify();
};

void student::enter()
{
    cout << "Enter scholar number:";
    cin >> sno;
    cout << "enter the class:";
    cin >> cls;
    cin.get();
    cout << "enter the name:";
    cin.getline(name,30);
}
void student::show()
{
    cout << "scholar number:" << sno << endl;
    cout << "class:" << cls << endl;
    cout << "name:" << name << endl;
}
int student::get_sno()
{
    return sno;
}
void student::modify()
{
    show();
    enter();
}


class bk_info               // class for book information
{
    int book_no;
    char bk_name[30], athr_name[30];     // book name and author name
    int book_cnt;                  // no. of particular book in library
public:
    void enter();
    int get_no();
    void show();
    void modify();
};
void bk_info::enter()
{
    cout << "enter book no.:";
    cin >> book_no;
    cin.get();
    cout << "enter book name:";
    cin.getline(bk_name,30);
    cout << "enter author name:";
    cin.getline(athr_name,30);
}
int bk_info::get_no()
{
    return book_no;
}
void bk_info::show()
{
    cout << "book number:" << book_no << endl;
    cout << "book name:" << bk_name << endl;
    cout << "author name:" << athr_name <<endl;
}
void bk_info::modify()
{
    show();
    enter();
}


student s;
bk_info b;
ifstream fin_st,fin_bk,fin;
fstream fst,fbk,fout;

void add_st()
{
    fst.open("stu.txt",ios::out|ios::app);
    s.enter();
    fst.write((char*)&s,sizeof(student));
    fst.close();
}
void add_bk()
{
    fbk.open("book.txt",ios::out|ios::app);
    b.enter();
    fbk.write((char*)&b,sizeof(bk_info));
    fbk.close();
}
void show_st(int n)
{
    fin_st.open("stu.txt",ios::in);
    while(fin_st.read((char*)&s,sizeof(student)))
    {
        if(s.get_sno() == n)
        {
            s.show();
            break;
        }
    }
    fin_st.close();
}
void show_bk(int n)
{
    fin_bk.open("book.txt",ios::in);
    while(fin_bk.read((char*)&b,sizeof(b)))
    {
        if(b.get_no() == n)
        {
            b.show();
            break;
        }
    }
    fin_bk.close();
}
int check(int n)
{
    int ch_sno, ch_bk_no;
    int cnt = 0;
    fin.open("issue.txt",ios::in);
    fin.seekg(0);
    while(fin.eof() == 0)
    {
        fin >> ch_sno;
        fin.get();
        fin >> ch_bk_no;
        fin.get();
        if(fin.eof() == 0)
        if(n == ch_sno)
            cnt++;
    }
    fin.close();
    if(cnt == 3)
        return 0;
    else
        return 1;
}

void issue()
{
    int sno, bk_no;
    cout << "enter scholar number:";
    cin >> sno;
    if(check(sno))
    {
    fout.open("issue.txt",ios::out|ios::app);
    fout << sno;
    fout << ":";
    cout << "enter book no.:";
    cin >> bk_no;
    fout << bk_no;
    fout << endl;
    cout << endl << "successful" << endl;
    fout.close();
    }
    else
    {
        cout << "sorry! it exceeds the limit" << endl;
    }
}
void deposit(int p,int q)
{
    int sno, bk_no;
    fin.open("issue.txt",ios::in);
    fout.open("temp.txt",ios::out|ios::app);
    while(fin >> sno && fin >> bk_no)
    {
        if (sno == p && bk_no == q)
        {
            show_st(p);
            show_bk(q);
        }
        else
        {
            fout << sno;
            fout << ":";
            fout << bk_no;
            fout << endl;
        }
    }
    remove("issue.txt");
    rename("temp.txt","issue.txt");
}
void st_modify(int n)
{
    long pos;
    fin_st.open("stu.txt",ios::in);
    fst.open("stu.txt",ios::out|ios::app);
    while(fin_st.read((char*)&s,sizeof(s)))
    {
        pos = fin_st.tellg();
        if(n == s.get_sno())
        {
            s.modify();
            fst.seekp(pos);
            fst.write((char*)&s,sizeof(student));
            break;
        }
    }
    fin_st.close();
    fst.close();
}
void bk_modify(int n)
{
    int pos;
    fin_bk.open("book.txt",ios::in);
    fbk.open("book.txt",ios::out|ios::app);
    while(fin_bk.read((char*)&b,sizeof(bk_info)))
    {
        pos = fin_bk.tellg();
        if(n == b.get_no())
        {
            b.modify();
            fbk.seekp(pos);
            fbk.write((char*)&b,sizeof(bk_info));
            break;
        }
    }
    fin_bk.close();
    fbk.close();
}

int main()
{
    int sno, bk_no;
    int ch, a_ch;
    char opt = 'y';
    do
    {
    cout << " Main Menu:" << endl;
    cout << "1. Book Issue:" << endl;
    cout << "2. Book Deposit:" << endl;
    cout << "3. Administrator Main Menu:" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice:";
    cin >> ch;
    switch(ch)
    {
        case 1:
            {
                issue();
                break;
            }
        case 2:
            {
                cout << "enter scholar number:";
                cin >> sno;
                cout << "enter book number:";
                cin >> bk_no;
                deposit(sno,bk_no);
                break;
            }
        case 3:
            {
            cout << "Administrator Menu:" << endl;
            cout << "1. Display specific student record" << endl;
            cout << "2. Add student details" << endl;
            cout << "3. Modify Student Details" << endl;
            cout << "4. Add book" << endl;
            cout << "5. Display Specific Book" << endl;
            cout << "6. Modify Book Details" << endl;
            cout << "7. Back To Main Menu" << endl;
            cout << "Enter your choice:";
            cin >> a_ch;
            switch(a_ch)
            {
                case 1:
                    {
                    cout << "enter scholar number:";
                    cin >> sno;
                    show_st(sno);
                    break;
                    }
                case 2:
                    {
                     add_st();
                     break;
                    }
                case 3:
                    {
                        cout << "enter scholar number:";
                        cin >> sno;
                        st_modify(sno);
                        break;
                    }
                case 4:
                    {
                        add_bk();
                        break;
                    }
                case 5:
                    {
                        cout << "add book number:";
                        cin >> bk_no;
                        show_bk(bk_no);
                        break;
                    }
                case 6:
                    {
                        cout << "enter book number:";
                        cin >> bk_no;
                        bk_modify(bk_no);
                        break;
                    }
                case 7:
                    {
                        continue;
                    }
            }
            break;
            }
        case 4:
            {
                opt = 'n';
            }
    }
    if (opt == 'n');
    else
    {
    cout << "do you want to continue:";
    cin >> opt;
    }
    }while(opt == 'y' || opt == 'Y');
    cin.get();
    return 0;
}

