#include <stdio.h>
#include <time.h>

int main()
{
 time_t	now; 
 struct tm ts;
 char buf[80];

 time(&now);

 ts = *localtime(&now);

 strftime(buf, sizeof(buf), "%Y:%H:%M:%S %Z", &ts);
 puts (buf);

 return 0;
}
