#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[], int width);
void reverse(char s[]);

main()
{
	int n, width;
	char s[MAXLINE];

	printf("Enter the number: ");

	scanf("%d", &n);

	printf("Enter the width: ");

	scanf("%d", &width);

	itoa(n, s, width);

	printf("%s\n", s);

	return 0;
}

void itoa(int n, char s[], int width)
{
	int i, sign;

	if ((sign = n) < 0)
	{
		n = -n;
	}

	i = 0;

	do
	{
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0)
	{
		s[i++] = '-';
	}

	while (i < width)
	{
		s[i++] = ' ';
	}

	s[i] = '\0';

	reverse(s);
}

void reverse(char s[])
{
	int i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		s[i] ^= s[j] ^= s[i] ^= s[j];
	}
}