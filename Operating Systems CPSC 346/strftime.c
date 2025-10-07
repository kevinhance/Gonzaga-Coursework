#include <stdio.h>
#include <time.h>

int main()
{
 time_t rawtime;
 struct tm* timeinfo;
 char buf[80];

 time(&rawtime);
 printf("%d\n",(int)rawtime);
 timeinfo = localtime(&rawtime);

 //%p is for A.M. or P.M.
 //%T is ISO 8601 time format(HH:MM:SS)
 strftime(buf, 80, "%T\n",timeinfo);
 puts (buf);

 return 0;
}
