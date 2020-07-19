#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

main() 
{
	char s1[MAXLINE], s2[MAXLINE];

	gets(s1);
	
	expand(s1,s2);
	
	printf("%s", s2);
}

void expand(char s1[], char s2[])
{
	int i, j, sign;
	char temp;

	i = j = 0;

	while (s1[i]!='\0')
	{
		sign = 1;

		if (s1[i] == '-')
		{
			sign = -1;
			i++;

			if (s1[i + 1] != '-')
			{
				s1[--i] = s1[i - 1];
				temp = s1[i + 1];
				s1[i + 1] = '-';
				s1[i + 2] = temp;
				s1[i + 3] = '\0';
			}
		}

		if (isdigit(s1[i]))
		{
			for (int k = (s1[i] - '0') * sign; k <= s1[i + 2] - '0'; k++)
			{
				if (k < 0)
				{
					s2[j++] = '-';
					s2[j++] = '0' + (k * -1);
					s2[j++] = ' ';
				}
				else
				{
					s2[j++] = '0' + k;
					s2[j++] = ' ';
				}
			}

			i += 3;
		}
		else
		{
			for (int k = s1[i]; k <= s1[i + 2]; k++)
			{
				s2[j++] = k;
				s2[j++] = ' ';
			}

			i += 3;
		}
	}

	s2[j] = '\0';
}