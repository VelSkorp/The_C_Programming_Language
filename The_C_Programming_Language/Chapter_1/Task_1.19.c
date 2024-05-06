#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char s[], int len);

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
			reverse(line, len);
			printf("%sLen = %d\n", line, len);
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
		s[i++] = c;
	}

	s[i] = '\0';

	return i;
}

void reverse(char s[], int len)
{
	int i, j;
	for (i = 0, j = len - 2; i < j; i++, j--)
	{
		char c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}