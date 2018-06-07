#include <stdio.h>
#include <dirent.h>


int main(int argc, char const *argv[])
{
	if(argv[1]!=NULL && strcmp(argv[1],"-a")==0)
	{
		if(argv[2]!=NULL && strcmp(argv[2],"-m")==0)
			ls_a_m();
		else
			ls_a();
		printf("\n");
	}
	else if(argv[1]!=NULL && strcmp(argv[1],"-m")==0)
	{
		if(argv[2]!=NULL && strcmp(argv[2],"-a")==0)
			ls_a_m();
		else
			ls_m();
		printf("\n");
	}
	else
	{
		list_dir();
		printf("\n");
	}
	return 0;
}


void list_dir()
{
	DIR *d;
	d = opendir(".");
	struct dirent *dir;
	
	int flag=0;
	if(d!=NULL)
	{
		while((dir = readdir(d)) != NULL)
		{
			if((strcmp(dir->d_name,".")==0) || (strcmp(dir->d_name,"..")==0))
			{

			}
			else
			{
				flag=1;
				printf("%s ", dir->d_name);
			}
		}
		closedir(dir);
	}
	
	if(flag==0)
	{
		printf("%s","No contents present in the directory.");
	}
}

void ls_a_m()
{
	DIR *d;
	d = opendir(".");
	struct dirent *dir;

	if(d!=NULL)
	{
		int o=0;
		while((dir = readdir(d)) != NULL)
		{
			if(o!=0)
			printf("%s",", ");
			printf("%s", dir->d_name);
			o++;
		}

		closedir(dir);
	}

}

void ls_a()
{
	DIR *d;
	d = opendir(".");
	struct dirent *dir;

	if(d!=NULL || d!='\n')
	{
		while((dir = readdir(d)) != NULL)
		{
			printf("%s\t", dir->d_name);
		}
		closedir(dir);
	}
}

void ls_m()
{
	DIR *d;
	d = opendir(".");
	struct dirent *dir;

	int flag=0;
	if(d!=NULL || d!='\n')
	{
		int o=0;
		while((dir = readdir(d)) != NULL)
		{
			

			if((strcmp(dir->d_name,".")==0) || (strcmp(dir->d_name,"..")==0))
			{

			}
			else
			{
				if(o!=0)
				printf("%s",", ");
				printf("%s", dir->d_name);
				flag=1;
			}
			o++;
		}

		closedir(dir);
	}
	
	if(flag==1)
	{
		printf("%s\n","No contents present in the directory.");
	}					
}

