#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof (struct key))

int getword(char*, int);
int binsearch(char*, struct key[], int);

struct key
{
	char* word;
	int count;
} keytab[] = {
"auto", 0,
"continue", 0,
"else", 0,
"for", 0,
"long", 0,
"signed", 0,
"switch", 0,
"void", 0,
"break", 0,
"default", 0,
"enum", 0,
"goto", 0,
"register", 0,
"sizeof", 0,
"typedef", 0,
"while", 0,
"case", 0,
"do", 0,
"extern", 0,
"if", 0,
"return", 0,
"static", 0,
"union", 0,
"char", 0,
"double", 0,
"float", 0,
"int", 0,
"short", 0,
"struct", 0,
"unsigned", 0,
};

main()
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
	{
		if (isalpha(word[0]))
		{
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
			{
				keytab[n].count++;
			}
		}
	}

	for (n = 0; n < NKEYS; n++)
	{
		if (keytab[n].count > 0)
		{
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
		}
	}

	return 0;
}

int binsearch(char* word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
		{
			high = mid - 1;
		}
		else if (cond > 0)
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}

int getword(char* word, int lim)
{
	int c, t;
	char* w = word;

	int getch(void);
	void ungetch(int);
	
	while (isspace(c = getch()))
		;

	if (c != EOF)
	{
		*w++ = c;
	}

	if (!isalpha(c))
	{
		if (c == '\"')
		{
			for (c = getch(); c != '\"'; c = getch())
				;
		}
		else if (c == '#')
		{
			for (c = getch(); c != '\n'; c = getch())
				;
		}
		else if (c == '/')
		{
			if ((c = getch()) == '/')
			{
				for (c = getch(); c != '\n'; c = getch())
					;
			}
			else if (c == '*')
			{
				for (c = getch(), t = getch(); c != '*' && t != '/'; c = getch(), t = getch())
				{
					ungetch(t);
				}
			}
			else
			{
				ungetch(c);
			}
		}
		else
		{
			for (; !isspace(c) && c != EOF; c = getch())
				;
		}

		if (c != '\"' && c != '\n' && c != '/')
		{
			ungetch(c);
		}

		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
	{
		if (!isalnum(*w = getch()))
		{
			if (!isspace(*w))
			{
				ungetch(*w);
				return *w;
			}
			else
			{
				ungetch(*w);
				break;
			}
		}
	}
	
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

int bufp = 0;
char buf[BUFSIZE];

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int ñ)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters\n");
	}
	else
	{
		buf[bufp++] = ñ;
	}
}