#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getch(void);
void ungetch(int c);
void ungets(char s[]);
int gets(char s[], int lim);

main()
{
	char line[MAXLINE];
	int c;

	gets(line, MAXLINE);

	ungets(line);

	while ((c = getch()) != EOF)
	{
		putchar(c);
	}

	return 0;
}

int gets(char s[], int lim)
{
	int c, i;

	i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
	{
		s[i++] = c;
	}

	if (c == '\n')
	{
		s[i++] = c;
	}

	s[i] = '\0';

	return i;
}

void ungets(char s[])
{
	int i = strlen(s);

	while (i > 0)
	{
		ungetch(s[--i]);
	}
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters\n");
	}
	else
	{
		buf[bufp++] = c;
	}
}