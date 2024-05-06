#include <stdio.h>

#define MAXLINE 1000

int getline(char[], int);

main()
{
	int len, t;
	int brace = 0, bracket = 0, parenthesis = 0;
	int s_quote = 1, d_quote = 1;
	char line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0)
	{
		t = 0;

		while (t < len)
		{
			if (line[t] == '[')
			{
				brace++;
			}

			if (line[t] == ']')
			{
				brace--;
			}

			if (line[t] == '(')
			{
				parenthesis++;
			}

			if (line[t] == ')')
			{
				parenthesis--;
			}

			if (line[t] == '{')
			{
				bracket++;
			}

			if (line[t] == '}')
			{
				bracket--;
			}

			if (line[t] == '\'')
			{
				s_quote *= -1;
			}

			if (line[t] == '"')
			{
				d_quote *= -1;
			}

			t++;
		}
	}

	if (d_quote != 1)
	{
		printf("Mismatching double quote mark\n");
	}

	if (s_quote != 1)
	{
		printf("Mismatching single quote mark\n");
	}

	if (parenthesis != 0)
	{
		printf("Mismatching parenthesis\n");
	}

	if (brace != 0)
	{
		printf("Mismatching brace mark\n");
	}

	if (bracket != 0)
	{
		printf("Mismatching bracket mark\n");
	}

	if (bracket == 0 && brace == 0 && parenthesis == 0 && s_quote == 1 && d_quote == 1)
	{
		printf("Syntax appears to be correct.\n");
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