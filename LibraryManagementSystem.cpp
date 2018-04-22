//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include <windows.h>
using namespace std;


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



class book
{
	char bno[10];
	char bname[50];

	char aname[20];

	char checkErr[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		
		cout<<"\nEnter The book no.";
		
		gets(checkErr);
		gets(bno);
		cout<<"\n\nEnter The Name of The Book ";
		gets(bname);
	
		cout<<"\n\nEnter The Author's Name ";
		gets(aname);
		//cin>>aname;
		cout<<"\n\n\nBook Created..";
		
		cout<<"-------------------------------------------------------";
		cout<<"Bno: "<<bno<<endl;
		cout<<"Bname: "<<bname<<endl;
		cout<<"Aname: "<<aname<<endl;
		
	}

	void show_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nBook Name : ";
		puts(bname);
		//cout<<bname;
		cout<<"Author Name : ";
		puts(aname);
		//cout<<aname;
	}

	void modify_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		gets(bname);
		getch();
		//cin>>bname;
		cout<<"\nModify Author's Name of Book : ";
		gets(aname);
		//cin>>aname;
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}


};         //class ends here




class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	char checkErr[20];
	int token;
public:
	void create_student()
	{
		system("cls");
		cout<<"\n\n========================================================================================================================";
		cout<<"\n\t\t\t\t\t\tNEW STUDENT ENTRY\n";
		cout<<"========================================================================================================================";
		cout<<"\n\n\n\n\t\t\t\t\t Enter The admission no. : ";
		cin>>admno;
		cout<<"\n\n\n\n\t\t\t\t\t Enter The Name of The Student : ";
		fflush(stdout);
		gets(checkErr);
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"\n\n\n\n\t\t\t\t\t Student Record Created ...";
	}

	void show_student()
	{
		cout<<"\n\t\t\t\t\t\t    Admission no. : "<<admno;
		cout<<"\n\t\t\t\t\t\t    Student Name : ";
		puts(name);
		cout<<"\n\t\t\t\t\t\t    No of Book issued : "<<token;
		if(token==1)
			cout<<"\n\t\t\t\t\t\t    Book No "<<stbno;
			cout<<"\n";
	}

	void modify_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Student Name : ";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<"\t\t\t"<<admno<<setw(20)<<"\t\t"<<name<<"\t\t"<<setw(10)<<token<<endl;}

};         //class ends here




//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
book bk;
student st;


//***************************************************************
//    	function to write in file
//****************************************************************

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		system("cls");
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
		 	flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\n\t\t\t\t\t\t    STUDENT DETAILS\n";
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	cout<<"\n";
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
    		cout<<"\n\n\n\t\t\t\t\t\t    Student does not exist !!! ";
 	getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_book()
{
	char n[6];
	int found=0;
	system("cls");
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
		    	fp.seekp(pos,ios::cur);
		    	fp.write((char*)&bk,sizeof(book));
		    	cout<<"\n\n\t Record Updated";
		    	found=1;
		}
	}

    	fp.close();
    	if(found==0)
    		cout<<"\n\n Record Not Found ";
    	getch();
}


void modify_student()
{
	char n[6];
	int found=0;
	system("cls");
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter The New Details of student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_student()
{
	char n[6];
	int flag=0;
	system("cls");
    	cout<<"\n\n\n\tDELETE STUDENT...";
    	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
    	cin>>n;
    	fp.open("student.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
	     		fp2.write((char*)&st,sizeof(student));
		else
	   		flag=1;
	}

	fp2.close();
    	fp.close();
    	remove("student.dat");
    	rename("Temp.dat","student.dat");
    	if(flag==1)
     		cout<<"\n\n\tRecord Deleted ..";
    	else
     		cout<<"\n\nRecord not found";
    	getch();
}


void delete_book()
{
	char n[6];
	system("cls");
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
    	fp.close();
    	remove("book.dat");
    	rename("Temp.dat","book.dat");
    	cout<<"\n\n\tRecord Deleted ..";
    	getch();
}



//***************************************************************
//    	function to display all students list
//****************************************************************

void display_alls()
{
	system("cls");
     	fp.open("student.dat",ios::in);
     	if(!fp)
     	{
       		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}

	cout<<"\n\n========================================================================================================================";
	cout<<"\n\t\t\t\t\t\t\tSTUDENT LIST\n";
	cout<<"========================================================================================================================\n\n\n\n\n\n";
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\t\t\t\tAdmission No."<<setw(20)<<"Name"<<setw(30)<<"Book Issued\n";
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";

	while(fp.read((char*)&st,sizeof(student)))
	{ cout<"\t\t\t\t";
		st.report();
	}

	fp.close();
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	getch();
}


//***************************************************************
//    	function to display Books list
//****************************************************************

void display_allb()
{
	system("cls");
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}
	cout<<"\n\n========================================================================================================================";
	cout<<"\n\t\t\t\t\t\t\tBOOK LIST\n";
	cout<<"========================================================================================================================\n\n\n\n\n\n";
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"\t\t\t\tBook No."<<setw(20)<<"Book Name"<<setw(30)<<"Author\n";
	cout<<"------------------------------------------------------------------------------------------------------------------------\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{ cout<<"\t\t\t\t";
		bk.report();
	}
     	fp.close();
    cout<<"------------------------------------------------------------------------------------------------------------------------\n";
	getch();

}



//***************************************************************
//    	function to issue book
//****************************************************************

void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
		system("cls");
		cout<<"\n\n========================================================================================================================";
		cout<<"\n\t\t\t\t\t\t\tBOOK ISSUE\n";
		cout<<"========================================================================================================================\n\n\n";
	cout<<"\n\n\t\t\t\t\t  Enter the student's admission no. : ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
    	fp1.open("book.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(student)) && found==0)
       	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"\n\n\t\t\t\t\t  Enter the book no. : ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
			   		if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
       						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t\t\t\t  Book issued successfully\n\nPlease Note: Write the current date 						in backside of your book and submit within 15 days fine Rs. 1 for each day 							after 15 days period";
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book no does not exist";
			}
	    		else
		  		cout<<"\n\n\n\n\t\t\t\t\t  You have not returned the last book ... ";

		}
	}
      	if(found==0)
		cout<<"\n\n\n\n\t\t\t\t\t  Student record not exist !!! ";
	getch();
  	fp.close();
  	fp1.close();
}

//***************************************************************
//    	function to deposit book
//****************************************************************

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    system("cls");
    cout<<"\n\n========================================================================================================================";
	cout<<"\n\t\t\t\t\t\t\tBOOK DEPOSITE\n";
	cout<<"========================================================================================================================\n\n\n";
    cout<<"\n\n\n\n\t\t\t\t\t  Enter the student\'s admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"\n\nBook deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no does not exist";
		      }
		 else
			cout<<"\n\n\n\n\t\t\t\t\t  No book is issued ...  please check !!!";
		}
	   }
      if(found==0)
	cout<<"\n\n\n\n\t\t\t\t\t  Student record not exist !!! ";
	getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	system("cls");
	cout<<"\n\n\n\n\n\n";
	cout<<"\t\t\t\t\t___________________________________________\n\n";
	cout<<"\t\t\t\t\t\tLIBRARY  ";
	cout<<"MANAGEMENT  ";
	cout<<"SYSTEM"<<"\n";
	cout<<"\t\t\t\t\t___________________________________________";
	cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\t   MADE BY : Vaibhav Sharma (05510102716) \n\t\t\t\t\t\t     Apoorva Singh (40110102716) \n\t\t\t\t\t\t     Nischay Garg (03910102716) ";
	cout<<"\n\n\t\t\t\t\t      B.Tech (CSE) 4th Semester";
	cout<<"\n\n\t\t\t    Ambedkar Institute of Advanced Communication Technologies and Research\n\n";
	getch();
}



//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
	system("cls");
	int ch2;
	cout<<"\n\n========================================================================================================================";
	cout<<"\n\t\t\t\t\t\t\tADMINISTRATOR MENU\n";
	cout<<"========================================================================================================================\n";
	cout<<"\n\n\t\t\t\t\t\t    1. CREATE STUDENT RECORD";
	cout<<"\n\n\t\t\t\t\t\t    2. DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t\t\t\t\t\t    3. DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t\t\t\t\t\t    4. MODIFY STUDENT RECORD";
	cout<<"\n\n\t\t\t\t\t\t    5. DELETE STUDENT RECORD";
	cout<<"\n\n\t\t\t\t\t\t    6. CREATE BOOK ";
	cout<<"\n\n\t\t\t\t\t\t    7. DISPLAY ALL BOOKS ";
	cout<<"\n\n\t\t\t\t\t\t    8. DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t\t\t\t\t\t    9. MODIFY BOOK ";
	cout<<"\n\n\t\t\t\t\t\t    10. DELETE BOOK ";
	cout<<"\n\n\t\t\t\t\t\t    11. BACK TO MAIN MENU";
	cout<<"\n\n\t\t\t\t\t\t  Please Enter Your Choice (1-11) : ";
	cin>>ch2;
	cout<<"\n";
	switch(ch2)
	{
    		case 1: system("cls");
	    		write_student();break;
    		case 2: display_alls();break;
    		case 3:
	       		char num[6];
	       		system("cls");
	       		cout<<"\n\n\n\n\t\t\t\t\t Please Enter The Admission No. : ";
	       		cin>>num;
	       		cout<"\n";
	       		display_sps(num);
	       		break;
      		case 4: modify_student();break;
      		case 5: delete_student();break;
		case 6: system("cls");
			write_book();break;
		case 7: display_allb();break;
		case 8: {
	       		char num[6];
	       		system("cls");
	       		cout<<"\n\n\tPlease Enter The book No. ";
	       		cin>>num;
	       		display_spb(num);
	       		break;
			}
      		case 9: modify_book();break;
      		case 10: delete_book();break;
     		case 11: return;
      		default:cout<<"\a";
   	}
   	admin_menu();
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n========================================================================================================================";
		cout<<"\n\t\t\t\t\t\t\tMAIN MENU\n";
		cout<<"========================================================================================================================\n\n\n";
		cout<<"\n\n\t\t\t\t\t\t    01. BOOK ISSUE";
		cout<<"\n\n\t\t\t\t\t\t    02. BOOK DEPOSIT";
	  	cout<<"\n\n\t\t\t\t\t\t    03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t\t\t\t\t\t    04. EXIT";
	  	cout<<"\n\n\n\n\t\t\t\t\t\tPlease Select Your Option (1-4) : ";

	  	ch=getche();
	  	switch(ch)
	  	{
			case '1':system("cls");
				 book_issue();
			   	 break;
		  	case '2':book_deposit();
			    	 break;
		  	case '3':admin_menu();
				 break;
		  	case '4':exit(0);
		  	default :cout<<"\a";
		}
    	}while(ch!='4');
return 0;
}

