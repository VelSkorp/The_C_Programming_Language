#include <stdio.h>

#define MINLINE 80
#define MAXLINE 1000

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

		if (len > MINLINE)
		{
			printf("%s\nLen = %d\n", line, len);
		}
	}

	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		s[i] = c;
	}

	if (c == '\n')
	{
		s[i] = c;
		i++;
	}

	s[i] = '\0';

	return i;
}