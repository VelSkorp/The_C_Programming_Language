#include <stdio.h>

#define MAXLINE 1000

main() 
{
	int c;
	int lim = MAXLINE;
	char s[MAXLINE];

	for (int i = 0; i < lim - 1; i++)
	{
		if ((c = getchar()) == EOF)
		{
			break;
		}

		if (c == '\n')
		{
			break;
		}

		s[i] = c;
	}
}