#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define NUMERIC 1
#define DECR 2
#define FOLD 4
#define MDIR 8
#define MAXLINES 5000

int charcmp(char*, char*);
void error(char*);
int numcmp(char*, char*);
void readargs(int, char* []);
int readlines(char* [], int);
void qsort(int, int, int(*)(void*, void*));
void writelines(char* [], int);
void substr(char*, char*, int);

static int option = 0;
static int pos1 = 0;
static int pos2 = 0;

char* lineptr[MAXLINES];

main(int argc, char* argv[])
{
	int nlines, c;

	readargs(argc, argv);

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsort(0, nlines - 1, (int(*)(void*, void*))(option & NUMERIC ? numcmp : charcmp));
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("input too big to sort \n");
		return 1;
	}
}

void readargs(int argc, char* argv[])
{
	int c;

	while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+')
	{
		if (c == '-' && !isdigit(*(argv[0] + 1)))
		{
			while (c = *++argv[0])
			{
				switch (c)
				{
				case 'f':
					option |= FOLD;
					break;

				case 'd':
					option |= MDIR;
					break;

				case 'n':
					option |= NUMERIC;
					break;

				case 'r':
					option |= DECR;
					break;

				default:
					printf("sort:illegal option %c\n", c);
					error("Usage: sort -dfnr [+pos1] [-pos2]");
					break;
				}
			}
		}
		else if (c == '-')
		{
			pos2 = atoi(argv[0] + 1);
		}
		else if ((pos1 = atoi(argv[0] + 1)) < 0)
		{
			error("Usage: sort -dfnr [+pos1][-pos2]");
		}
	}

	if (argc || pos1 > pos2)
	{
		error("Usage: sort -dfnr [+pos1] [-pos2]");
	}
}

void qsort(int left, int right, int(*comp)(void*, void*))
{
	int i, last;

	void swap(void* [], int, int);

	if (left >= right)
	{
		return;
	}

	swap(lineptr, left, (left + right) / 2);

	last = left;

	for (i = left + 1; i <= right; i++)
	{
		if (option & DECR && (*comp)(lineptr[i], lineptr[left]) > 0)
		{
			swap(lineptr, ++last, i);
		}
		else if (!(option & DECR) && (*comp)(lineptr[i], lineptr[left]) < 0)
		{
			swap(lineptr, ++last, i);
		}
	}

	swap(lineptr, left, last);
	qsort(left, last - 1, comp);
	qsort(last + 1, right, comp);
}

void swap(void* v[], int i, int j)
{
	void* temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int charcmp(char* s, char* t)
{
	char a, b;
	int i, j, endpos;
	int fold = option & FOLD ? 1 : 0;
	int dir = option & MDIR ? 1 : 0;

	i = j = pos1;

	if (pos2 > 0)
	{
		endpos = pos2;
	}
	else if ((endpos = strlen(s)) > strlen(t))
	{
		endpos = strlen(t);
	}

	do
	{
		if (dir)
		{
			while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
			{
				if (s[i] != ' ' && s[i] != '\0')
				{
					i++;
				}
			}

			while (j<endpos&&!isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
			{
				if (t[j] != ' ' && t[j] != '\0')
				{
					j++;
				}
			}
		}

		if (i < endpos && j < endpos)
		{
			a = fold ? tolower(s[i]) : s[i];
			i++;
			b = fold ? tolower(t[j]) : t[j];
			j++;

			if (a == b && a == '\0')
			{
				return 0;
			}
		}
	} while (a == b && i < endpos && j < endpos);

	return a - b;
}

#define MAXSTR 100

int numcmp(char* s1, char* s2)
{
	double v1, v2;
	char str[MAXSTR];

	substr(s1, str, MAXSTR);
	v1 = atof(str);

	substr(s2, str, MAXSTR);
	v2 = atof(str);

	if (v1 < v2)
	{
		return -1;
	}
	else if (v1 > v2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#define MAXLEN 1000

int readlines(char* lineptr[], int maxlines)
{
	int len, nlines;
	char* p, line[MAXLEN];

	int getline(char*, int);
	char* alloc(int);

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
	while (nlines-- > 0)
	{
		printf("%s\n", *lineptr++);
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

void substr(char* s, char* str)
{
	int i, j, len;

	len = strlen(s);

	if (pos2 > 0 && len > pos2)
	{
		len = pos2;
	}
	else if (pos2 > 0 && len < pos2)
	{
		error("substr: string too short");
	}

	for (j = 0, i = pos1; i < len; i++, j++)
	{
		str[j] = str[i];
	}

	str[j] = '\0';
}

void error(char* s)
{
	printf("%s \n", s);
	exit(1);
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char* allocp = allocbuf;

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