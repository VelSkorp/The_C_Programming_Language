#include <stdio.h>

#define MAXLINE 1000

int strend(char*, char*);
int strlen(char*);
int getline(char[], int);

main()
{
	char s[MAXLINE], t[MAXLINE];

	getline(s, MAXLINE);
	getline(t, MAXLINE);

	printf("%d\n", strend(s, t));

	return 0;
}

int strend(char* s, char* t)
{
	int len = strlen(t);

	while (*s != '\0')
	{
		s++;
	}

	s--;

	while (*t != '\0')
	{
		t++;
	}

	t--;

	while (len > 0)
	{
		if (*t == *s)
		{
			t--;
			s--;
			len--;
		}
		else
		{
			return 0;
		}
	}

	if (len == 0)
	{
		return 1;
	}
}

int strlen(char* s)
{
	int n;

	for (n = 0; *s != '\0'; s++)
	{
		n++;
	}

	return n;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && ((c = getchar()) != EOF) && c != '\n'; i++)
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