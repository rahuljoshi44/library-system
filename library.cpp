#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>

struct Borrower
{
	char name[20];
	char Rno[10];
	int copies;
};

class Book
{
	private:
		char title[50];
		char author[50];
		int ID;
		int copies;

	public:
		void display();
		void getInfo();
		void addCopy(int);
		void removeCopy(int);
		void getBorrowerInfo();
		void displayBorrower();
		char getTitle();
		int getID();
		int getCopies();
		int getBorrowedCopies();
        int BC; //count for borrowers
		Borrower borrower[10];
		Book()
		{
			strcpy(title,"NULL");
			strcpy(author,"NULL");
			ID=0;
			copies=0;
			BC=0;
		}
};
int Book::getCopies()
{
	return copies;
}

void Book::getBorrowerInfo()
{
	cout<<"Enter Student Name: ";
	gets(borrower[BC].name);
	cout<<"Enter Roll number: ";
	gets(borrower[BC].Rno);

	cop:
	cout<<"Number of Copies: ";
	cin>>borrower[BC].copies;
	if(borrower[BC].copies>copies)
	{
		cout<<"Insufficient Copies, please enter again.\n";
		goto cop;
	}
	removeCopy(borrower[BC].copies);
	BC++;
}

void Book::displayBorrower()
{
	for(int i=0; i<BC-1; i++)
	{
		cout<<"\n";
		cout<<"Student Name: "<<borrower[i].name;
		cout<<"\tRoll Number: "<<borrower[i].Rno;
		cout<<"\tCopies: "<<borrower[i].copies;
	}
}
int Book::getBorrowedCopies()
{
	int cop=0;
	for(int i=0;i<BC-1;i++)
		cop+=borrower[i].copies;
	return cop;
}

void Book::getInfo()
{
	cout<<"Enter Book title: ";
	gets(title);
	cout<<"Enter Author: ";
	gets(author);
	cout<<"Enter ID: ";
	cin>>ID;
}

void Book::display()
{
	cout<<"\nTitle: "<<title;
	cout<<"\t\tAuthor: "<<author;
	cout<<"\nID: "<<ID;
	cout<<"\t\tCopies: "<<copies;
}
int Book::getID()
{
	return ID;
}
void Book::addCopy(int a)
{
	copies+=a;
}
void Book::removeCopy(int c)
{
	copies-=c;
}

void title()
{
	for(int i=0;i<26;i++)
	cout<<"-";
	cout<<"(LIBRARY MANAGEMENT SYSTEM)";
	for(i=0;i<27;i++)
	cout<<"-";
	cout<<"\n";
}

void MainMenu(char &ch)
{
	cout<<"\t\t\t\t MENU\n";
	cout<<"\t\t\t______________________\n\n";
	cout<<"\t\t\t(1) Add Book\n";
	cout<<"\t\t\t(2) Display Books\n";
	cout<<"\t\t\t(3) Borrow Book\n";
	cout<<"\t\t\t(4) View Borrowed Books\n";
	cout<<"\t\t\t(5) Return Book\n";
	cout<<"\t\t\t(6) Delete Books\n";
	cout<<"\t\t\t(7) Metrics\n";
	cout<<"\t\t\t(8) Exit\n";
	ch=getch();
}


void main()
{
	clrscr();
	Book book,temp;

	char choice;
	do
	{
		clrscr();
		title();
		MainMenu(choice);
		//  Add Book
		if(choice=='1')
		{
			long pos;
			int isCopy=0;
			fstream fBook("books.dat",ios::in|ios::out|ios::binary);
			clrscr();
			title();
				cout<<"ADD BOOK\n\n";
				book.getInfo();
				while(!fBook.eof())
				{
						pos=fBook.tellg();
						fBook.read((char*)&temp,sizeof(temp));
						if(temp.getID()==book.getID())
						{
							int cop1;
							cout<<"\nBook is already present, how many copies do you wish to add:";
							cin>>cop1;
							temp.addCopy(cop1);
							fBook.seekg(pos);
							fBook.write((char*)&temp,sizeof(temp));
							cout<<"\nCopies succesfully added.";
							isCopy=1;
							cop1=0;
							break;
						}
				}
				fBook.close();
				if(isCopy==0)
				{
					int cop2=0;
					ofstream appBook("books.dat",ios::app|ios::binary);
					cout<<"Number of Copies: ";
					cin>>cop2;
					book.addCopy(cop2);
					appBook.write((char*)&book,sizeof(book));
					cout<<"\nBook succesfully added.";
					appBook.close();
				}

			getch();
		  }
		//  Display Books
		if(choice=='2')
		{
			clrscr();
			title();
			cout<<"BOOKS LIST:\n\n";
			ifstream inBook("books.dat",ios::in|ios::binary);
			inBook.seekg(0);
			while(!inBook.eof())
			{
					inBook.read((char*)&book,sizeof(book));
					book.display();
					cout<<"\n";
			}
			inBook.close();
		 }
		 //  Borrow Books
		 if(choice=='3')
		 {
			int ID;
			char isThere=0;
			long pos;
			fstream fBook("books.dat",ios::in|ios::out|ios::binary);
			clrscr();
			title();

				cout<<"Enter ID of book:";
				cin>>ID;
				fBook.seekg(0);
				while(!fBook.eof())
				{
					pos=fBook.tellg();
					fBook.read((char*)&book,sizeof(book));
					if(book.getID()==ID)
					{
						cout<<"\nEnter Borrower Info:\n";
						book.getBorrowerInfo();
						book.BC++;
						fBook.seekg(pos);
						fBook.write((char*)&book,sizeof(book));
						cout<<"\nBook Succesfully issued.";
						isThere=1;
						break;
					}
				}
				fBook.close();
				if(isThere==0)
					cout<<"Sorry, no book found.";
		 }
		 //  View Borrowed Books
		 if(choice=='4')
		 {
			clrscr();
			title();
			ifstream inBook("books.dat",ios::in|ios::binary);
			inBook.seekg(0);
			cout<<"LIST OF BORRWED BOOKS:\n\n";
			while(!inBook.eof())
				{
					inBook.read((char*)&book,sizeof(book));
					if(book.BC>0)
					{
						book.display();
						cout<<" (in stock) \nBORRWERS:\n";
						book.displayBorrower();
						cout<<"\n";
					}

				}
			inBook.close();
		 }
		 //  Return Books
		  if(choice=='5')
		  {
			clrscr();
			title();
			int ID,cop;
			long pos;
			char RN[10];
			fstream fBook("books.dat",ios::in|ios::out|ios::binary);
			cout<<"Enter ID of book to return: ";
			cin>>ID;
			fBook.seekg(0);
			while(!fBook.eof())
			{
				pos=fBook.tellg();
				fBook.read((char*)&book,sizeof(book));
				if(book.getID()==ID)
				{
					if(book.BC>0)
					{
						book.display();
						book.displayBorrower();
						cout<<'\n';
						cout<<"Enter RNO of borrower: ";
						cin>>RN;
						for(int i=0;i<book.BC;i++)
						{
							if(strcmpi(book.borrower[i].Rno,RN)==0)
							{
								ret:
								cout<<"Enter number of copies to return: ";
								cin>>cop;
								if(cop>book.borrower[i].copies)
								{
									cout<<"\nInvalid, Only ";
									cout<<book.borrower[i].copies<<" borrowed.\n";
									goto ret;
								}
								else
								{
									book.borrower[i].copies-=cop;
									book.addCopy(cop);
									cout<<"\nBooks succesfully returned.";
								}
								fBook.seekg(pos);
								fBook.write((char*)&book,sizeof(book));
							}
						}
					}
					else
					{
						cout<<"Sorry, no one has borrowed this book.";
					}
					break;
				}
			 }
		  }
		 //  Delete Books
		 if(choice=='6')
		 {
			int ID,cop,isThere=0;
			long pos;
			fstream fBook("books.dat",ios::in|ios::out|ios::binary);
			clrscr();
			title();

				cout<<"Enter ID of desired book:";
				cin>>ID;
				fBook.seekg(0);
				while(!fBook.eof())
				{
						pos=fBook.tellg();
						fBook.read((char*)&book,sizeof(book));
						if(book.getID()==ID)
						{
							del1:
							cout<<"Copies to be deleted: ";
							cin>>cop;
							if(book.getCopies()<cop)
							{
								cout<<"\nOnly "<<book.getCopies()<<" copies available.\n";
								cout<<"Please enter again.\n";
								goto del1;
							}
							book.removeCopy(cop);
							fBook.seekg(pos);
							fBook.write((char*)&book,sizeof(book));
							cout<<"\nBooks Succesfully deleted.";
							isThere=1;
						}
				}
				fBook.close();
				if(isThere==0)
					cout<<"\nSorry, no book found.";
		 }
		 //  Metrics
		 if(choice=='7')
		 {
			clrscr();
			title();
			int totalBooks;
			int netBooks=0,borrowedBooks=0;
			ifstream inBook("books.dat",ios::in|ios::binary);
			while(!inBook.eof())
			{
				inBook.read((char*)&book,sizeof(book));
				netBooks+=book.getCopies();
				if(book.BC>0)
					borrowedBooks+=book.getBorrowedCopies();
			}
			totalBooks=netBooks+borrowedBooks;

			cout<<"\n\t\t\t\tMETRICS\n";
			cout<<"\n\t\t\t______________________\n";
			cout<<"\n\tTotal Books owned: "<<totalBooks;
			cout<<"\n\n\tTotal Borrowed Books: "<<borrowedBooks;
			cout<<"\n\tTotal books available in library: "<<netBooks;
	      }
		  getch();
	}while(choice!='8');
 }
