#include <stdio.h>
#include <stdlib.h>

void history_command()
{
	FILE *f; 
	f=fopen("/home/shagunuppal/Desktop/OS_Assignment0/history_data.txt","r");
	size_t length = 255;
	char *line=malloc(sizeof(char)*length);
	int pt;
	int increment=1;

	if(f!=NULL)
	{

		while(fgets(line,length,f) != NULL)
		{
			printf("%d %s",increment,line);
			increment++;
		}
		fclose(f);
	}

	FILE *f1; 
	f1=fopen("/home/shagunuppal/Desktop/OS_Assignment0/standby.txt","r");
	size_t len = 255;
	char *line1=malloc(sizeof(char)*len);
	int pt1;

	if(f1!=NULL)
	{

		while(fgets(line1,len,f1) != NULL)
		{
			printf("%d %s",increment,line1);
			increment++;
		}
		fclose(f1);
	}
}

void history_c()
{
	FILE *f1; 
	f1=fopen("/home/shagunuppal/Desktop/OS_Assignment0/standby.txt","r");
	size_t len = 255;
	char *line1=malloc(sizeof(char)*len);
	int pt1;
	int inc=1;

	if(f1!=NULL)
	{

		while(fgets(line1,len,f1) != NULL)
		{
			printf("%d %s",inc,line1);
			inc++;
		}
		fclose(f1);
	}
}
