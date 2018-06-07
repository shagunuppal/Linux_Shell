#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "path.c"

int main(int argc, char const *argv[])
{
	if(strcmp(argv[1],"-v")==0)
	{

		if(strcmp(argv[2],"-p")==0)
		{
			mkdir_v_p(argv[3]);
		}
		else
		{
			mkdir_v(argv[2]);
		}
	}
	else if(strcmp(argv[1],"-p")==0)
	{
		if(strcmp(argv[2],"-v")==0)
		{
			mkdir_v_p(argv[3]);						
		}
		else
		{
			mkdir_p(argv[2]);
		}
	}
	else
	{
		char *s;
		s=argv[1];
		make_dir(s);
	}
	return 0;
}
void mkdir_v(char *arg)
{
	struct stat st = {0};
	struct stat buf;
    stat(("%s/%s",path(),arg), &buf);
			
	if(chdir(arg)==0)
		printf("%s\n","File already exists." );
	else if (stat(arg, &st) == -1)
	{
    	mkdir(arg, 0700);
    	printf("mkdir: created directory \'%s\'\n",arg);
	}
}

void mkdir_v1(char *arg)
{
	struct stat st = {0};
	struct stat buf;
    stat(("%s/%s",path(),arg), &buf);
			
	if(chdir(arg)==0)
		printf("");
	else if (stat(arg, &st) == -1)
	{
    	mkdir(arg, 0700);
    	printf("mkdir: created directory \'%s\'\n",arg);
	}
}


void mkdir_p(char *u)
{	

	char *copy=malloc(sizeof(char)*1024);
	strcpy(copy, u);
	strtok(copy,"/");	

	make_dir1(copy);

	char *c2=malloc(sizeof(char)*1024);
	strcpy(c2,copy);
	strcat(c2, "/");

	while(copy != NULL)
	{
		copy = strtok(NULL,"/");
		strcat(c2,copy);
		make_dir1(c2);
		strcat(c2,"/");	
	}
}

void mkdir_v_p(char *u)
{
	char *copy=malloc(sizeof(char)*1024);
	strcpy(copy, u);
	strtok(copy,"/");	
	mkdir_v1(copy);
	char *c2=malloc(sizeof(char)*1024);
	strcpy(c2, copy);
	strcat(c2, "/");

	while(copy != NULL)
	{
		copy = strtok(NULL,"/");
		strcat(c2,copy);
		mkdir_v1(c2);	
		strcat(c2,"/");	
	}
}

void make_dir(char *arg)
{
	struct stat st = {0};
	struct stat buf;
    stat(("%s/%s",path(),arg), &buf);
			
	if(chdir(arg)==0)
		printf("%s\n","File already exists." );
	else if (stat(arg, &st) == -1)
	{
    	mkdir(arg, 0700);
	}
}

void make_dir1(char *arg)
{
	struct stat st = {0};
	
	if (stat(arg, &st) == -1)
	{
    	mkdir(arg, 0700);
	}
}