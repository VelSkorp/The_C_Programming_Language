#include <stdio.h>

#define MAXLINE 1000

#define IN 1
#define OUT 0

int getline(char line[], int maxline);

main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];
	int c;

	max = 0;

	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (line[len - 1] != '\n')
		{
			while ((c = getchar()) != EOF && c != '\n')
			{
				len++;
			}
		}

		if (len > 1)
		{
			printf("%sLen = %d\n", line, len);
		}
	}

	return 0;
}

int getline(char s[], int lim)
{
	int c, i, state;

	i = 0;
	state = OUT;

	while(i < lim - 1 && (c = getchar()) != EOF && c != '\n')
	{
		if (c != ' ' && c != '\t')
		{
			s[i++] = c;
			state = IN;
		}

		if ((c == ' ' || c == '\t') && state == IN)
		{
			s[i++] = c;
			state = OUT;
		}
	}

	if (c == '\n')
	{
		s[i++] = c;
	}

	s[i] = '\0';

	return i;
}