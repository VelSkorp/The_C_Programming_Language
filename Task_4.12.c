#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAXLINE 1000

void itoa(int n, char s[]);

main()
{
	int n;
	char s[MAXLINE];

	printf("Enter the number: ");

	scanf("%d", &n);

	itoa(n, s);

	printf("%s\n", s);

	return 0;
}

void itoa(int n, char s[])
{
	static int i;

	if (n / 10)
	{
		itoa(n / 10, s);
	}
	else
	{
		i = 0;
		if (n < 0)
		{
			s[i++] = '-';
		}
	}
	s[i++] = abs(n) % 10 + '0';

	s[i] = '\0';
}