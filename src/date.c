#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	if(argv[1]!=NULL)
	{
		if(strcmp(argv[1],"-u")==0)
			UTC();
		else if(strcmp(argv[1],"-R")==0)
			RFC();	
	}
	else
		IST();
	return 0;
}

void IST()
{	
	printf("%s : ","IST Format" );
	//printf("%s\n",d);
	time_t tt;
	time(&tt);
	printf("%s",ctime(&tt));
}

void UTC()
{
	struct tm1 *loc;
	time_t t1;
	printf("%s : ","UTC Format" );
  	t1 = time(NULL);
  	loc = gmtime(&t1);
  	printf("%s", asctime(loc));

}

void RFC()
{
	printf("%s : ","RFC 2822 Format" );
	char buf[1000];
  	time_t now = time(0);
  	struct tm tm = *gmtime(&now);
  	strftime(buf,sizeof buf,"%a, %d %b %Y %H:%M:%S %Z",&tm);
  	printf("%s\n",buf);
}