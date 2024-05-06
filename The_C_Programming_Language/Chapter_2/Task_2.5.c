#include <stdio.h>

#define MAXLINE 1000

int any(char s1[], char s2[]);

main()
{
	char s1[MAXLINE], s2[MAXLINE];

	printf("s1: ");

	gets(s1);

	printf("s2: ");

	gets(s2);

	int pos = any(s1, s2);

	printf("position: %d", pos);
}

int any(char s1[], char s2[])
{
	int lens1 = strlen(s1);
	int lens2 = strlen(s2);

	for (int i = 0; i < lens2; i++)
	{
		for (int j = 0; j < lens1; j++)
		{
			if (s1[j] == s2[i])
			{
				return j + 1;
			}
		}
	}

	return -1;
}