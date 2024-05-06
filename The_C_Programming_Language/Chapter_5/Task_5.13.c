#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000
#define NLINES 10

static char allocbuf[ALLOCSIZE];
static char* allocp = allocbuf;
char* lineptr[MAXLINES];

int readlines(char* [], int);
void writelines(char* [], int);
int getline(char*, int);
char* alloc(int);

main(int argc, char* argv[])
{
	int nlines;

	if (argc == 1)
	{
		readlines(lineptr, MAXLINES);
		writelines(lineptr, NLINES);
	}
	else if (argc == 2 && *argv[1] == '-')
	{
		nlines = atoi(&(*++argv)[1]);
		readlines(lineptr, MAXLINES);
		writelines(lineptr, nlines);
	}
}

int readlines(char* lineptr[], int maxlines)
{
	int len, nlines;
	char* p, line[MAXLEN];

	nlines = 0;

	while ((len = getline(line, MAXLEN)) > 0)
	{
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
		{
			return -1;
		}
		else
		{
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

void writelines(char* lineptr[], int nlines)
{
	while (*lineptr != NULL)
	{
		*lineptr++;
	}

	*lineptr--;

	while (nlines-- > 0)
	{
		printf("%s\n", *lineptr--);
	}
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

char* alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n)
	{
		allocp += n;
		return allocp - n;
	}
	else
	{
		return NULL;
	}
}