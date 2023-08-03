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
        cout<<"Date = "<<date<<"-"<<month<<"-"<<year;
    }

};
class student
{
    public:
    int rollno;
    char name[20];
    char phone[10];
    char classes[20];
    char fathers_name[20];
    DOB d;
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
        cout<<"   students rollno "         <<rollno<<"\n";
        cout<<"   students name "           <<name<<"\n";
        cout<<"   students phone number "     <<phone<<"\n";
        cout<<"   student class "           <<classes<<"\n";
        cout<<"   students fathers_name "     <<fathers_name<<"\n";
        d.display();
    }
};

int Search(int roll)
{
    student s;
    fstream file("project.dat",ios::in|ios::binary);
    int i=0;
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollno==roll)
        {
            i=1;
            cout<<"\nEntry found ";
            break;
        }
        
    }
    if(i=0)
    cout<<"\nEntry not found ";
    file.close();
    return i;

}
student getInfo(int s=0)
{
    int date;
    int month;
    int year;
    int roll;
    cout<<"Enter students rollno ";
    cin>>roll;
    if(Search(roll)==1&&s==0)
    {
        cout<<"roll number exists sorry for invalid information "<<endl;
        student s;
        return s;
    }

    char name[20];
    char phone[20];
    char classes[20];
    char fathers_name[20];
    cout<<"Enter students data ";
    
    cout<<"Enter students name ";
    cin>>name;
    cout<<"Enter students phone no ";
    cin>>phone;
    cout<<"Enter student class ";
    cin>>classes;
    cout<<"Enter students fathers name " ;
    cin>>fathers_name;
    cout<<"Enter date of birth ";
    cin>>date>>month>>year;
    DOB d(date,month,year);
    student s1(roll,name,phone,classes,fathers_name,d);
    return s1;
}



void write_to_file()
{
    student s=getInfo();
    if(s.rollno!=0)
    {
        fstream file("project.dat",ios::app|ios::binary);
        file.write((char*)&s,sizeof(s));
        file.close();

    }
   
}

void read_from_file()
{
    student s;
    fstream file("project.dat",ios::in|ios::binary);
    //fstream file("project_copy.dat",ios::in);
    cout<<"Inside reading";
    while(file.read((char*)&s,sizeof(s)))
    {
        //cout<<"Hello\n";
        s.display();
    }
    file.close();


}

void search(int roll)
{
    student s;
    fstream file("project.dat",ios::in|ios::binary);
    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollno==roll)
        s.display();
    }
    file.close();

}



void copy()
{
    student s;
    fstream inputFile("project.dat",ios::in|ios::binary);
    fstream outputFile("project_copy.dat",ios::out|ios::binary);
    while(inputFile.read((char*)&s,sizeof(s)))
    {
        outputFile.write((char*)&s,sizeof(s));

    }
    inputFile.close();
    outputFile.close();
}

void deleteInfo(int rollno)
{
    ofstream fout("projectcopy.dat",ios::binary);
    ifstream fin("project.dat",ios::binary);
    student s;
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(s.rollno!=rollno)
        {
            fout.write((char*)&s,sizeof(s));
        }
        
    }
    fout.close();
    fin.close();
    remove("project.dat");
    rename("projectcopy.dat","project.dat");
    cout<<"\nContent deleted success\n";
}

void updatetofile(student s)
{
    ofstream fout("projectcopy.dat",ios::binary);
    ifstream fin("project.dat",ios::binary);
    student scopy;

    while(fin.read((char*)&scopy,sizeof(scopy)))
    {
        if(s.rollno!=scopy.rollno)
        {
            fout.write((char*)&scopy,sizeof(scopy));
        }
        else{
            fout.write((char*)&s,sizeof(s));
        }
    }    

        fout.close();
        fin.close();
        remove("project.dat");
        rename("projectcopy.dat","project.dat");
        cout<<"\nContent updated success\n";
    
    
}
void getStudentMenu()
{
    char choice;
    do
    {
    cout<<"1.Add\n";
    cout<<"2.Delete\n";
    cout<<"3.Show All Data\n";
    cout<<"4.Edit\n";
    cout<<"5.Show Desired Entry\n";
    cout<<"6.Search Entry\n";
    cout<<"7.Exit\n";
    int c;
    cout<<"Enter Your Choice:";
    cin>>c;
    switch(c)
    {
        case 1:
           write_to_file();
           break;
        case 2:
        {
            int roll;
            cout<<"Enter roll which u want to delete:";
            cin>>roll;
            deleteInfo(roll);
            break;
        }
        case 3:
        {
            read_from_file();
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
            cout<<"Enter roll which u want to search:";
            cin>>roll;
            search(roll);
            break;            
        }
        case 6:
        {
            int roll;
            cout<<"Enter roll which u want to search:";
            cin>>roll;
            Search(roll);
            break;            
        }        
        case 7:
        {
            cout<<"THANK YOU!";
            exit(0);
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
        string sub[]={"Eng","Hindi","Punjabi","Math","Sci"};
        cout<<"\n";
        cout<<"Roll No"<<roll;
        cout << "\nMarks Record:\n";
        for (int i = 0; i < 5; i++)
        {
            cout << sub[i] << ": " << marks[i] << '\n';
        }
       int totalMarks = sum();
        cout << "Total marks obtained are: " << totalMarks << '\n';
        float percentage = per(totalMarks);
        cout << "Percentage Obtained: " << percentage;
        char grade=Grade(percentage);
        cout << "\nGrade: " << grade;
    }
};
Marks getmarks()
{
    int marks[5];
    int roll;
    string sub[]={"Eng","Hindi","Punjabi","Math","Sci"};
    cout<<"Enter Roll number:";
    cin>>roll;
    cout << "Enter the marks for 5 subjects:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "Marks of "<<sub[i]<<":";
        cin >> marks[i];
    }
    Marks m(roll,marks);
    return m;
}
void write_marks()
{
    Marks m=getmarks();
    fstream file("marksinfo.dat",ios::app|ios::binary);
    file.write((char*)&m,sizeof(m));
    file.close();
}
void read_marks()
{
    Marks m;
    fstream file("marksinfo.dat",ios::in|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
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
        }
    }
}
void search_roll(int roll)
{
    Marks m;
    fstream file("marksinfo.dat",ios::in|ios::binary);
    while(file.read((char*)&m,sizeof(m)))
    {
        if(m.roll==roll)
        {
            cout<<"Entry Found!";
        }
        else
        {
            cout<<"Entry Not Found!";
        }
    }   
}
void update_marks(Marks m1)
{
    Marks m;
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
    cout<<"1.Add\n";
    cout<<"2.Delete\n";
    cout<<"3.Show All Data\n";
    cout<<"4.Edit\n";
    cout<<"5.Show Desired Entry\n";
    cout<<"6.Search Entry\n";
    cout<<"7.Exit\n";
    int c;
    cout<<"Enter Your Choice:";
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
            cout<<"Enter roll no. you want to delete:";
            cin>>roll;
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
            Marks m=getmarks();
            update_marks(m);
            break;
        }
        case 5:
        {
            int roll;
            cout<<"Enter roll no. you want to search:";
            cin>>roll;
            search_data(roll);
            break;
        }
        case 6:
        {
            int roll;
            cout<<"Enter roll no. you want to search:";
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
main()
{
int c;
do
{
    cout<<"1.Student\n";
    cout<<"2.Marks\n";
    cout<<"3.exit";
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
            exit(0);
        default:
        cout<<"Invalid";
    }
} while(c!=4);

}




/*main()
 {
    
    //deleteInfo(1);
    //   char c;
    //    do{
    //     write_to_file();
    //     cout<<"Enter your choice";
    //     cin>>c;
    //    }while(c=='Y'||c=='y');

          
    //  int rollno;
    // cout<<"Enter rollno ";
    // cin>>rollno;
     //deleteInfo(1);
     
    // search(rollno);

    // copy();
     read_from_file();
      //student s=getInfo();
      //updatetofile(s);
    getstudentMenu();

}*/

