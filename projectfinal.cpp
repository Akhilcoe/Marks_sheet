#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class DOB
{  
    int date;
    int month;
    int year;
    public:
    DOB(int date=0,int month=0,int year=0)
    {
        this->date=date;
        this->month=month;
        this->year=year;

    }
    void display()
    {
        cout<<"Date = "<<date<<"-"<<month<<"-"<<year<<"\n";
    }
};
class student
{
    public:
    DOB d;
    int rollno;
    char name[20];
    char phone[20];
    char classes[20];
    char fathers_name[20];
    student()
    {
        rollno=0;
        strcpy(name,"");
        strcpy(phone,"");
        strcpy(classes,"");
        strcpy(fathers_name,"");
        d=DOB(0,0,0);

    }
    student(int rollno,char name[],char phone[],char classes[],char fathers_name[],DOB d)
    {
        this->rollno=rollno;
        strcpy(this->name,name);
        strcpy(this->phone,phone);
        strcpy(this->classes,classes);
        strcpy(this->fathers_name,fathers_name);
        this->d=d;

    }
    void display()
    {
        cout<<"\n";
        cout<<"\nStudent's Rollno:"         <<rollno;
        cout<<"\nStudent's Name:"           <<name;
        cout<<"\nStudent's Phone Number:"     <<phone;
        cout<<"\nStudent's Class:"           <<classes;
        cout<<"\nstudents Father's name:"     <<fathers_name<<"\n";
        d.display();
    }
};

int Search(int roll)
{
   student s;
    fstream file("myproject.dat",ios::in|ios::binary);
    int i=0;
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollno==roll)
        {
            i=1;
            cout<<"\nEntry found!\n";
            break;
        }
    }
    if(i==0)
    cout<<"\nEntry not found\n";
    file.close();
    return i;
}
student getInfo(int s=0)
{
    int roll;
    cout<<"Enter Roll number:";
    cin>>roll;
    if(Search(roll)==1&&s==0)
    {
        cout<<"\nRoll number already exits Sorry Enter valid information\n";
        student s1;
        return s1;
        
    }
    cout<<"Enter Name:";
    char name[20];
    // strcpy(name,"Test");
    cin>>name;
    cout<<"Enter Father's Name:";
    char fathers_name[20];
    // strcpy(fathers_name,"Test g");
    cin>>fathers_name;
    cout<<"Enter Phone number:";
    char phone[20];
    // strcpy(phone,"1234567");
    cin>>phone;
    cout<<"Enter class:";
    char classes[20];
    cin>>classes;
    int dd,mm,yy;
    cout<<"Enter DOB(dd/mm/yy):";
    cin>>dd>>mm>>yy;
    DOB d(dd,mm,yy);
    student s1(roll,name,phone,classes,fathers_name,d);
    return s1;
}

void writetofile()
{
    student s=getInfo();
    if(s.rollno!=0)
    {
        fstream file("myproject.dat",ios::out|ios::app|ios::binary);
        file.write((char*)&s,sizeof(s));
        file.close();
    }   
}
void readfromfile()
{
    student s;
    fstream file("myproject.dat",ios::in|ios::binary);
    // cout<<"Inside Reading";
    while(file.read((char*)&s,sizeof(s)))
    {
        // cout<<"Hello\n";
        s.display();
    }
    file.close();
}
void search(int roll)
{
   student s;
    fstream file("myproject.dat",ios::in|ios::binary);
    // cout<<"Inside Reading";
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollno==roll)
        // cout<<"Hello\n";
        s.display();
    }
    file.close();
}
void deletefromfile(int roll)
{
    student s;
    fstream file("myproject.dat",ios::in|ios::binary);
    ofstream fileo("myprojectcopy.dat",ios::out|ios::binary);
    // cout<<"Inside Reading";
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollno!=roll)
            fileo.write((char*)&s,sizeof(s));
        // cout<<"Hello\n";
        // s.display();
    }
    fileo.close();
    file.close();
    remove("myproject.dat");
    rename("myprojectcopy.dat","myproject.dat");
}


void updatetofile(student s1)
{
    student s;
    fstream file("myproject.dat",ios::in|ios::binary);
    ofstream fileo("myprojectcopy.dat",ios::out|ios::binary);
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s1.rollno!=s.rollno)
            fileo.write((char*)&s,sizeof(s));
        else
            fileo.write((char*)&s1,sizeof(s1));
    }
    fileo.close();
    file.close();
    remove("myproject.dat");
    rename("myprojectcopy.dat","myproject.dat");
}
void copyfile()
{
    student s;
    fstream file("myproject.dat",ios::in|ios::binary);
    ofstream fileo("myprojectcopy.dat",ios::out|ios::binary);
    while(file.read((char*)&s,sizeof(s)))
    {
        fileo.write((char*)&s,sizeof(s));
        s.display();
    }
    fileo.close();
    file.close();
}
void getStudentMenu()
{
    char choice;
    do
    {
        cout<<"\n........................\n";
    cout<<"\n1.Add\n";
    cout<<"2.Delete\n";
    cout<<"3.Show All Data\n";
    cout<<"4.Edit\n";
    cout<<"5.Show Desired Entry\n";
    cout<<"6.Search Entry\n";
    cout<<"7.Exit\n";
        cout<<"\n........................\n";
    int c;
    cout<<"Enter Your Choice:";
    cin>>c;
    switch(c)
    {
        case 1:
           writetofile();
           break;
        case 2:
        {
            int roll;
            cout<<"\nEnter roll which u want to delete:";
            cin>>roll;
            int x=Search(roll);
            if(x==0)
                cout<<"\nStudent is not available\n";
            else
                deletefromfile(roll);
            break;
        }
        case 3:
        {
            readfromfile();
            break; 
        }
        case 4:
        {
            student s=getInfo(1);
            updatetofile(s);
            cout<<"\nUpdated Successfully!";
            break;
        }
        case 5:
        {
            int roll;
            cout<<"\nEnter roll which u want to search:";
            cin>>roll;
            search(roll);
            break;            
        }
        case 6:
        {
            int roll;
            cout<<"\nEnter roll which u want to search:";
            cin>>roll;
            Search(roll);
            break;            
        }        
        case 7:
        {
            cout<<"THANK YOU!";
            break;
        }
    }
    cout<<"\nDo you want to continue:";
    cin>>choice;
    }while(choice=='y'||choice=='Y');
}
class Marks
{
public:
    int marks[5];
    int roll;
    Marks()
    {
        roll=0;
        for (int i = 0; i < 5; i++)
        {
            marks[i] = 0;
        }
    }
    Marks(int roll,int marks[])
    {
        this->roll=roll;
        for (int i = 0; i < 5; i++)
        {
            this->marks[i] = marks[i];
        }
    }
    int sum()
    {
        int s = 0;
        for (int i = 0; i < 5; i++)
        {
            s += marks[i];
        }
        return s;
    }
    float per(int s)
    {
        float p = (float)s / 5;
        return p;
    }
    char Grade(float p)
    {
        char grade;
        if(p>=90)
        grade='A';
        else if(p<90 && p>=80)
        grade='B';
        else if(p<80 && p>=65)
        grade='C';
        else if(p<65 && p>=33)
        grade='D'; 
        else
        grade='F';
        return grade;
    }
    void display()
    {
        cout<<"\n Student Marks Details \n";
        string sub[]={"Eng","Hindi","Punjabi","Math","Sci"};
        // cout<<"\n";
        cout<<"\nRoll No.:"<<roll;
        cout << "\nMarks Record:";
        for (int i = 0; i < 5; i++)
        {
            cout << '\n' << sub[i] << ": " << marks[i];
        }
       int totalMarks = sum();
        cout <<"\nTotal marks obtained are: " << totalMarks ;
        float percentage = per(totalMarks);
        cout << "\nPercentage Obtained: " << percentage;
        char grade=Grade(percentage);
        cout << "\nGrade: " << grade<<"\n";
    }
};

int search_roll(int roll)
{
    int i=0;
    Marks m;
    fstream file("marksinfo.dat",ios::in|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
        if(m.roll==roll)
        {
            i=1;
            cout<<"Entry Found!";
            break;
        }
    } 
    if(i==0)
        cout<<"Entry Not Found";  
        file.close();
    return i;
}
Marks getmarks(int n=0)
{
    int marks[5];
    int roll;
    string sub[]={"Eng","Hindi","Punjabi","Math","Sci"};
    cout<<"\nEnter Roll number:";
    cin>>roll;
    cout<<"\n"<<search_roll(roll)<<"\n";
     if(Search(roll)==0)
    {
        cout<<"\nStudent doesnt exits\n";
        Marks m;
        return m;
    }
  
    else if(search_roll(roll)==1&&n==0)
    {
        Marks m;
        cout<<"Roll number already exits";
        return m;
    }

    else if(search_roll(roll)==0&&n==1)
    {
        Marks m;
        cout<<"Roll number not exits we are not updating that file sorry";
        return m;
    }
  
    
    // else if(search_roll(roll)==0&&n==1)
    // {
    //     cout<<"\nIt is not available we cannot update\n";
    //     Marks m;
    //     return m;
    // }
    cout << "Enter the marks for 5 subjects:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "\nMarks of "<<sub[i]<<":";
        cin >> marks[i];
    }
    Marks m(roll,marks);
    return m;
}
void write_marks()
{
    Marks m=getmarks();
    if(m.roll!=0)
    {
    fstream file("marksinfo.dat",ios::app|ios::binary);
    file.write((char*)&m,sizeof(m));
    file.close();    
    }
    
}
void read_marks()
{
    Marks m;
    fstream file("marksinfo.dat",ios::in|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
        search(m.roll);
        m.display();
    }
    file.close();    
}
void search_data(int roll)
{
    Marks m;
    fstream file("marksinfo.dat",ios::in|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
        if(m.roll==roll)
        {
            m.display();
            break;
        }
    }
}
void update_marks(Marks m1)
{
    Marks m;
    // if(m.roll==0)
    // {
    //     // cout<<"\nRoll number already exits\n";
    //     return;
    // }
    fstream file("marksinfo.dat",ios::in|ios::binary);
    ofstream fileo("marksinfo_copy.dat",ios::out|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
        if(m1.roll!=m.roll)
            fileo.write((char*)&m,sizeof(m));
        else
            fileo.write((char*)&m1,sizeof(m1));
    }
    fileo.close();
    file.close();
    remove("marksinfo.dat");
    rename("marksinfo_copy.dat","marksinfo.dat");
}
void delete_marks(int roll)
{
    Marks m;
    fstream file("marksinfo.dat",ios::in|ios::binary);
    ofstream fileo("marksinfo_copy.dat",ios::out|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
        if(roll!=m.roll)
            fileo.write((char*)&m,sizeof(m));
    }
    fileo.close();
    file.close();
    remove("marksinfo.dat");
    rename("marksinfo_copy.dat","marksinfo.dat");
}
void marks_info()
{
    char choice;
    do
    {
        cout<<"\n............\n";
    cout<<"1.Add\n";
    cout<<"2.Delete\n";
    cout<<"3.Show All Data\n";
    cout<<"4.Edit\n";
    cout<<"5.Show Desired Entry\n";
    cout<<"6.Search Entry\n";
    cout<<"7.Exit\n";
    
        cout<<"\n............\n";
    int c;
    cout<<"\nEnter Your Choice:";
    cin>>c;
    switch(c)
    {
        case 1:
        {
            write_marks();
            break;
        }
        case 2:
        {
            int roll;
            cout<<"\nEnter roll no. you want to delete:";
            cin>>roll;
            int x=Search(roll);
            if(x==0)
            cout<<"\nStudent is not available\n";
            else
            delete_marks(roll);
            break;
        }
        case 3:
        {
            read_marks();
            break;
        }
        case 4:
        {
            Marks m=getmarks(1);
            update_marks(m);
            break;
        }
        case 5:
        {
            int roll;
            cout<<"\nEnter roll no. you want to search:";
            cin>>roll;
            search_data(roll);
            break;
        }
        case 6:
        {
            int roll;
            cout<<"\nEnter roll no. you want to search:";
            cin>>roll;
            search_roll(roll);
            break;
        }
        case 7:
        {
            cout<<"Thank You!";
            break;
        }
    }
    cout<<"\nDo you want to continue:";
    cin>>choice;
    } while (choice=='y'||choice=='Y');
    
}
class Result
{
    int roll;
    int total;
    int position;
    public:
        Result(int roll=0,int total=0,int position=0)
        {
            this->roll=roll;
            this->total=total;
            this->position=position;
        }
        void display1()
        {
            cout<<"\nStudent Info :\n";
            cout<<"roll number: "<<roll<<"\n";
            cout<<"total:"<<total<<"\n";
            cout<<"position:"<<position<<"\n\n";
        }

};
void getresult()
{
    cout<<"\n Result Calculated and information of all student is \n";
    int a[3];
    fstream file("marksinfo.dat",ios::in|ios::binary);
    for(int i=0;i<3;i++)
    {
        Marks m;
        file.read((char*)&m,sizeof(m));
        a[i]=m.sum();
    }
    for(int i=0;i<3;i++)
    {
            for(int j=0;j>3-i-1;j--)
            {
                if(a[j]>a[j+1])
                {
                    int temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
            }
    }
    fstream filer("result.dat",ios::out|ios::binary);
    int x=0;      
    for(int i=0;i<3;i++)
    {
        Marks m;
        fstream file("marksinfo.dat",ios::in|ios::binary);
        while(file.read((char*)&m,sizeof(m))) 
        {
            if(m.sum()==a[i])
            {
                x++;
                Result ob(m.roll,m.sum(),x);
                filer.write((char*)&ob,sizeof(ob));    
                m.display();
                break;
            }
        }      
    }
    filer.close();
}
int count_result()
{
    Result ob;
    int i=0;
    fstream file("result.dat",ios::in|ios::binary);
    while(file.read((char*)&ob,sizeof(ob)))
    {
        i++;
        // ob.display1();
    }
    file.close();  
    return i;  
}

void read_result()
{
    Result ob;
    fstream file("result.dat",ios::in|ios::binary);
    while(file.read((char*)&ob,sizeof(ob)))
    {
        ob.display1();
    }
    file.close();    
}

void getMenu()
{
    int c;
    do
    {
        cout<<"\n.............\n";
        cout<<"1.Student\n";
        cout<<"2.Marks\n";
        cout<<"3.Calulate or show result\n";
        cout<<"4.exit\n";
        cout<<"\n.............\n";
        cout<<"\nEnter your choice:";
        cin>>c;
        switch(c)
        {
            case 1:
                getStudentMenu();
                break;
            case 2:
                marks_info();
                break;
            case 3:
                {
                    if(count_result()>0)
                        read_result();
                    else
                        getresult();
                    break;
                    
                    }
            case 4:
                exit(0);
            default:
                cout<<"Invalid";
        }
    } while (c!=10);
}
main()
{
getMenu();
}