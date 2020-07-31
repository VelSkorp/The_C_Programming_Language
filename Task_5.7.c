#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char* lineptr[MAXLINES];
char linestor[MAXLINES];

int readlines(char* [], char*, int);
void wrtielines(char* [], int);
void qsort(char* [], int, int);

main()
{
	int nlines;
	if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines - 1);
		wrtielines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("ошибка: слишком много строк\n");
		return 1;
	}
}

#define MAXLEN 1000
#define MAXSTOR 5000

int getline(char*, int);
void swap(char* [], int, int);

int readlines(char* lineptr[], char* linestor, int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	char* p = linestor;
	char* linestop = linestor + MAXSTOR;

	nlines = 0;

	while ((len = getline(line, MAXLEN)) > 0)
	{
		if (nlines >= maxlines || p + len > linestop)
		{
			return -1;
		}
		else
		{
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	}

	return nlines;
}

void wrtielines(char* lineptr[], int nlines)
{
	while (nlines-- > 0)
	{
		printf("%s\n", *lineptr++);
	}
}

void qsort(char* v[], int left, int right)
{
	int i, last;

	if (left >= right)
	{
		return;
	}

	swap(v, left, (left + right) / 2);

	last = left;

	for (i = left + 1; i <= right; i++)
	{
		if (strcmp(v[i], v[left]) < 0)
		{
			swap(v, ++last, i);
		}
	}

	swap(v, left, last);
	swap(v, left, last - 1);
	swap(v, last + 1, right);
}

void swap(char* v[], int i, int j)
{
	char* temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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