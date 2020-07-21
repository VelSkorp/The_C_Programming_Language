#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char patern[] = "ould";

main() 
{
	char line[MAXLINE];
	int index = 0;

	while (getline(line, MAXLINE) > 0)
	{
		if ((index = strindex(line, patern)) >= 0)
		{
			printf("%s\n", line);
			printf("index form 0 = %d\n", index);
		}
	}

	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
	{
		s[i++] = c;
	}

	if (c == '\n')
	{
		s[i++] = c;
	}

	s[i] = '\0';

	return i;
}

int strindex(char s[], char t[])
{
	int i, j, k;

	for (i = strlen(s) - 1; i > 0; i--)
	{
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;

		if (k > 0 && t[k] == '\0')
		{
			return i;
		}
	}

	return -1;
}