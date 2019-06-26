/*fifth change of day*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

//#define IN 1
//#define OUT 0
#define ADMIN 1234

void AddBook();
void DisplayBookInfo();
void Searchbook();
void Addmember();
void Issue();
void ReturnBook();
void DisplayMemberInfo();
void DeleteBook();
void EditBookInfo();
void DeleteMember();
void EditMemberInfo();
int Check(char *a);
//int Check2()
void Exit();


char info[500];
char infom[500];
char avail[20]="avail";
char unavail[20]="issued";

struct
	{
	int bookId;
	char bookName[50] ;
	char author[50];
	int noOfChap;
	char status[20];
	int mBookId;
	} book;
struct
	{
	int memberId;
	char memberName[25] ;
	char department[25];
	int availableCard;
	double phoneNo;
	} member;


FILE *libraryData;
FILE *memberData;
FILE *file1;
FILE *file2;
FILE *temp1;
FILE *temp2;


int main()
	{
	int pass;
	printf("\nEnter The Password To Use The Program\n");
	scanf("%d",&pass);
	memberData = fopen("memberData.txt","r");
	while(!feof(memberData))
		{
		fscanf(memberData,"%d %s %s %lf %d ",&member.memberId,&member.memberName,&member.department,&member.phoneNo,&member.availableCard);
		if(pass==member.memberId || pass==ADMIN)
			{


			int choice=0,i;

			printf("\n*********************************************************\n\t\tLIBRARY MANAGEMENT SYSTEM\n*********************************************************\n");
			do
				{
				printf("\n\t\t\t<<<<MENU>>>>\n\n 1>  Add A New Book\t\t\t 2>  Display Book Information\n\n 3>  Search a book \t\t\t 4>  Add A New Member \n\n 5>  Issue \t\t\t\t 6>  Return A Issued Book \n\n 7>  Display Member Information \t 8>  Delete Book \n\n 9>  Edit Book Information \t\t 10> Delete Member \n\n 11> Edit Member Information \t\t 12> Exit the program \n\n\t Enter your choice  ");
				scanf("%i",&choice);


				switch (choice)
					{
					case 1:
						AddBook();
						break;
					case 2:
						DisplayBookInfo();
						break;
					case 3:
						Searchbook();
						break;
					case 4:
						Addmember();
						break;
					case 5:
						Issue();
						break;
					case 6:
						ReturnBook();
						break;
					case 7:
						DisplayMemberInfo();
						break;
					case 8:
						DeleteBook();
						break;
					case 9:
						EditBookInfo();
						break;
					case 10:
						DeleteMember();
						break;
					case 11:
						EditMemberInfo();
						break;
					case 12:
						Exit();
						break;
					default:
						printf(" Sorry Invalid Input\n");
					}
				}
			while(choice!=12);
			return (0);
			}
		else
			{

			printf("\nWrong Password Try Again!!!\n");
			main();
			}
		}
	fclose(memberData);
	}

void AddBook()
	{
	int check,found=0;
	strcpy(book.status,avail);
	book.mBookId=NULL;
	srand((unsigned)time(NULL));
	libraryData = fopen("libraryData.txt","a+");
	printf("\n*>Enter The Name of The Book :\n");
	scanf("%s",book.bookName);
	do
		{
		printf("\n*>Enter The Name of Author :\n");
		scanf("%s",book.author);
		check=Check(book.author);
		}
	while(check);
	printf("\n*>Enter The Number of Chapters Of The Book:(Numeric)\n");
	scanf("%d",&book.noOfChap);
	while(book.noOfChap==0)
		{
		printf("\n*>Number of Chapters Of The Book Cannot Be Zero:(Enter Numeric Value)\n");
		scanf("%d",&book.noOfChap);
		}
	book.bookId=rand();
	printf("The Id Assigned To The Book Is %d\n\n",book.bookId);
	fprintf( libraryData,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
	fclose( libraryData);
	printf("Your Book has been Successfully Added\n");
	}


void DisplayBookInfo()
	{
	libraryData = fopen("libraryData.txt","a+");
	printf("_________________________________________________________________________\nBookId\tName\t\tAuthor\t\tStatus\tNo.Of Chapter\tMember Id\n_________________________________________________________________________\n");
	while(!feof(libraryData))
		{
		fgets(info,500,libraryData);
		printf("%s\n",info);
		}
	printf("_________________________________________________________________________\n\n");
	fclose(libraryData);
	}


void Searchbook()
	{
	int i,findId,check=0,x;
	char find[25],stats[3];
	int found=0;
	if((libraryData=fopen("libraryData.txt","r"))==NULL)
		printf("\n\n Sorry The File Is Empty\n\n");
	else
		{
		do
			{
			printf("\n\n 1>Search By Name Of Book:\t\t\t 2>Search By Unique Id Of Book:\n\n 3>Search Book With Chapter More Than 5:\t 4>Search By Member Id:\n\n 5>Generic Search  \n\n\t Enter Your Choice  ");
			scanf("%d",&i);
			switch(i)
				{

				case 1:
					printf("\nEnter The Name Of Book : \n\n");
					scanf("%s",find);
					while(feof(libraryData)==0 && found==0)
						{
						fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
						if(strcmp(find,book.bookName)==0)
							found=1;
						}
					check=1;
					break;
				case 2:
					printf("\nEnter The Unique Id Of Book : \n");
					scanf("%d",&findId);
					while(feof(libraryData)==0 && found==0)
						{
						fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
						if(findId==book.bookId)
							found=1;
						}
					check=1;
					break;
				case 3:
					while(feof(libraryData)==0)
						{
						fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
						if(5<book.noOfChap)
							{
							if(strcmp(book.status,avail)==0)
								strcpy(book.status,avail);
							else
								strcpy(book.status,unavail);
							printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters: %d\nMember Id: %d\n\n",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
							found=3;
							}
						}
					fclose(libraryData);
					check=1;
					break;
				case 4:
					printf("\nEnter The Member Id : \n");
					scanf("%d",&findId);
					while(feof(libraryData)==0)
						{
						fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
						if(findId==book.mBookId)
							{
							if(strcmp(book.status,avail)==0)
								strcpy(book.status,avail);
							else
								strcpy(book.status,unavail);
							printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters: %d\nMember Id: %d\n\n",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
							found=3;
							}
						}
					fclose(libraryData);
					check=1;
					break;
				case 5:
					printf("\n\nEnter the name or number you want to search\n");
					scanf("%s",find);
					x=atoi(find);
					if(x==0)
						{
						while(feof(libraryData)==0)
							{
							fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
							if(strcmp(find,book.bookName)==0 || strcmp(find,book.author)==0 || strcmp(find,book.status)==0)
								{
								if(strcmp(book.status,avail)==0)
									strcpy(book.status,avail);
								else
									strcpy(book.status,unavail);
								printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters: %d\nMember Id: %d\n\n",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
								found=3;
								}
							}
						check=1;
						}
					else
						{
						while(feof(libraryData)==0)
							{
							fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
							if(x==book.bookId || x==book.noOfChap || x==book.mBookId)
								{
								if(strcmp(book.status,avail)==0)
									strcpy(book.status,avail);
								else
									strcpy(book.status,unavail);
								printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters: %d\nMember Id: %d\n\n",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
								found=3;
								}
							}
						check=1;
						}
					break;
				default :
					printf("\n\nInvalid Choice\n\n");
					break;
				}
			}
		while(check==0);

		if(found==1 && found!=2 && found!=3)
			{
			if(strcmp(book.status,avail)==0)
				strcpy(book.status,avail);
			else
				strcpy(book.status,unavail);
			printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters: %d\nMember Id: %d\n\n",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
			}
		else if(found!=1 && found!=2 && found!=3)
			printf("\n\nSorry There is no such Entry\n");
		fclose(libraryData);
		}

	}



void Addmember()
	{
	int check;
	srand((unsigned)time(NULL));
	memberData = fopen("memberData.txt","a+");
	do
		{
		printf("Enter The Name of the Member :\n");
		scanf("%s",member.memberName);
		check=Check(member.memberName);
		}
	while(check);
	do
		{
		printf("Enter The Department\n");
		scanf("%s",member.department);
		check=Check(member.department);
		}
	while(check);
	printf("Enter The phone number of the member:\n");
	scanf("%lf",&member.phoneNo);
	member.memberId=rand();
	member.memberId=member.memberId%1000;
	printf("The Member Id Assigned Is :%d",member.memberId);
	member.availableCard=5;
	fprintf(memberData,"\n%d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
	fclose(memberData);
	printf("\n\n New Member Is Successfully Added\n");
	}

void Issue()
	{
	int memberid,check1=0,check2=0;
	int issuBookName;
	temp1=libraryData;
	temp2=memberData;
	DisplayMemberInfo();
	printf("\nEnter The userid of the Member : \n");
	scanf("%d",&memberid);
	if((memberData=fopen("memberData.txt","r"))==NULL)
		printf(" Sorry The file is empty\n\n");
	else
		{
		while(!feof(memberData)&& check1==0)
			{
			fscanf(memberData,"%d %s %s %lf %d ",&member.memberId,&member.memberName,&member.department,&member.phoneNo,&member.availableCard);
			if(memberid==member.memberId)
				{
				check1=1;
				}
			}
		if(check1)
			{
			if(member.availableCard<1)
				{
				printf(" Sorry You Have No More Library Card\n");
				}
			else
				{
				DisplayBookInfo();
				printf("\nEnter The Id of book :");
				scanf("%d",&issuBookName);
				if((libraryData=fopen("libraryData.txt","r"))==NULL)
					printf(" Sorry The file is empty\n\n");
				else
					{
					while(!feof(libraryData)&& check2==0)
						{
						fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
						if(issuBookName==book.bookId)
							check2=1;
						}
					if(check2)
						{
						if(strcmp(book.status,unavail)==0)
							{
							printf(" Sorry The Book already issued...\n");
							}
						else
							{
							file2=fopen("file2.txt","w");
							if((temp2=fopen("memberData.txt","r"))==NULL)
								printf(" Sorry The file is empty\n\n");
							else
								{
								while(!feof(temp2))
									{
									fscanf(temp2,"%d %s %s %lf %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
									if(memberid==member.memberId)
										{
										member.availableCard--;
										fprintf(file2,"\n %d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
										}
									else
										{
										fprintf(file2,"\n %d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
										}
									if(feof(temp2))
										break;
									}
								}
							fclose(temp2);
							fclose(file2);
							file1=fopen("file1.txt","w");
							if((temp1=fopen("libraryData.txt","r"))==NULL)
								printf(" Sorry The file is empty\n\n");
							else
								{
								while(!feof(temp1))
									{
									fscanf(temp1,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
									if(issuBookName!=book.bookId)
										{
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										}
									else
										{
										book.mBookId=memberid;
										strcpy(book.status,unavail);
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										}
									}
								}
							fclose(temp1);
							fclose(file1);
							fclose(libraryData);
							fclose(memberData);
							remove("libraryData.txt");
							rename("file1.txt","libraryData.txt");
							remove("memberData.txt");
							rename("file2.txt","memberData.txt");
							printf("\n\nYou Have Successfully Issued A Book\n");
							}
						}
					else if(!check2)
						printf(" Sorry There Is No Such Book\n");
					}
				}
			}
		else if(!check1)
			printf(" Sorry Invalid User id\n");
		}

	}


void DisplayMemberInfo()
	{
	memberData = fopen("memberData.txt","a+");
	printf("_______________________________________________\nMemId\tName\tDept\tPh.no\t    Availablecards\n_______________________________________________");
	do
		{
		fgets(infom,500,memberData);
		printf("%s\n",infom);
		}
	while(!feof(memberData));
	printf("\n_______________________________________________\n");
	fclose(memberData);
	}


void ReturnBook()
	{
	int memberid,check1=0,check2=0,flag=0;
	int retbookname;
	temp1=libraryData;
	temp2=memberData;
	DisplayMemberInfo();
	printf("\nEnter The userid of the Member :\n");
	scanf("%d",&memberid);
	if((memberData=fopen("memberData.txt","r"))==NULL)
		printf("Sorry The file is empty\n\n");
	else
		{

		while(!feof(memberData) && check1==0)
			{
			fscanf(memberData,"%d %s %s %lf %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
			if(memberid==member.memberId)
				{
				check1=1;
				}
			}
		if(check1)
			{
			if(member.availableCard>=5)
				{
				printf("Sorry You Have Not Issued A Book\n");
				}
			else
				{
				libraryData = fopen("libraryData.txt","r");
				printf("_________________________________________________________________________\nBookId\tName\t\tAuthor\t\tStatus\tNo.Of Chapter\tMember Id\n_________________________________________________________________________\n");
				while(feof(libraryData)==0)
					{
					fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
					if(memberid==book.mBookId)
						{
						printf("\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d\n",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
						}
					}
				printf("_________________________________________________________________________\n\n");
				fclose(libraryData);
				printf("\nEnter The Id of book:");
				scanf("%d",&retbookname);
				if((libraryData=fopen("libraryData.txt","r"))==NULL)
					printf("Sorry The file is empty\n\n");
				else
					{
					while(!feof(libraryData) && check2==0 && check2!=2)
						{
						fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
						if(retbookname==book.bookId)
							check2=1;
						}
					if(check2)
						{
						if(strcmp(book.status,avail)==0)
							{
							printf("Sorry The Book already in stock\n");
							}
						else
							{

							file2=fopen("file2.txt","w");
							if((temp2=fopen("memberData.txt","a+"))==NULL)
								printf("Sorry The file is empty\n\n");
							else
								{
								while(!feof(temp2))
									{
									fscanf(temp2,"%d %s %s %lf %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);


									if(memberid==member.memberId)
										{
										member.availableCard++;
										fprintf(file2,"\n %d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
										}
									else
										{
										fprintf(file2,"\n %d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
										}
									if(feof(temp2))
										break;
									}
								}
							fclose(temp2);
							fclose(file2);


							file1=fopen("file1.txt","w");
							if((temp1=fopen("libraryData.txt","r"))==NULL)
								printf("Sorry The file is empty\n\n");
							else
								{
								while(!feof(temp1))
									{
									fscanf(temp1,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
									if(retbookname!=book.bookId)
										{
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										}
									else
										{
										book.mBookId=NULL;
										strcpy(book.status,avail);
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										}
									}
								}
							fclose(temp1);
							fclose(file1);
							fclose(libraryData);
							fclose(memberData);
							remove("libraryData.txt");
							rename("file1.txt","libraryData.txt");
							remove("memberData.txt");
							rename("file2.txt","memberData.txt");
							printf("\n\nBook Successfully Returned\n");
							}
						}
					else if(!check2)
						printf("Sorry There Is No Such Book\n");

					}
				}
			}
		else if(!check1)
			printf("Sorry Invalid User Id\n");
		}

	}


void DeleteBook()
	{
	int password,bookid,flag=0;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
		{
		DisplayBookInfo();
		printf("\nEnter The Id Of Book To Delete :\n");
		scanf("%d",&bookid);
		if((libraryData=fopen("libraryData.txt","r"))==NULL)
			printf("Sorry The file is empty\n\n");
		else
			{
			file1=fopen("file1.txt","a+");
			while(!feof(libraryData))
				{
				fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
				if(bookid==book.bookId)
					{
					if(strcmp(book.status,unavail)==0)
						{
						printf("\nSorry Cannot Delete Issued Book\n");
						}
					else
						{
						if(bookid!=book.bookId)
							fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
						fclose(file1);
						fclose(libraryData);
						printf("\n\nBook Successfully Deleted\n");
						remove("libraryData.txt");
						rename("file1.txt","libraryData.txt");
						}
					}
				}
			}
		}
	else
		printf("Sorry Password Is Incorrect\n");
	}


void DeleteMember()
	{
	int password,memberid;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
		{
		DisplayMemberInfo();
		printf("\nEnter The Id Of Member To Delete :\n");
		scanf("%d",&memberid);
		if((memberData=fopen("memberData.txt","r"))==NULL)
			printf("Sorry The file is empty\n\n");
		else
			{
			file2=fopen("file2.txt","a+");
			while(!feof(memberData))
				{
				fscanf(memberData,"%d %s %s %lf %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
				if(memberid==member.memberId)
					{
					if(member.availableCard<5)
						{
						libraryData=fopen("libraryData.txt","r");
						file1=fopen("file1.txt","a+");
						while(feof(libraryData)==0)
							{
							fscanf(libraryData,"%d %s %s %s %d %d",&book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
							if(memberid!=book.mBookId)
								{
								fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
								}
							else
								{
								book.mBookId=NULL;
								strcpy(book.status,avail);
								fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
								}
							}
						}
					}

				if(memberid!=member.memberId)
					fprintf(file2,"\n%d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
				}
			fclose(file2);
			fclose(memberData);
			fclose(file1);
			fclose(libraryData);
			printf("\n\nMember Successfully Deleted\n");
			remove("memberData.txt");
			rename("file2.txt","memberData.txt");
			remove("libraryData.txt");
			rename("file1.txt","libraryData.txt");
			}
		}
	else
		printf("Sorry Password Is Incorrect\n");
	}


void EditBookInfo()
	{
	int password,bookid,i,check=0,check1;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
		{
		DisplayBookInfo();
		printf("\nEnter The Id Of Book To Edit :\n");
		scanf("%d",&bookid);
		if((libraryData=fopen("libraryData.txt","r"))==NULL)
			printf("Sorry The file is empty\n\n");
		else
			{
			file1=fopen("file1.txt","a+");
			while(!feof(libraryData))
				{
				fscanf(libraryData,"%d %s %s %s %d %d", &book.bookId,book.bookName,book.author,book.status,&book.noOfChap,&book.mBookId);
				if(bookid==book.bookId)
					{
					if(strcmp(book.status,unavail)==0)
						{
						printf("Sorry Cannot Edit A Issued Book\n");
						}

					else
						{

						if(bookid!=book.bookId)
							fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
						else
							{
							do
								{
								printf("\nEnter Your Choice\n 1> Edit Book Name \n 2> Edit Book Author \n 3> Edit Number Of Chapter Of Book\n");
								scanf("%d",&i);
								switch(i)
									{
									case 1:
										printf("Enter The Name of The Book :\n");
										scanf("%s",book.bookName);
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										check=1;
										break;
									case 2:
										do
											{
											printf("Enter The Name of Author :\n");
											scanf("%s",book.author);
											check1=Check(book.author);
											}
										while(check1);
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										check=1;
										break;
									case 3:
										printf("Enter The Number of Chapters Of The Book:(Numeric)\n");
										scanf("%d",&book.noOfChap);
										while(book.noOfChap==0)
											{
											printf("Number of Chapters Of The Book Cannot Be Zero:(Enter Numeric Value)\n");
											scanf("%d",&book.noOfChap);
											}
										fprintf(file1,"\n%d\t%s\t\t%s\t\t%s\t%d\t\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap,book.mBookId);
										check=1;
										break;
									default:
										printf("Sorry Invalid Input\n");
										break;
									}
								}
							while(check==0);
							}
						fclose(file1);
						fclose(libraryData);
						printf("\n\nBook Successfully Edited\n");
						remove("libraryData.txt");
						rename("file1.txt","libraryData.txt");
						}
					}
				}
			}
		}
	else
		printf("Sorry Password Is Incorrect\n");
	}


void EditMemberInfo()
	{
	int password,memberid,i,check=0,check1;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
		{
		DisplayMemberInfo();
		printf("\nEnter The Id Of Member To Delete :\n");
		scanf("%d",&memberid);
		if((memberData=fopen("memberData.txt","r"))==NULL)
			printf("Sorry The file is empty\n\n");
		else
			{
			file1=fopen("file1.txt","a+");
			while(!feof(memberData))
				{
				fscanf(memberData,"%d %s %s %lf %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
				if(memberid!=member.memberId)
					fprintf(file2,"\n%d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
				else
					{
					do
						{
						printf("\nEnter Your Choice\n 1> Edit Member Name\n 2> Edit Member's Department\n 3>Edit Member's Phone Number\n");
						scanf("%d",&i);
						switch(i)
							{
							case 1:
								do
									{
									printf("Enter The Name of the Member :\n");
									scanf("%s",member.memberName);
									check1=Check(member.memberName);
									}
								while(check1);
								fprintf(memberData,"\n%d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
								check=1;
								break;
							case 2:
								do
									{
									printf("Enter The Department\n");
									scanf("%s",member.department);
									check1=Check(member.department);
									}
								while(check1);
								fprintf(memberData,"\n%d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
								check=1;
								break;
							case 3:
								printf("Enter Phone Number\n");
								scanf("%d",&member.phoneNo);
								fprintf(memberData,"\n%d\t%s\t%s\t%0.lf\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
								check=1;
								break;
							default:
								printf("Sorry Invalid Input\n");
								break;
							}
						}
					while(check==0);
					}
				}
			fclose(file1);
			fclose(memberData);
			printf("\n\nMember Successfully Edited\n");
			remove("memberData.txt");
			rename("file1.txt","memberData.txt");
			}
		}
	else
		printf("Sorry Password Is Incorrect\n");
	}


int Check(char *a)
	{
	int alphabet = 0, number = 0, i;
	for (i=0; a[i]!= '\0'; i++)
		{
		if (isdigit(a[i]) != 0)
			number=1;
		}
	if(number==1)
		printf("\nNumbers Are Not Allowed\n\n");
	return number;
	}

void Exit()
	{
	exit(0);
	}
