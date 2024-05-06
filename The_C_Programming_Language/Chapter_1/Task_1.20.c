#include <stdio.h>

#define MAXLINE 1000
#define SPACES 4

char line[MAXLINE];

int getline(void);

main() 
{
	int len;

	while ((len = getline()) > 0)
	{
		printf("%s", line);
	}

	return 0;
}

int getline(void) 
{
	int c, i;
	extern char line[];

	i = 0;

	while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n')
	{
		if (c == '\t')
		{
			for (int j = 0; j < SPACES; j++)
			{
				line[i++] = ' ';
			}
		}
		else
		{
			line[i++] = c;
		}
	}

	if (c == '\n')
	{
		line[i++] = c;
	}

	line[i] = '\0';

	return i;
}