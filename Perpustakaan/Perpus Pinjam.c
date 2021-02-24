#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

char dusername[100], dpass[100], dcode[100];	

void UserInterface();
void UIMEMBER();
int global=1;
int permission=1;
time_t ambil_waktu;

FILE *fptr, *nf, *admin, *member;

void savead(char username[100], char pass [100])
{
	int j=1;
	admin =fopen("DATAADMIN.txt","ab+");
	fflush(stdin);
	
	while(fscanf(admin, "%s %s %s", dusername, dpass, dcode)!=EOF)
	{
		if(strcmp(dusername, username)==0)
		{
			puts("Mmmm sorry This UserName can't be used");
			UserInterface();
		}
		j++;
	}
	puts("\nCongrats! Your UserName are now ready to use");
	char bc[10];
	strncpy(bc, username, 3);
	bc[3]='\0';
	strupr(bc);
	
	fprintf(admin, "%s %s %s-%04d\n", username, pass, bc, j);
	printf("Username: %s\nPassword: %s\nUser Code: %s-%04d\n\n", username, pass, bc, j);
	

	fclose(admin);
}

void savemember(char username[100], char pass[100])
{
	
	int j=1;
	member =fopen("DATAMEMBER.txt","ab+");
	fflush(stdin);
	
	while(fscanf(member, "%s %s %s", dusername, dpass, dcode)!=EOF)
	{
		if(strcmp(dusername, username)==0)
		{
			puts("Mmmm sorry This UserName can't be used");
			UserInterface();
		}
		j++;
	}
	puts("\nCongrats! Your UserName are now ready to use");
	char bc[10];
	strncpy(bc, username, 3);
	bc[3]='\0';
	strupr(bc);
	
	fprintf(member, "%s %s %s-%04d\n", username, pass, bc, j);
	printf("Username: %s\nPassword: %s\nUser Code: %s-%04d\n\n", username, pass, bc, j);
	

	fclose(member);
}

void save(char username[100])
{
	
	int j=1;
	fptr =fopen("DATAREG.txt","ab+");
	fflush(stdin);
	
	while(fscanf(fptr, "%s %s", dusername, dcode)!=EOF)
	{
		if(strcmp(dusername, username)==0)
		{
			puts("Mmmm sorry This Book's Name already used");
			UserInterface();
		}
		j++;
	}
	puts("\nCongrats! Your Book's Name are now registered");
	char bc[10];
	strncpy(bc, username, 3);
	bc[3]='\0';
	strupr(bc);
	
	fprintf(fptr, "%s %s-%04d\n", username, bc, j);
	printf("Book's Name: %s\nBook's Code: %s-%04d\n\n", username, bc, j);
	

	fclose(fptr);
}

void datlist()
{
	char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nBook's Name : %s\nBook's Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
   UserInterface();
}

void datlistmemberbook()
{
	char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nBook's Name : %s\nBook's Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
   UIMEMBER();
}


void regad()
{
	char username[100], pass[100];
	fflush(stdin);
	puts("Input your UserName: ");
	gets(username);

	puts("Input your Password:");
	gets(pass);
	
	
	savead(username, pass);
	UserInterface();
}



void reg()
{
	char username[100];
	fflush(stdin);
	puts("Input your Book's Name: ");
	gets(username);
	

	save(username);
	UserInterface();
}


void datlistmember()
{
	int i= 0;
   member = fopen("DATAMEMBER.txt", "r");
   puts("=== LIST DATA ===");
  while(fscanf(member, "%s %s %s", dusername, dpass, dcode)!=EOF)
   {
	   printf("Username: %s\nPassword: %s\nUserCode: %s", dusername, dpass, dcode);
	   i++;
   }
   puts("");
   fclose(member);
   UserInterface();
}

void loginmember()
{
	char username[100], pass[100];
	int fail=0;
	fflush(stdin);
	puts("Welcome You Can LOGIN Now");
	puts("Enter Your UserName:");
	gets(username);
	puts("Enter Your Password:");
	gets(pass);
	
	member=fopen("DATAMEMBER.txt","r");
	while(fscanf(member, "%s %s %s", dusername, dpass, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0) && strcmp(dpass, pass) == 0)
		{
			fail = 1;
			break;
		}
		global++;
	}
	fclose(member);
	if(fail==1)
	{
		printf("\nWelcome! %s\n", dusername);
		puts("=== This is Your Data ===");
		printf("Username : %s\n", dusername);
		printf("User Code : %s\n\n", dcode);
		UIMEMBER();
	}
	else
	{
		puts("User Data Not Found!!!!!!");
		puts("Invalid Username or Password");
		loginmember();
	}
}

void regmember()
{
	char username[100], pass[100];
	fflush(stdin);
	puts("Input your UserName: ");
	gets(username);
	
	
	if(strlen(username)<=6)
	{
		puts("Username must consist more than 6 character");
		return regmember();		
	}
	else
	{
		int i=0, alphabet=0, numerical=0, spec=0;
		while(username[i]!='\0')
		{ 
			
			if((username[i]>=97 && username[i]<=122) || (username[i]>=65 && username[i]<=90))
			{
				alphabet++;
			}
			else if((username[i]>=48 && username[i]<=57))
			{
				numerical++;
			}
			else if(username[i]==46)
			{
				alphabet++;
			}
			else
			{
				spec++;
			}
			i++; 	
		}
	if(spec>=1)
		{
		puts("No Special Character Allowed for UserName!");
		return regmember();
	    }	
	}

	puts("Input your Password:");
	gets(pass);
	
	if(strlen(pass)<=8)
	{
		puts("Password should more than 8 characters");
		return regmember();
	}
	else
    {
		int i=0, sc=0, bc=0, spec=0, numerical=0;
		while(i<strlen(pass))
		{
		
			if(pass[i]>=48 && pass[i]<=57)
				numerical++;	
			else if(pass[i]>=65 && pass[i]<=90)
				bc++;
			else if(pass[i]>=97 && pass[i]<=122)
				sc++;
			else 
				spec++;
			
			i++;
		}
		
		if(sc==0 || bc==0 || spec==0 || numerical==0)
		{
			puts("Password must consists of 1 lowercase, 1 capital letters, 1 number, 1 special character"  );
			return regmember();
		}
		else
		{
			char passrev[50];
			strcpy(passrev,pass);
			strrev(passrev);
			if(strcmp(pass, passrev)==0)
			{
				puts("Password can't be palindrome");
				return regmember();
			}
		}
	}
	savemember(username, pass);
	loginmember();
}

void UU()
{
	char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nBook's Name : %s\nBook's Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
	char us[100];
	int u=1;
	fflush(stdin);
	puts("Input new UserName:");
	gets(us);
	int i=1;
	fptr= fopen("DATAREG.txt", "r");
	while (fscanf(fptr, "%s %s %s", dusername, dpass, dcode) != EOF)
	{
		if(strcmp(dusername, us)==0)
		{
			puts("This Book's Name has already used");
			fclose(fptr);
			UU();
		}
		i++;
	}
	fclose(fptr);
	char bc[10];
	fptr = fopen("DATAREG.txt", "r");
	nf = fopen("Patch.txt", "ab+");
	while (fscanf(fptr, "%s %s", dusername, dcode) != EOF)
	{
		if (u == global)
		{
			strncpy(bc, us, 3);
			bc[3]='\0';
			strupr(bc);
			fprintf(nf, "%s %s-%04d\n", us, bc, global);
		}
		else
		{
			fprintf(nf, "%s %s\n", dusername, dcode);
		}
		u++;
	}
	fclose(fptr);
	fclose(nf);
	remove("DATAREG.txt");
	rename("Patch.txt", "DATAREG.txt");
	printf("\n=== Book's name has been changed ===\n\n");
	fptr=fopen("DATAREG.txt","r");
	printf("Book's Name: %s\nBook's Code: %s-%04d\n\n", us, bc,global);
	fclose(fptr);
	global=1;
	UserInterface();
	
}

void UC()
{
	char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nBook's Name : %s\nBook's Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
	char cod[100];
	int p=1;
	fflush(stdin);
	puts("Input your own Book's Code:");
	gets(cod);
	if(strlen(cod)<8)
	{
		puts("Code should contains at least 8 character");	
		return UC();
	}
	else
	{
		int i=0, bc=0, num=0, spec=0;
		while(cod[i]!='\0')
		{
			if(cod[i]>=65&& cod[i]<=90)
				bc++;
			else if(cod[i]>=48 && cod[i]<=57)
				num++;
			else if(cod[i]=='-')
				spec++;
			
			i++;
			
		}
		if(bc!=3||num!=4||spec!=1)
		{
			puts("Code should contain 3 Capital letters, 1 strip and then 4 number");
			return UC();
		}
	}
	int i=1;
	fptr= fopen("DATAREG.txt", "r");
	while (fscanf(fptr, "%s %s", dusername, dcode) != EOF)
	{
		if(strcmp(dcode, cod)==0)
		{
			puts("This Code has already used");
			fclose(fptr);
			UC();
		}
		i++;
	}
	fclose(fptr);
	fptr = fopen("DATAREG.txt", "r");
	nf = fopen("Patch.txt", "a+");
	while (fscanf(fptr, "%s %s", dusername, dcode) != EOF)
	{
		if (p == global)
		{
			fprintf(nf, "%s %s\n", dusername, cod);
		}
		else
		{
			fprintf(nf, "%s %s\n", dusername, dcode);
		}
		p++;
	}
	fclose(fptr);
	fclose(nf);
	remove("DATAREG.txt");
	rename("Patch.txt", "DATAREG.txt");
	printf("\n===Book's Code has been changed ===\n\n");
	global = 1;
	UserInterface();
}

void DA()
{
	char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nBook's Name : %s\nBook's Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
	int b = 1;

	fptr = fopen("DATAREG.txt", "a+");
	nf = fopen("Patch.txt", "a+");

	while (fscanf(fptr, "%s %s", dusername, dcode) != EOF)
	{
		if (b != global)
		{
			fprintf(nf, "%s %s\n", dusername, dcode);
		}
		b++;
	}
	fclose(fptr);
	fclose(nf);
	remove("DATAREG.txt");
	rename("Patch.txt", "DATAREG.txt");

	printf("\n=== Book data has been deleted!! ===\n\n");
	global = 1;
	UserInterface();
	
}

void DAL()
{
		char username[100], pass[100];
	int fail=0;
	fflush(stdin);
	puts("You should Login as one of admin first if you wanna delete the whole data in database");
	puts("Enter Your UserName:");
	gets(username);
	puts("Enter Your Password:");
	gets(pass);
	
	admin=fopen("DATAADMIN.txt","r");
	while(fscanf(admin, "%s %s %s", dusername, dpass, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0) && strcmp(dpass, pass) == 0)
		{
			fail = 1;
			break;
		}
		permission++;
	}
	fclose(admin);
	
	if(fail==1)
	{
		printf("\nWelcome! %s\n", dusername);
		puts("=== This is Your Data ===");
		printf("Username : %s\n", dusername);
		printf("Admin Code : %s\n\n", dcode);
		remove("DATAREG.txt");
		puts("Database is down now");
		UserInterface();
	}
	else
	{
		puts("Admin Data Not Found!!!!!!");
		puts("Invalid Username or Password");
		UserInterface();
	}
	
}

void loginadmin()
{
	char username[100], pass[100];
	int fail=0;
	fflush(stdin);
	puts("Enter Your UserName:");
	gets(username);
	puts("Enter Your Password:");
	gets(pass);
	
	admin=fopen("DATAADMIN.txt","r");
	while(fscanf(admin, "%s %s %s", dusername, dpass, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0) && strcmp(dpass, pass) == 0)
		{
			fail = 1;
			break;
		}
		permission++;
	}
	fclose(admin);
	if(fail==1)
	{
		printf("\nWelcome! %s\n", dusername);
		puts("=== This is Your Data ===");
		printf("Username : %s\n", dusername);
		printf("Admin Code : %s\n\n", dcode);
		UserInterface();
	}
	else
	{
		puts("Admin Data Not Found!!!!!!");
		puts("Invalid Username or Password");
		loginadmin();
	}
}


void login()
{
	time(&ambil_waktu);
char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nBook's name : %s\nBook's Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);

   
	char username[100];
	int borrow;
	int fail=0;
	fflush(stdin);
	puts("Enter Book's Name:");
	gets(username);
	fptr=fopen("DATAREG.txt","r");
	while(fscanf(fptr, "%s %s", dusername, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0) )
		{
			fail = 1;
			break;
		}
		global++;
	}
	fclose(fptr);
	if(fail==1)
	{
		printf("How long you will borrow this book?\n");
		scanf("%d",&borrow);
		if(borrow==1)
		{
		puts("|==================== This is Your Borrow Card =====================|");
		printf("|Book's Name : %s						    |\n", dusername);
		printf("|Book's Code : %s                           		    |\n", dcode);
		printf("|You will borrow this book for: %d Day\t\t\t            |\n", borrow);
		printf("|Time/Day You Starting borrow this book: %s|", ctime (&ambil_waktu));
		puts("==================== Enjoy to read your books =====================|\n");
		UIMEMBER();
		}
		else
		{
		puts("=== This is Your Receipt ===");
		printf("Book's Name : %s\n", dusername);
		printf("Book's Code : %s\n", dcode);
		printf("You will borrow this book for: %d Days\n",borrow);
		printf("Time/Day You Starting borrow this book: %s\n\n", ctime (&ambil_waktu));
		UIMEMBER();
		}
		
	}
	else
	{
		puts("Book Data Not Found!!!!!!");
		puts("Invalid Book's name or code");
		UserInterface();
	}
}

void logu()
{
char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nUsername : %s\nUser Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
	char username[100];
	int fail=0;
	fflush(stdin);
	puts("Enter Book's Name you want to update first");
	puts("Enter Your Book's Name:");
	gets(username);
	
	fptr=fopen("DATAREG.txt","r");
	while(fscanf(fptr, "%s %s", dusername, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0) )
		{
			fail = 1;
			break;
		}
		global++;
	}
	fclose(fptr);
	if(fail==1)
	{
		puts("=== This is Your Data ===");
		printf("Book's Name : %s\n", dusername);
		printf("Book's Code : %s\n\n", dcode);
		UU();
	}
	else
	{
		puts("Book's Data Not Found!!!!!!");
		puts("Invalid Book's name or code");
		UserInterface();
	}
}

void logindel()
{
char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nUsername : %s\nUser Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
	char username[100];
	int fail=0;
	fflush(stdin);
	puts("Enter The Book's name you want to delete");
	puts("Enter The Book's Name:");
	gets(username);
	
	fptr=fopen("DATAREG.txt","r");
	while(fscanf(fptr, "%s %s", dusername, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0) )
		{
			fail = 1;
			break;
		}
		global++;
	}
	fclose(fptr);
	if(fail==1)
	{
		puts("=== This is Your Data ===");
		printf("Book's name : %s\n", dusername);
		printf("Book's Code : %s\n\n", dcode);
		DA();
	}
	else
	{
		puts("Book's Data Not Found!!!!!!");
		puts("Invalid Book's Name or Password");
		UserInterface();
	}
}

void logic()
{
	char a[100];
	int k= 0, j=0;
   fptr = fopen("DATAREG.txt", "r");
   puts("=== LIST DATA ===");
   while(fscanf(fptr, "%s", a)!=EOF)
   {
	   if (j==0)
	   {
			strcpy(dusername, a);
			j++;
       } 
		else if (j==1)
		{
			j=k+1;
			j=j/2;
			printf("=== %d ===\nUsername : %s\nUser Code : %s\n", j, dusername, a);
			j=0;
		}
	   k++;
   }
   puts("");
   fclose(fptr);
   char username[100];
   int fail=0;
	fflush(stdin);
	puts("Enter the book's name you want to update");
	puts("Enter Your Book's Name:");
	gets(username);;
	
	fptr=fopen("DATAREG.txt","r");
	while(fscanf(fptr, "%s %s", dusername, dcode)!=EOF)
	{
		if ((strcmp(dcode, username) == 0 || strcmp(dusername, username) == 0))
		{
			fail = 1;
			break;
		}
		global++;
	}
	fclose(fptr);
	if(fail==1)
	{
		puts("=== This is Your Data ===");
		printf("Book's Name : %s\n", dusername);
		printf("Book's Code : %s\n\n", dcode);
		UC();
	}
	else
	{
		puts("Book's Data Not Found!!!!!!");
		puts("Invalid Book's Name or Password");
		UserInterface();
	}
}


void UserInterface()
{
	int chc;
	puts("MENU\n1. REGISTER A BOOK\n2. REGISTER AN ADMIN\n3. List of Book's Data\n4. Update Username\n5. Delete a Book\n6. Create Your Own UserCode\n7. BRING DOWN THE WHOLE DATABASE\n8. Member's Data List\n9. EXIT\nEnter Menu:");
	scanf("%d",&chc);
	
	switch(chc)
	{
	case 1:
		reg();
		break;
	case 2:
		regad();
		break;
	case 3:
		datlist();
		break;
	case 4:
		logu();
		break;
	case 5:
		logindel();
		break;
	case 6:
		logic();
		break;
	case 7:
		DAL();
		break;
	case 8:
		datlistmember();
		break;
	case 9:
		puts("Goodbye see ya later");
		break;
	default:
	puts("Gaada pilihannya tolong, jan aneh aneh pack/buck");
	UserInterface();
	break;
	}
}

void UIMEMBER()
{
	int choice;
	puts("MENU\n1. Book's List\n2. Borrow a Book\n3. EXIT\nEnter Menu:");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		datlistmemberbook();
		break;
	case 2:
		login();
		break;
	case 3:
		puts("Have Fun Bro/Sist");
		break;
	default:
		puts("There is no choice like that in da menu come on");
		UIMEMBER();
		break;
	}
}

int main(int argc, char** argv)
{
	int pil;
	puts("======================================WELCOME TO UMM NATIONAL TREASURE LIBRARY UwU======================================");
	puts("1. REGISTER AS ADMIN\n2. LOGIN AS ADMIN\n3. REGISTER AS MEMBER\n4. LOGIN AS MEMBER\nEnter Choice:");
	scanf("%d",&pil);
	switch(pil)
	{
	case 1:
		regad();
		break;
	case 2:
		loginadmin();
		break;
	case 3:
		regmember();
		break;
	case 4:
		loginmember();
		break;
	default:
		break;
	}
	return 0;
}
