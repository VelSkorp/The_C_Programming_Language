#include <stdio.h>

#define MAXLINE 1000

void squeeze(char s1[], char s2[]);

main() 
{
	char s1[MAXLINE], s2[MAXLINE];

	printf("s1: ");

	gets(s1);

	printf("s2: ");

	gets(s2);

	squeeze(s1, s2);

	printf(s1);
}

void squeeze(char s1[], char s2[])
{
	int i, j, k;
	int lens1 = strlen(s1) + 1;
	int lens2 = strlen(s2);

	for (i = 0; i < lens2; i++)
	{
		k = 0;

		for (j = 0; j < lens1; j++)
		{
			if (s1[j] != s2[i])
			{
				s1[k++] = s1[j];
			}
		}
	}

	s1[k] = '\0';
}