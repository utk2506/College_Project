#include<iostream>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<windows.h>
using namespace std;

int i,n;
ifstream fin;
ofstream fout;
fstream fio;
void disp();
void gotoxy(short a, short b);
class stock
{
		char name[20],pass[10];
	float pr; int quant;

public:
	void get();
	void get2();
	void show();
    int stchk(char nm[30]);    
    void withd(int qty);
    void refil(int qty);
    void gotoxy(short a,short b);
}st;
void gotoxy(short a, short b) //Custom gotoxy() function
{
    COORD coordinates; //Data type of co-ordinates
    coordinates.X = a; //Assign value to X- Co-ordinate
    coordinates.Y = b; //Assign value to Y Co-ordinate
 
SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void stock::withd(int qty)
{
	if(quant>=qty)
	{
		quant-=qty;
		cout<<"\n\nStock updated.\n";
		cout<<"\n\nTotal price to be paid:"<<pr*qty;
    }
	else 
	   cout<<"\n\nInsufficient stock";
	    getch();
		
	
}

void stock::refil(int qty)
{
	
		quant+=qty;
		cout<<"\n\nStock updated.";
	    getch();
		
	
}
int stock::stchk(char nm[30])
{
	if(strcmp(nm,name)==0)
	 return 0;
	else 
	return 1;
}
void stock::get()
{
	cin>>name>>pr>>quant;

}

void stock::get2()
{
	cin>>name>>quant;
}

void stock::show()
{
	
	cout<<"\n\t"<<name<<"\t\t\t\t\t\t"<<quant<<"\t\t\t\t"<<pr;
}
void bill()
{
	system("cls");
}

void addnew()
{
 

    system("cls");

	disp();
	getch();
	system("cls");
	
	cout<<"\nEnter the No. of Products that you wish to add: ";
    cin>>n;
	
    
    if (n!=0)
    {
	
	int j,l,sum=0;
	fout.open("shop.dat",ios::binary|ios::app);
	for(i=0;i<n;i++)
	
	{
		cout<<"\n\nInput the name, price and the quantity of item respectively\n\n";
	    st.get();
	    fout.write((char*)&st,sizeof(st));
        cout<<"\n\nitem updated";
		cin.get();


    }
    cout<<"\n\nStock Updated!!";
    

    fout.close();
    cin.get();
    system("cls");
    disp();
}

	else
{

	fout.close();
	cin.get();
	system("cls");
	cout<<"\n\nNo items to be added";

}
}




void withdraw()
{
	system("cls");
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the product's name \n"<<endl;
	cin>>temp;
	cout<<"\n\nEnter quantity: \n"<<endl;
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
     while(fio)
     {
	    pos=fio.tellp();
	    fio.read((char*)&st,sizeof(st));
	    if(st.stchk(temp)==0)
	    {
		  
		  st.withd(qty);
		  fio.seekp(pos);
		  fio.write((char*)&st,sizeof(st));
		  i++;break;
	    }
     }
     
    
     if(i!=1)
       cout<<"\n\n!!Record not found!!";
     fio.close();
    cin.get();
    system("cls");
	 disp(); 
	getch();
}
void disp()
{
	int i=1;
	gotoxy(15,1);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(15,3);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\tTHE STOCK ITEMS ARE\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(15,5);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
	
	cout<<"--------------------------------------------------------------------------------------------------";
	gotoxy(15,7);
	cout<<"\n\tPARTICULARS\t\t\t\tSTOCK AVAILABLE\t\t\t\t PRICE\n";

	cout<<"--------------------------------------------------------------------------------------------------";
	gotoxy(15,9);
	 fin.open("shop.dat",ios::binary);
     while(!fin.eof())
     {
	  fin.read((char*)&st,sizeof(st));
	  if(!fin.eof())
	  {
	     if(fin.tellg()<0)
	     {	i=0; break;}
	     
	     st.show();
	  }
     }
     if(i==0)
     {	cout<<"\n\n\t\t\t!!Empty record room!!";
	getch();
     }
     fin.close();
    
}
void refill()
{
	system("cls");
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the products name \n"<<endl;
	cin>>temp;
	cout<<"\n\nEnter quantity: \n"<<endl;
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
     while(fio)
     {
	    pos=fio.tellp();
	    fio.read((char*)&st,sizeof(st));
	    if(st.stchk(temp)==0)
	    {
		  
		  st.refil(qty);
		  fio.seekp(pos);
		  fio.write((char*)&st,sizeof(st));
		  i++;break;
	    }
     }
     if(i!=1)
       cout<<"\n\n!!Record not found!!";
     fio.close();
    system("cls");
    cin.get();
	 disp(); cin.get();
    
	
}
void remove()
{
	system("cls");	
	 int i=0;
     char temp[30];
     cout<<"\n\t\t\t\tDelete Record";
     cout<<"\n\nEnter the name of the product:";
     cin>>temp;
     fout.open("temp.dat",ios::binary);
     fin.open("shop.dat",ios::binary);
     while(!fin.eof())
     {
	  fin.read((char*)&st,sizeof(st));
	  if(!fin.eof())
	    if(st.stchk(temp)==0)
	    {
		  st.show();
		  cout<<"\n\n\t\tRecord deleted";
		  i++;
	    }
	    else
		  fout.write((char*)&st,sizeof(st));
     }
     if(i==0)
       cout<<"\n\n!!Record not found!!";
     fin.close();
     fout.close();
     remove("shop.dat");
     rename("temp.dat","shop.dat");
}
int main()
{
	char pass[10],pass2[10];
	int i,j;
	mainmenu:
	system("cls");
	gotoxy(20,1);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2WELCOME TO SALES MANAGEMENT SYSTEM\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";	
	gotoxy(20,5);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,7);
	cout<<"\xDB\xDB\xDB\xDB\xB2 1. Dealer Menu";
	gotoxy(20,9);
	cout<<"\xDB\xDB\xDB\xDB\xB2 2. Customer Menu";
	gotoxy(20,11);
	cout<<"\xDB\xDB\xDB\xDB\xB2 3. Employee Menu ";
//	gotoxy(20,13);
//	cout<<"\xDB\xDB\xDB\xDB\xB2 . Bill`s History";
	gotoxy(20,13);
	cout<<"\xDB\xDB\xDB\xDB\xB2 4. Exit\n\n";
	gotoxy(20,15);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,17);
	cout<<"\n\nEnter Your Choice:";
	cin>>j;
	if(j==1)
	{
	

    system("cls");
    cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";
	
	for(int z=0;z<3;z++)
	{
		pass[z]=getch();
		system("cls");
		cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";
		for(i=1;i<=(z+1);i++)
		{
			cout<<"*";
		}
	}
	if(strcmp(pass,"123")==0)
	{
    cout<<"\n\n\nCongrats!!Access Granted!!\n\n";
    getch();
    system("cls");
	dealermenu:
	system("cls");
	gotoxy(20,1);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2           DEALER MENU            \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";	
	gotoxy(20,3);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,5);
	cout<<"\xDB\xDB\xDB\xDB\xB2 1. Add new product";
	gotoxy(20,7);
	cout<<"\xDB\xDB\xDB\xDB\xB2 2. Display stock";
	gotoxy(20,9);
	cout<<"\xDB\xDB\xDB\xDB\xB2 3. Refill";
	gotoxy(20,11);
	cout<<"\xDB\xDB\xDB\xDB\xB2 4. Remove an item";
	gotoxy(20,13);
	cout<<"\xDB\xDB\xDB\xDB\xB2 5. Main Menu";
	gotoxy(20,15);
	cout<<"\xDB\xDB\xDB\xDB\xB2 6. Exit";
	gotoxy(20,17);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	cout<<"\n\n Enter your Choice :\t";
	cin>>i;
	if(i==1)
	{
		addnew();getch();
	goto dealermenu;
	}

	else if(i==2)
	{
		system("cls");
	disp();getch();goto dealermenu;
	}
	else if(i==3)
	{
		refill();goto dealermenu;
	}
	else if(i==4)
	{
		remove();getch();goto dealermenu;
	}
	else if(i==5)
	{
		goto mainmenu;
	}
	else 
	{
		system("cls");
	cout<<"\n\n\n\t\t\tThank you for Using";

	exit(0);
}
}
else
{
	cout<<"\n\n\nAuthorised Personnel Only\n\n";
	getch();
	
	exit(0);
}
	}
	if(j==2)
	{
		custmenu:
	system("cls");
	gotoxy(20,1);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2           CUSTOMER MENU            \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";	
	gotoxy(20,3);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,5);
	cout<<"\xDB\xDB\xDB\xDB\xB2 1. Purchase\n";
	gotoxy(20,7);
	cout<<"\xDB\xDB\xDB\xDB\xB2 2. Display stock\n";
	gotoxy(20,9);
	cout<<"\xDB\xDB\xDB\xDB\xB2 3. Main Menu\n";
	gotoxy(20,11);
	cout<<"\xDB\xDB\xDB\xDB\xB2 4. Exit:";
	gotoxy(20,13);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,15);
	cout<<"\n\n Enter your Choice :\t";
	cin>>i;
	
	
	
	if (i==1)
	{
	withdraw();getch();goto custmenu;
	}
	else if(i==2)
	{
		system("cls");
	disp();getch();goto custmenu;
	}
	else if(i==3)
	{
		system("cls");
	goto mainmenu;
	}
	else 
	{
		system("cls");
	cout<<"\n\n\n\t\t\tThank you for Using";

	exit(0);
}
	
}
if(j==3)

{
	system("cls");
	cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";
	
	for(int z=0;z<3;z++)
	{
		pass2[z]=getch();
		system("cls");
		cout<<"\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";
		for(i=1;i<=(z+1);i++)
		{
			cout<<"*";
		}
	}
	if(strcmp(pass2,"emp")==0)
	{
		cout<<"\n\n\nCongrats!!Access Granted!!\n\n";
    getch();
    system("cls");
	empmenu:
	system("cls");
	gotoxy(20,1);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2           EMPLOYEE MENU          \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";	
	gotoxy(20,3);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,5);
	cout<<"\xDB\xDB\xDB\xDB\xB2 1. Display stock\n";
	gotoxy(20,7);
	cout<<"\xDB\xDB\xDB\xDB\xB2 2. Refill\n";
	gotoxy(20,9);
	cout<<"\xDB\xDB\xDB\xDB\xB2 3. Main Menu\n";
	gotoxy(20,11);
	cout<<"\xDB\xDB\xDB\xDB\xB2 4. Exit:";
	gotoxy(20,13);
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(20,15);

	cout<<"\n\n Enter your Choice :\t";
	cin>>i;
	if(i==1)
	{
		system("cls");
	disp();getch();goto empmenu;
	}
	else if(i==2)
	{
		refill();goto empmenu;
	}
	
	else if(i==3)
	{
		goto mainmenu;
	}
	else 
	{
		system("cls");
	cout<<"\n\n\n\t\t\tThank You!!";
	
	exit(0);
}
}
else if(j==4)
	{
		system("cls");
	cout<<"\n\n\n\t\t\tThank You!!";
	
	exit(0);			}				

//	else if(j==4)
//	{
//			bill();goto mainmenu;		
//	}
else
{
	cout<<"\n\nSorry!! Access Denied..\n\n";
	
	getch();
	
	exit(0);
}

	}	
	
	
	
}
