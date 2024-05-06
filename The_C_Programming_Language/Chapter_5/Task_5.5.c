#include <stdio.h>

#define MAXLINE 1000
#define N 5

int getline(char[], int);
int strlen(char* s);

char* strncpy(char*, const char*, int);
char* strncat(char*, const char*, int);
char strncmp(const char*, const char*, int);

main()
{
	char s[MAXLINE], t[MAXLINE];

	getline(s, MAXLINE);
	getline(t, MAXLINE);
	strncat(s, t, N);
	printf("strncat: %s\n", s);

	getline(s, MAXLINE);
	getline(t, MAXLINE);
	strncpy(s, t, N);
	printf("strncpy: %s\n", s);
	
	getline(s, MAXLINE);
	getline(t, MAXLINE);
	printf("strncmp: %d\n", strncmp(s, t, N));

	return 0;
}

char strncmp(const char* cs, const char* ct, int n)
{
	for (; *cs == *ct; cs++, ct++)
	{
		if (*cs == '\0' || --n <= 0)
		{
			return 0;
		}
	}

	return *cs - *ct;
}

char* strncpy(char* s, const char* ct, int n)
{
	for (int i = 1; (*s++ = *ct++) != '\0' && i < n; i++)
		;

	if (strlen(ct) < n)
	{
		*s = '\0';
	}

	return s;
}

char* strncat(char* s, const char* ct, int n)
{
	while (*s != '\0')
	{
		s++;
	}

	s--;

	for (int i = 1; (*s++ = *ct++) != '\0' && i < n; i++)
		;

	*s = '\0';

	return s;
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

int strlen(char* s)
{
	int n;

	for (n = 0; *s != '\0'; s++)
	{
		n++;
	}

	return n;
}