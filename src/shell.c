#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "history.c"
#include "save_history.c"
#include "path.c"

#define delimiter " \n\t\r"
char string[1024][1024];
int ind;

// Internal Commands - cd,echo,history,pwd,exit
// External Commands - ls,cat,date,rm,mkdir

int print_printf(char **array)
{
	int k;
	if(array[1]!=NULL && strcmp(array[1],"-n")==0)
	{
		k=2;
	}
	else
		k=1;
	if(array[1]!=NULL && strcmp(array[1],"-E")==0)
	{
		k=2;
	}
	int count1=0;
	int index1=0;
	if(ind!=0)
		k=0;
	while(array[k]!=NULL)
	{
		index1=0;
		for(int t=0;t<strlen(array[k]);t++)
		{
			if(((array[k])[t])!='"')
			{
				string[ind][index1]=array[k][t];
				index1++;
			}
			else
			{
				count1+=1;
			}
		}
		string[ind][index1]='\0';

		ind++;
		k++;
	}
	
	return count1;
}

int main(int argc, char const *argv[])
{
	char instruction[1024];

	FILE * f_in;
   	int i;
   	int flag=0;
	while(1)
	{
		printf("%s","Shell >>> " );
		fgets(instruction,1024,stdin);
		if(strcmp(instruction,"\n")==0)
		{
			continue;
		}
		char *pointer;
		if((pointer=strchr(instruction,'\n'))!=NULL)
		{
			*pointer='\0';
		}

		f_in = fopen ("/home/shagunuppal/Desktop/OS_Assignment0/standby.txt","a");
       	fprintf(f_in, instruction);
       	fprintf(f_in,"\n");
  		fclose (f_in);
	

		int i=0;
		char **array = malloc(1024*sizeof(char*));
		char *ch = strtok(instruction,delimiter);
		array[i]=ch;
		i++;

		while(ch != NULL)
		{
			ch = strtok(NULL,delimiter);
			array[i]=ch;
			i++;
		}

		array[i]=NULL;

		if(strcmp(array[0],"cd")==0)
		{
			if(array[1]!=NULL && strcmp(array[1],"~")==0)
			{
				chdir("/home/shagunuppal");
			}
			else if(array[1]!=NULL && strcmp(array[1],"/")==0)
			{
				chdir("/");
			}
			else if(array[1]==NULL)
			{
				chdir("/home/shagunuppal");
			}
			else if(strcmp(array[1],"..")==0)
				chdir(array[1]);
			else 
			{
				struct stat buf;
    			stat(("%s/%s",path(),array[1]), &buf);
			
				if(chdir(array[1])==0)
					chdir(array[1]);
				else if(chdir(array[1])==-1)
				{
					if (S_ISREG(buf.st_mode))
					{
						printf("%s %s\n",array[1],": Not a directory" );
					}
					else
					{
						printf("%s %s\n",array[1],": No such file or directory present" );
					}
				}
			}
		}
		else if(strcmp(array[0],"exit")==0)
		{
			save();
			exit(1);
		}
		else if(strcmp(array[0],"echo")==0)
		{	
			// one space extra
			ind=0;
			int count = print_printf(array);
 
			if(count%2!=0)
			{
				char inst[1024];

				while(count%2!=0)
				{
					printf("%c",'>' );

					fgets(inst,1024,stdin);
					char *ptr;
					
					if((ptr=strchr(inst,'\n'))!=NULL)
					{
						*ptr='\0';
					}

					int m=0;
					char **arr = malloc(1024*sizeof(char*));
					char *c = strtok(inst,delimiter);
					arr[m]=c;
					m++;
					
					while(c != NULL)
					{
						c = strtok(NULL,delimiter);
						arr[m]=c;
						m++;
					}
			
					arr[m]=NULL;
					string[ind][0]='\n';
					ind++;
					count+=print_printf(arr);
				}
			}
			for(int y=0;y<ind;y++)
			{
				if(string[y][0]!='\n')
				{
					printf("%s ",string[y]);
				}
				else
				{
					printf("%s",string[y]);
				}
				memset(string[y],'\0',strlen(string[y]));
			}
			
			if(strcmp(array[1],"-n")!=0)
			{
				printf("\n");	
			}
		}
		else if(strcmp(array[0],"pwd")==0)
		{
			char directory[1024];

			if(getcwd(directory, sizeof(directory))==NULL)
			{
				perror("Error ");
			}
			else
			{
				printf("%s\n", directory );
			}
		}
		else if(strcmp(array[0],"history")==0)
		{

			// one more command option
			if(array[1]!=NULL && strcmp(array[1],"-c")==0)
			{
				save();
				FILE *fc;
				flag=1;
				fc=fopen("/home/shagunuppal/Desktop/OS_Assignment0/standby.txt","a");
			}
			else if(array[1]!=NULL && strcmp(array[1],"-a")==0)
			{
				save();
			}
			else
			{
				if(flag==0)
					history_command();
				else
					history_c();				
			}

		}
		else
		{
			if(fork() == 0)
			{
				if(strcmp(array[0],"date")==0)
				{
					execv("/home/shagunuppal/Desktop/OS_Assignment0/date",array);
				}
				else if(strcmp(array[0],"mkdir")==0)
				{
					execv("/home/shagunuppal/Desktop/OS_Assignment0/mkdir",array);
				}
				else if(strcmp(array[0],"rm")==0)
				{
					execv("/home/shagunuppal/Desktop/OS_Assignment0/rm",array);
				}
				else if(strcmp(array[0],"ls")==0)
				{
					execv("/home/shagunuppal/Desktop/OS_Assignment0/ls",array);
				}
				else if(strcmp(array[0],"cat")==0)
				{
					execv("/home/shagunuppal/Desktop/OS_Assignment0/cat",array);
				}
				else
				{
					printf("%s %s\n",instruction,": command not found" );
				}
				exit(1);
				
			}
			else 
			{
				wait(NULL);
			}
		}

		
	}
	return 0;
}