#include <stdio.h>

#define MAXLINE 1000
#define YES 1
#define NO 0

int getline(char[], int);

main()
{
	int len, i, in_comment;
	char line[MAXLINE];

	in_comment = NO;

	while ((len = getline(line, MAXLINE)) > 0)
	{
		i = 0;

		while (i < len)
		{
			if (line[i] == '\"')
			{
				while (line[++i] != '\"')
					;

				i++;
			}
			else if (line[i] == '#')
			{
				break;
			}
			else if (line[i] == '/')
			{
				if (line[++i] == '/')
				{
					break;
				}
				else if (line[i] == '*')
				{
					in_comment = YES;
				}
			}

			if (in_comment == NO)
			{
				putchar(line[i++]);
			}
			else
			{
				i++;
			}

			if (line[i] == '*' && line[++i] == '/')
			{
				in_comment = NO;
			}
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