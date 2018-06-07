#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "path.c"

int increment=1;

int main(int argc, char const *argv[])
{

	if(strcmp(argv[1],"-n")==0)
	{
		int i=2;
		while(argv[i]!=NULL)
		{
			struct stat buf;
		    stat(("%s/%s",path(),argv[i]), &buf);

		    if(chdir(argv[i])==-1)
		    {
		    	if (S_ISREG(buf.st_mode))
				{
					cat_n(argv[i]);
				}
		      	else
		      		printf("No such file or directory present\n");
		    }
			else if(S_ISDIR(buf.st_mode))
		    {
		    	printf("%s %s\n",argv[i]," is a Directory." );
		    }
			else
				cat_n(argv[i]);
			i++;
		}
	}
	else if(strcmp(argv[1],"-b")==0)
	{
		int i=2;
		while(argv[i]!=NULL)
		{
			struct stat buf;
		    stat(("%s/%s",path(),argv[i]), &buf);

		    if(chdir(argv[i])!=0)
		    {
		    	if (S_ISREG(buf.st_mode))
				{
					cat_b(argv[i]);
				}
		      	else
		      		printf("No such file or directory present\n");
		    }
			else if(S_ISDIR(buf.st_mode))
		    {
		    	printf("%s %s\n",argv[i]," is a Directory." );
		    }
		    else
				cat_b(argv[i]);
			i++;
		}
	}
	else
	{
		int i=1;
		while(argv[i]!=NULL)
		{
			struct stat buf;
		    stat(("%s/%s",path(),argv[i]), &buf);
		    //printf("%s\n",argv[i] );
		    if(chdir(argv[i])!=0)
		    {

		    	if (S_ISREG(buf.st_mode))
				{
					//printf("%s\n","ddf" );
					cat_command(argv[i]);
				}
		      	else
		      	{
		      		//printf("%s\n","222");
		      		printf("No such file or directory present\n");
		      	}
		    }
			else if(S_ISDIR(buf.st_mode))
		    {
		    	printf("%s %s\n",argv[i],"is a Directory." );
		    }

			i++;	
		}
		
	}

	return 0;
}

void cat_command(char *y)
{
	FILE *f;
	f = fopen(y,"r");
	char pt;
	if(f!=NULL)
	{
		while((pt=fgetc(f))!=EOF)
		{
			printf("%c",pt);	
		}
		fclose(f);
	}
}

void cat_n(char *y)
{
	FILE *f; 
	f=fopen(y,"r");
	size_t length = 255;
	char *line=malloc(sizeof(char)*length);
	int pt;
	//int increment=1;

	if(f!=NULL)
	{

		while(fgets(line,length,f) != NULL)
		{
			printf("%d %s",increment,line);
			increment++;
		}
		fclose(f);
	}

}	

void cat_b(char *y)
{
	FILE *f; 
	f=fopen(y,"r");
	size_t length = 255;
	char *line=malloc(sizeof(char)*length);
	int pt;
	//int increment=1;

	if(f!=NULL)
	{

		while(fgets(line,length,f) != NULL)
		{
			if(strcmp(line,"\n")==0)
			{
				printf("\n");
			}
			else
			{
				printf("%d %s",increment,line);
				increment++;
			}
			
		}
		fclose(f);
	}
}	