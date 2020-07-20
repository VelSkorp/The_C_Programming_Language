#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

main()
{
	int n, base;
	char s[MAXLINE];

	printf("Enter the number: ");

	scanf("%d", &n);

	printf("Enter the base: ");

	scanf("%d", &base);

	itob(n, s, base);

	printf("%s\n", s);

	return 0;
}

void itob(int n, char s[], int b)
{
	int i, j, sign;

	if ((sign = n) < 0)
	{
		n = -n;
	}

	i = 0;

	do
	{
		j = n % b;

		s[i++] = (j <= 9) ? j + '0' : j + 'A' - 10;
	} while ((n /= b) > 0);

	if (sign < 0)
	{
		s[i++] = '-';
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