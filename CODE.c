/*
	JUST CODE UNTIL YOU CRACK IT!
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>
#include<unistd.h>
#include<dos.h>
int sugi=97;					// used to display option numbers in search function
int sugin=0;					// used to display option numbers in searchN function
char* something[20]={NULL};		//used to store pointers of code to be displayed in suggestion function
char* somethingN[20]={NULL};	//used to store pointers of name to be displayed in suggestionN function

typedef struct data{
	char name[15];         	// name of employee is stored
	char sname[15];			// surname of employee is stored
	char fname[32];			// full name in form "name surname" is stored
	char code[15];			// code of employee is stored
	char department[15];	// department of employee is stored
	float salary;			// Salary per month of employee is stored
}DATA;

typedef struct deptdata{	// used to keep track of record of average salary per department
	float salcse,salmech,saltronics,saltrical,salcivil,salit;
	int empcntcse,empcntmech,empcnttronics,empcnttrical,empcntcivil,empcntit;
}Dept_Data;

Dept_Data dpdata={0};

typedef struct TRIE_DATA_STRUCTURE_N{
	struct TRIE_DATA_STRUCTURE_N* children[27];
	bool datapresent;
	DATA* getdata;
}TRIEN;

typedef struct TRIE_DATA_STRUCTURE_C{
	struct TRIE_DATA_STRUCTURE_C* children[11];
	bool datapresent;		// bool is true if data is present
	DATA* getdata;
}TRIEC;

TRIEN* createNodeN(){
	int index=0;
	TRIEN* pnew=(TRIEN*)malloc(sizeof(TRIEN));
	pnew->datapresent=false;
	for(index=0;index<27;index++){
		pnew->children[index]=NULL;
	}                                                       
	return pnew;
}

TRIEC* createNodeC(){
	int index=0;
	TRIEC* pnew=(TRIEC*)malloc(sizeof(TRIEC));
	pnew->datapresent=false;
	for(index=0;index<11;index++){
		pnew->children[index]=NULL;
	}
	return pnew;
}

void insertcode(TRIEC* root,DATA* data1){
	int i=0;
	TRIEC* travel=root;    	// travel is trie pointer used to traverse trie
	for(i=0;i<strlen(data1->code);i++){
		int index=data1->code[i]-'0';
		if(travel->children[index]==NULL){
			travel->children[index]=createNodeC();
		}
		travel=travel->children[index];
	}
	travel->datapresent=true;
	travel->getdata=data1;
}
void insertname(TRIEN* root,DATA* data1){
	int i=0,index;
	TRIEN* travel=root;

	if(strcmp(data1->department,"Mechanical")==0){
		dpdata.empcntmech++;
		dpdata.salmech+=data1->salary;
	}
	else if(strcmp(data1->department,"Civil")==0){
		dpdata.empcntcivil++;
		dpdata.salcivil+=data1->salary;
	}
	else if(strcmp(data1->department,"CSE")==0){
		dpdata.empcntcse++;
		dpdata.salcse+=data1->salary;
	}
	else if(strcmp(data1->department,"IT")==0){
		dpdata.empcntit++;
		dpdata.salit+=data1->salary;
	}
	else if(strcmp(data1->department,"Electrical")==0){
		dpdata.empcnttrical++;
		dpdata.saltrical+=data1->salary;
	}
	else if(strcmp(data1->department,"Electronics")==0){
		dpdata.empcnttronics++;
		dpdata.saltronics+=data1->salary;
	}
	for(i=0;i<strlen(data1->fname);i++){
		if(data1->fname[i]==' ')
			index=26;
		else
		 	index=data1->fname[i]-'a';
		if(travel->children[index]==NULL){
			travel->children[index]=createNodeN();
		}
		travel=travel->children[index];
	}
	travel->datapresent=true;
	travel->getdata=data1;
}
void insertfirstname(TRIEN* root,DATA* data1){
	int i=0,index;
	TRIEN* travel=root;
	for(i=0;i<strlen(data1->name);i++){
		if(data1->name[i]==' ')
			index=26;
		else
		 	index=data1->name[i]-'a';
		if(travel->children[index]==NULL){
			travel->children[index]=createNodeN();
		}
		travel=travel->children[index];
	}
	travel->datapresent=true;
	travel->getdata=data1;
}
void insertlastname(TRIEN* root,DATA* data1){
	int i=0,index;
	TRIEN* travel=root;
	for(i=0;i<strlen(data1->sname);i++){
		if(data1->sname[i]==' ')
			index=26;
		else
		 	index=data1->sname[i]-'a';
		if(travel->children[index]==NULL){
			travel->children[index]=createNodeN();
		}
		travel=travel->children[index];
	}
	travel->datapresent=true;
	travel->getdata=data1;
}


void search(TRIEC* root,char* key)
{
	int i,index;
	TRIEC* travel=root;
	
	for(i=0;i<strlen(key);i++)
	{
		index=key[i]-'0';
		if(index<0 || index>=11)
		{
			printf("\tDATA NOT FOUND\n");
			return;
		}
		if(travel->children[index]==NULL)
		{
			travel=NULL;
			break;
		}
		travel=travel->children[index];	
	}
	if(travel!=NULL)
	{
		if(travel->datapresent==true)
		{
			printf("\tNAME OF EMPLOYEE : %s\n",travel->getdata->fname);
			printf("\tWORKING IN DEPARTMENT OF %s\n",travel->getdata->department);
			printf("\tSALARY PER MONTH : Rs. %f \n",travel->getdata->salary);
			return;
		}
		else 
		{
			printf("\tDATA NOT FOUND\n");
			return;
		}
	}
	else 
	{
		printf("\tDATA NOT FOUND\n");
		return;
	}
}
void searchN(TRIEN* root,char* key)
{
	int i,index;
	TRIEN* travel=root;
	
	for(i=0;i<strlen(key);i++)
	{
		if(key[i]==32) index=26;
		else
		index=key[i]-'a';
		if(index<0 || index>=27)
		{
			printf("\tDATA NOT FOUND\n");
			return;
		}
		if(travel->children[index]==NULL)
		{
			travel=NULL;
			break;
		}
		travel=travel->children[index];	
	}
	if(travel!=NULL)
	{
		if(travel->datapresent==true)
		{
			printf("\tUNIQUE ID OF EMPLOYEE : %s\n",travel->getdata->code);
			printf("\tWORKING IN DEPARTMENT OF %s\n",travel->getdata->department);
			printf("\tSALARY PER MONTH : %f Rs.\n",travel->getdata->salary);
			return;
		}
		else 
		{
			printf("\tDATA NOT FOUND\n");
			return;
		}
	}
	else 
	{
		printf("\tDATA NOT FOUND\n");
		return;
	}
}
void deleteN(TRIEN* root,char* key)
{
	int i,index;
	TRIEN* travel=root;
	
	for(i=0;i<strlen(key);i++)
	{
		if(key[i]==32) index=26;
		else
		index=key[i]-'a';
		if(index<0 || index>=27)
		{
			printf("\tDATA NOT FOUND\n");
			return;
		}
		if(travel->children[index]==NULL)
		{
			travel=NULL;
			break;
		}
		travel=travel->children[index];	
	}
	if(travel!=NULL)
	{
		if(travel->datapresent==true)
		{
			travel->datapresent=false;
			printf("\nRECORD DELETED\n");
			return;
		}
		else 
		{
			printf("\tDATA NOT FOUND\n");
			return;
		}
	}
	else 
	{
		printf("\tDATA NOT FOUND\n");
		return;
	}
}

void display_EMPCNT_AND_AVGSAL()
{
	printf("  =========================================================================================\n");
	printf("    Department                          Employee Count                     Average Salary \n");
    printf("  =========================================================================================\n");
	if(dpdata.empcntmech==0)
		printf("    1.%-15s%10d%10d\n","Mechanical",0,0);
	else
		printf("    1.Mechanical                              %2d                            %f\n",dpdata.empcntmech,dpdata.salmech/dpdata.empcntmech);
	if(dpdata.empcntcivil==0)
		printf("    2.Civil		                            0                                   0\n");
	else
		printf("    2.Civil 	                              %2d                            %f\n",dpdata.empcntcivil,dpdata.salcivil/dpdata.empcntcivil);
	if(dpdata.empcntcse==0)
		printf("    3.CSE		                              0                                   0\n");
	else
		printf("    3.CSE		                      %2d                            %f\n",dpdata.empcntcse,dpdata.salcse/dpdata.empcntcse);
	if(dpdata.empcntit==0)
		printf("    4.IT		                              0                                   0\n");
	else
		printf("    4.IT		                      %2d                            %f\n",dpdata.empcntit,dpdata.salit/dpdata.empcntit);
	if(dpdata.empcnttrical==0)
		printf("    5.Electrical		                      0                                   0\n");
	else
		printf("    5.Electrical                              %2d                            %f\n",dpdata.empcnttrical,dpdata.saltrical/dpdata.empcnttrical);
	if(dpdata.empcnttronics==0)
		printf("    6.Electronics		                      0                                   0\n");
	else
		printf("    6.Electronics                             %2d                            %f\n",dpdata.empcnttronics,dpdata.saltronics/dpdata.empcnttronics);
		
	printf("  =========================================================================================\n");
}

void displayViaName(TRIEN* travel)
{
	int i,a;
	
	
			if(travel->datapresent == true)
			{
				printf("          %-30s                   %-15s              %-15s\n",travel->getdata->fname,travel->getdata->department,travel->getdata->code);
			}
					
	for(i=0;i<27;i++)
	{
		if(travel->children[i] != NULL)
		{
			TRIEN* trav = travel->children[i];
			displayViaName(trav);
		}
	}
}
void ModifyFile(TRIEN* travel)
{
	int i,a;
	
	
			if(travel->datapresent == true)
			{
				FILE *fp=fopen("Input1.txt","a");
				fprintf(fp,"%s\n",travel->getdata->name);
				fprintf(fp,"%s\n",travel->getdata->sname);
				fprintf(fp,"%s\n",travel->getdata->department);
				fprintf(fp,"%s\n",travel->getdata->code);
				fprintf(fp,"%f\n",travel->getdata->salary);
				fclose(fp);
			}
					
	for(i=0;i<27;i++)
	{
		if(travel->children[i] != NULL)
		{
			TRIEN* trav = travel->children[i];
			ModifyFile(trav);
		}
	}
}
TRIEC* substr(TRIEC* root,char* key)
{
	int i,index;
	TRIEC* travel=root;
	
	for(i=0;i<strlen(key);i++)
	{
		index=key[i]-'0';
		
		if(travel->children[index]==NULL)
		{
			travel=NULL;
			break;
		}
		travel=travel->children[index];	
	}
	if(travel!=NULL)
	{
		return travel;
	}
	else 
	{
		return (NULL);
	}
}

void sugestName(TRIEC* travel)
{
	int i,a;
	if(travel!=NULL)
	{
	
	if(travel->datapresent == true)
	{
		printf("%c %-15s\n",sugi,travel->getdata->code);
		something[sugi-97]=(travel->getdata->code);
		sugi++;
	}				
	for(i=0;i<11;i++)
	{
		if(travel->children[i] != NULL)
		{
			TRIEC* trav = travel->children[i];
			sugestName(trav);
		}
	}
	}
}

TRIEN* substrN(TRIEN* root,char* key)
{
	int i,index;
	TRIEN* travel=root;
	
	for(i=0;i<strlen(key);i++)
	{
		if(key[i]==' ')
			index=26;
		else
			index=key[i]-'a';
		
		if(travel->children[index]==NULL)
		{
			travel=NULL;
			break;
		}
		travel=travel->children[index];	
	}
	if(travel!=NULL)
	{
		return travel;
	}
	else 
	{
		return (NULL);
	}
}

void sugestNameN(TRIEN* travel)
{
	int i,a;
	if(travel!=NULL)
	{
	if(travel->datapresent == true)
	{
		printf("%d %-15s\n",sugin,travel->getdata->fname);
		somethingN[sugin]=(travel->getdata->fname);
		sugin++;
	}				
	for(i=0;i<27;i++)
	{
		if(travel->children[i] != NULL)
		{
			TRIEN* trav = travel->children[i];
			sugestNameN(trav);
		}
	}
	}
}

void sugestNameNfirst(TRIEN* travel)
{
	int i,a;
	if(travel!=NULL)
	{
	if(travel->datapresent == true)
	{
		printf("%d %-15s\n",sugin,travel->getdata->name);
		somethingN[sugin]=(travel->getdata->name);
		sugin++;
	}				
	for(i=0;i<27;i++)
	{
		if(travel->children[i] != NULL)
		{
			TRIEN* trav = travel->children[i];
			sugestNameN(trav);
		}
	}
	}
}

void menu()
{
	printf("\n\n====================================COLLEGE EMPLYOEE DETAILS MANAGEMENT SYSTEM======================================\n\n");
	printf("\t1. EMPLOYEE COUNT AND AVERAGE SALARY\n");
	printf("\t2. Lexicographically ordered data\n");
	printf("\t3. Search data with Code\n");
	printf("\t4. Search data with Full Name\n");
	printf("\t5. Search data with First Name\n");
	printf("\t6. Search data with Last Name\n");
	printf("\t7. Add Employee Record\n");
	printf("\t8. Delete Employee Record\n");
	printf("\t9. Exit\n");
	printf("\n\tOPTION:_\b");
	
}

int main()
{
	int noe,i,opt;
	char ch;
	FILE *fp;
	fp=fopen("Input1.txt","r");
	
/*///////////////////////////*/	

	TRIEN* rootn;				 	// trie of name is created
	rootn=createNodeN();
	rootn->datapresent=false;
	TRIEN* rootfirstn;
	rootfirstn=createNodeN();
	rootfirstn->datapresent=false;
	TRIEN* rootlastn;
	rootlastn=createNodeN();
	rootlastn->datapresent=false;
	
/*///////////////////////////*/	

	TRIEC* rootc;					// trie of code is created
	rootc=createNodeC();
	rootc->datapresent=false;
	
/*///////////////////////////*/	

	fscanf(fp,"%d",&noe);
	DATA* a;
	for(i=0;i<noe;i++) // fullnames are stored in trie
	{
		char name[15],code[15],dept[15],sname[20],fname[32];
		float sal;
		a=(DATA*)malloc(sizeof(DATA));
		fscanf(fp,"%s %s %s %s %f",&name,&sname,&dept,&code,&sal);
		strcpy(a->code,code);
		strcpy(a->department,dept);
		strcpy(a->name,name);
		strcpy(a->sname,sname);
		a->salary=sal;
		strcpy(fname,name);
		strcat(fname," ");
		strcat(fname,sname);
		strcpy(a->fname,fname);
		insertname(rootn,a);
	}
	
/*///////////////////////////*/	

	fseek(fp, 0, SEEK_SET);
	fscanf(fp,"%d",&noe);
	for(i=0;i<noe;i++) 	// codes are stored in trie
	{
		char name[15],code[15],dept[15],sname[20],fname[32];
		float sal;
		a=(DATA*)malloc(sizeof(DATA));
		fscanf(fp,"%s %s %s %s %f",&name,&sname,&dept,&code,&sal);
		strcpy(a->code,code);
		strcpy(a->department,dept);
		strcpy(a->name,name);
		strcpy(a->sname,sname);
		a->salary=sal;
		strcpy(fname,name);
		strcat(fname," ");
		strcat(fname,sname);
		strcpy(a->fname,fname);
		insertcode(rootc,a);
	}
	
/*///////////////////////////*/

	fseek(fp, 0, SEEK_SET);
	fscanf(fp,"%d",&noe);
	for(i=0;i<noe;i++) // first name data is inserted in trie
	{
		char name[15],code[15],dept[15],sname[20],fname[32];
		float sal;
		a=(DATA*)malloc(sizeof(DATA));
		fscanf(fp,"%s %s %s %s %f",&name,&sname,&dept,&code,&sal);
		strcpy(a->code,code);
		strcpy(a->department,dept);
		strcpy(a->name,name);
		strcpy(a->sname,sname);
		a->salary=sal;
		strcpy(fname,name);
		strcat(fname," ");
		strcat(fname,sname);
		strcpy(a->fname,fname);
		insertfirstname(rootfirstn,a);
	}	
	
/*///////////////////////////*/

	fseek(fp, 0, SEEK_SET);
	fscanf(fp,"%d",&noe);
	for(i=0;i<noe;i++)	// lastname is stored in trie
	{
		char name[15],code[15],dept[15],sname[20],fname[32];
		float sal;
		a=(DATA*)malloc(sizeof(DATA));
		fscanf(fp,"%s %s %s %s %f",&name,&sname,&dept,&code,&sal);
		strcpy(a->code,code);
		strcpy(a->department,dept);
		strcpy(a->name,name);
		strcpy(a->sname,sname);
		a->salary=sal;
		strcpy(fname,name);
		strcat(fname," ");
		strcat(fname,sname);
		strcpy(a->fname,fname);
		insertlastname(rootlastn,a);
	}
		
/*///////////////////////////*/

	while(1){
		system("cls");
		menu();
		char ex;
		scanf("%d",&opt);
		switch(opt){
			case 1:
				system("cls");
				printf("\n\t\t\tEMPLOYEE COUNT AND AVERAGE SALARY PER DEPARTMENT\n");
				display_EMPCNT_AND_AVGSAL();
				printf("\n\n");
				scanf("%c",&ch);
				printf("\nEnter any key to continue: ");
				scanf("%c",&ex);
				break;
			case 2:
				system("cls");
				printf("\n\t\t\tNAME OF STUDENTS AND THEIR RESPECTIVE DEPARTMENT\n");
				printf("  =========================================================================================================\n");
				printf("               NAME                                        DEPARTMENT                      CODE\n");
				printf("  =========================================================================================================\n");
				displayViaName(rootn);
				printf("  =========================================================================================================\n");
				printf("\n\n");
				scanf("%c",&ch);
				printf("\nEnter any key to continue: ");
				scanf("%c",&ex);

				break;
			case 3:
			    
				system("cls");
				int refi=0,cnt=0,g,fail1=0;
				int flg=1;
				char arr[1500],tmmp;
				int len=1;
				do
				{
				system("cls");
				printf("  \n\t\t\tENTER CODE TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tCODE : ");
				if(flg)
				{
					char ch = _getch() ;
					if(ch>='a'&&ch<='z')
					{
						printf("Enter correct code.\n");
						fail1=1;
						break;
					}
					arr[refi++]= ch;
					arr[refi]='\0';
				}
				for(g=0;g<refi;g++)
				{
					printf("%c",arr[g]);
				}
				if(g)
				printf("\n");
				sugestName(substr(rootc,arr));
				sugi=97;
				printf("Option : ");
				tmmp = _getch() ;
				if(tmmp=='.')break;
				len++;
				if(tmmp>='a' && tmmp<='z')
				{
					system("cls");
					strcpy(arr,something[tmmp-97]);
					break;
				}
				else
				{
					arr[refi++]= tmmp;
					arr[refi]='\0';
					flg=0;
				}
				
				}while(!_kbhit() && len<=10);
				if(fail1==0)
				{
				system("cls");
				printf("  \n\t\t\tENTER CODE TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tCODE : %s",arr);
				
				char enthit;
				scanf("%c",&enthit);
				//printf("  =========================================================================================\n");
				printf("\n");
				search(rootc,arr);
				printf(" \n=========================================================================================\n");
				}
				printf("\nEnter any key to continue: ");
				scanf("%c",&ch);
				scanf("%c",&ch);
				//scanf("%c",&ex);
				break;
				//system("cls");
			/*///////////////////////////
			
			sugin=0;
			sugestNameN(substrN(rootn,"p"));
			
			/*///////////////////////////*/
			case 4:
				system("cls");
				int refiN=0,cntN=0,gN=0;
				int flgN=1;
				char arrN[1500],tmmpN;
				int lenN=1;
				while(!_kbhit())
				{
				system("cls");
				printf("  \n\t\t\tENTER NAME TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tNAME : ");
				if(flgN)
				{
					char ch = _getch();
					if(ch=='.')
						break;
					arrN[refiN++]= ch;
					arrN[refiN]='\0';
				}
				printf("%s\n",arrN);
				sugestNameN(substrN(rootn,arrN));
				sugin=0;
				printf("Option : ");
				tmmpN = _getch() ;
				lenN++;
				if(tmmpN>='0' && tmmpN<='9')
				{
					system("cls");
					strcpy(arrN,somethingN[tmmpN-48]);
					break;
				}
				else
				{
					if(tmmpN=='.')
						break;
					arrN[refiN++]= tmmpN;
					arrN[refiN]='\0';
					flgN=0;
				}
				
				}
				system("cls");
				printf("  \n\t\t\tENTER NAME TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tNAME : %s",arrN);
				char enthitN;
				scanf("%c",&enthitN);
				printf("\n");
				searchN(rootn,arrN);
				printf("  =========================================================================================\n");
				printf("\nEnter any key to continue: ");
				scanf("%c",&ex);
				break;
			case 5:
				system("cls");
				refiN=0,cntN=0,gN=0;
				flgN=1;
				arrN[1500],tmmpN;
				lenN=1;
				while(!_kbhit())
				{
				system("cls");
				printf("  \n\t\t\tENTER FIRST NAME TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tNAME : ");
				if(flgN)
				{
					char ch = _getch();
					if(ch=='.')
						break;
					arrN[refiN++]= ch;
					arrN[refiN]='\0';
				}
				printf("%s\n",arrN);
				sugestNameNfirst(substrN(rootfirstn,arrN));
				sugin=0;
				printf("Option : ");
				tmmpN = _getch() ;
				lenN++;
				if(tmmpN>='0' && tmmpN<='9')
				{
					system("cls");
					strcpy(arrN,somethingN[tmmpN-48]);
					break;
				}
				else
				{
					if(tmmpN=='.')
						break;
					arrN[refiN++]= tmmpN;
					arrN[refiN]='\0';
					flgN=0;
				}
				
				}
				system("cls");
				printf("  \n\t\t\tENTER FIRST NAME TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tNAME : %s",arrN);
				enthitN;
				scanf("%c",&enthitN);
				printf("\n");
				
				searchN(rootn,arrN);
				printf("  =========================================================================================\n");
				printf("\nEnter any key to continue: ");
				scanf("%c",&ex);
				break;
			case 6:
				system("cls");
				refiN=0,cntN=0,gN=0;
				flgN=1;
				arrN[1500],tmmpN;
				lenN=1;
				while(!_kbhit())
				{
				system("cls");
				printf("  \n\t\t\tENTER LAST NAME TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tNAME : ");
				if(flgN)
				{
					char ch = _getch();
					if(ch=='.')
						break;
					arrN[refiN++]= ch;
					arrN[refiN]='\0';
				}
				printf("%s\n",arrN);
				sugestNameN(substrN(rootlastn,arrN));
				sugin=0;
				printf("Option : ");
				tmmpN = _getch() ;
				lenN++;
				if(tmmpN>='0' && tmmpN<='9')
				{
					system("cls");
					strcpy(arrN,somethingN[tmmpN-48]);
					break;
				}
				else
				{
					if(tmmpN=='.')
						break;
					arrN[refiN++]= tmmpN;
					arrN[refiN]='\0';
					flgN=0;
				}
				
				}
				system("cls");
				printf("  \n\t\t\tENTER LAST NAME TO VIEW DETAILS OF A EMPLOYEE\n");
				printf("  =========================================================================================\n");
				printf("\tNAME : %s",arrN);
				enthitN;
				scanf("%c",&enthitN);
				printf("\n");
				searchN(rootn,arrN);
				printf("  =========================================================================================\n");
				printf("\nEnter any key to continue: ");
				scanf("%c",&ex);
				break;
			case 7:
				system("cls");
				fp=fopen("Input1.txt","a+");
				int j;
				DATA em;
				int op;
				printf("  \n\tADD DETAILS OF A EMPLOYEE TO SYSTEM\n");
				printf("  =========================================================================================\n");
				printf("\tName : ");
				scanf("%s",em.name);
				printf("\tSurname : ");
				scanf("%s",em.sname);
				printf("\tDepartment :\n");
				printf("\t1. CSE\n");
				printf("\t2. Mechanical\n");
				printf("\t3. IT\n");
				printf("\t4. Civil\n");
				printf("\t5. Electrical\n");
				printf("\t6. Electronics\n");
				printf("\tOPTION : ");
				scanf("%d",&op);
				switch(op)
				{
					case 1: strcpy(em.department,"CSE");break;
					case 2: strcpy(em.department,"Mechanical");break;
					case 3: strcpy(em.department,"IT");break;
					case 4: strcpy(em.department,"Civil");break;
					case 5: strcpy(em.department,"Electrical");break;
					case 6: strcpy(em.department,"Electronics");break;
				}
				printf("\tEnter Salary per month : ");
				scanf("%f",&em.salary);
				char str[16];
				srand(time(0));
				for(j=0;j<=10;j++)
				{
					int rr;
					if(j!=3 && j!=7)
					rr=rand()%10 +48;
					else
					rr=58;
					str[j]=rr;
				}
				str[j]='\0';
				strcpy(em.code,str);
				insertcode(rootc,&em);
				insertfirstname(rootfirstn,&em);
				insertlastname(rootlastn,&em);
				char fname[30];
				strcpy(fname,em.name);
				strcat(fname," ");
				strcat(fname,em.sname);
				strcpy(em.fname,fname);
				insertname(rootn,&em);
				fseek(fp,0,SEEK_END);
				fprintf(fp,"%s\n%s\n%s\n%s\n%f\n",em.name,em.sname,em.department,em.code,em.salary);
				printf("\n\tDATA ADDED SUCESSFULLY");
				noe++;
				fp=fopen("Input1.txt","w");
				fprintf(fp,"%d\n",noe);
				fclose(fp);
				ModifyFile(rootn);
				scanf("%c",&ex);
				break;
			case 8:
				system("cls");
				char nn[15],ss[15],ch[30];
				scanf("%c",&ex);
				printf("\n\n\tEnter the name of the Employee Record to be deleted\n");
				printf("  =========================================================================================\n");
				printf("\n\tNAME : ");
				scanf("%s",nn);
				printf("\tSurname : ");
				scanf("%s",ss);
				strcpy(ch,nn);
				strcat(ch," ");
				strcat(ch,ss);
				deleteN(rootn,ch);
				system("cls");
				deleteN(rootfirstn,nn);
				system("cls");
				deleteN(rootlastn,ss);
				fp=fopen("Input1.txt","w");
				fprintf(fp,"%d\n",noe-1);
				fclose(fp);
				ModifyFile(rootn);
				printf("\nEnter any key to continue: ");
				scanf("%c",&ex);
				scanf("%c",&ex);
				noe--;
				break;
			default:
				exit(0);
		}
	}

	return 0;
}
