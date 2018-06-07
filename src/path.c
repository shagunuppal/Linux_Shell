#include <stdio.h>
#include <stdlib.h>

char *path()
{
	char directory[1024];
	char *t;
	if(getcwd(directory, sizeof(directory))==NULL)
	{
		//perror("Error ");
		return NULL;
	}
	else
	{
		t=getcwd(directory, sizeof(directory));	
		return(t);
	}
}