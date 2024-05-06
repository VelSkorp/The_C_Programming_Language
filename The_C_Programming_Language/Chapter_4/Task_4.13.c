#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char[]);
int getline(char s[], int lim);

main() 
{
	char s[MAXLINE];

	printf("Enter the string: ");

	getline(s, MAXLINE);

	reverse(s);

	printf("%s\n", s);
}

int getline(char s[], int lim)
{
	int i, c;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{
		s[i] = c;
	}

	if (c == '\n')
	{
		s[i++] = '\n';
	}

	s[i] = '\0';
}

void reverse(char s[])
{
	void reverser(char s[], int i, int len);

	reverser(s, 0, strlen(s));
}

void reverser(char s[], int i, int len)
{
	int j = len - (i + 1);

	if (i < j)
	{
		s[i] ^= s[j] ^= s[i] ^= s[j];

		reverser(s, ++i, len);
	}
}