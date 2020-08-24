#include <stdio.h>

#define MAXLINE 1000
#define STRLEN 10

int getline(char[], int);

main()
{
	int len, t;
	int location, spaceholder;
	char line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > STRLEN)
		{
			t = 0;
			location = 0;

			while (t < len)
			{
				if (line[t] == ' ' || line[t] == '\t')
				{
					spaceholder = t;
				}

				if (location == STRLEN)
				{
					line[spaceholder] = '\n';
					location = 0;
				}

				location++;
				t++;
			}
		}

		printf("%s", line);
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