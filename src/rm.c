#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "path.c"

int main(int argc, char const *argv[])
{
	char *p;
	p=argv[1];

	if(strcmp(p,"-i")==0)
	{
		if(strcmp(argv[2],"-d")==0)
		{
			rm_i_d(argv[3]);
		}	
		else
		{
			rm_i(argv[2]);
		}
	}
	else if(strcmp(p,"-d")==0)
	{
		if(strcmp(argv[2],"-i")==0)
		{
			rm_i_d(argv[3]);
		}
		else
		{
			rm_d(argv[2]);
		}
	}
	else
	{
		rm(argv[1]);
	}
	return 0;
}

void rm_i(char *name)
{
	char choice;

	struct stat buf;
    stat(("%s/%s",path(),name), &buf);

	if(S_ISDIR(buf.st_mode))
	{
		printf("%s\n","Cannot remove directory");
	}
	else if(S_ISREG(buf.st_mode))
	{
		printf("Remove Directory %s ? (y/n) \n",name );
		scanf("%c",&choice);
	}
	else
	{
		printf("%s\n","No such file or directory present\n" );
	}

	if(choice=='y')
	{
		rm(name);
	}

}

void rm_d(char *name)
{
	struct stat buf;
    stat(("%s/%s",path(),name), &buf);

	if(S_ISDIR(buf.st_mode))
	{
		if(remove(name)==0)
			printf("%s\n","Deleted successfully" );
		else
		{
			printf("%s\n","Not an empty directory" );
		}
	}
	else if(S_ISREG(buf.st_mode))
	{
		if(remove(name)==0)
			printf("%s\n","Deleted successfully" );
	}
	else
	{
		printf("No such file or directory present\n");
	}

}

void rm_i_d(char *name)
{
	char choice;
	struct stat buf;
    stat(("%s/%s",path(),name), &buf);

	if (!(S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode)))
	{	
		printf("%s\n","No such file or directory present" );
	}
	else
	{
		printf("Remove Directory %s ? (y/n) \n",name );
		scanf("%c",&choice);
	
		if(choice=='y')
		{
			rm_d(name);
		}		
	}

	
}

void rm(char *name)
{
	struct stat buf;
    stat(("%s/%s",path(),name), &buf);

    if (S_ISREG(buf.st_mode))
    {
    	if (remove(name) == 0)
      		printf("Deleted successfully\n");
    }
    else if(S_ISDIR(buf.st_mode))
    {
    	printf("%s\n","Cannot remove Directory." );
    }
    else
      	printf("No such file or directory present\n");
   
}