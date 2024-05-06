#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char*, int);
int strindex(char*, char*);

main(int argc, char* argv[])
{
	FILE* f1;
	char line[MAXLINE];
	char* pattern = "ould";

	if (argc == 1)
	{
		while ((getline(line, MAXLINE)) > 0)
		{
			if (strindex(line, pattern) >= 0)
			{
				printf("%s\n", line);
			}
		}
	}
	else
	{
		while (--argc > 0)
		{
			if ((f1 = fopen(*++argv, "r")) == NULL)
			{
				printf("cat: can't open %s\n", *argv);
				return 1;
			}
			else
			{
				while ((fgets(line, MAXLINE, f1)) != NULL)
				{
					if (strindex(line, pattern) >= 0)
					{
						printf("\n%s\nfile: %s\n", line, *argv);
					}
				}
			}
		}
	}

	return 0;
}

int getline(char* s, int lim)
{
	int c;
	char* temp = s;

	while (s < s + lim - 1 && (c = getchar()) != EOF && c != '\n')
	{
		*s++ = c;
	}

	if (c == '\n')
	{
		*s++ = c;
	}

	*s = '\0';

	return s - temp;
}

int strindex(char* s, char* t)
{
	char* b = s;
	char* p, * r;

	for (; *s != '\0'; s++)
	{
		for (p = s, r = t; *r != '\0' && *p == *r; p++, r++)
			;

		if (r > t && *r == '\0')
		{
			return s - b;
		}
	}

	return -1;
}