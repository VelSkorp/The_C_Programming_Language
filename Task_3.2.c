#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void escape_revese(char s[], char t[]);

main() 
{
	char s[MAXLINE], t[MAXLINE];

	printf("t: ");
	gets(t);
	escape(s, t);
	printf("s: %s\n\n", s);

	printf("t: ");
	gets(t);
	escape_revese(s, t);
	printf("s: %s\n", s);

	return 0;
}

void escape(char s[], char t[])
{
	int i = 0;
	int j = 0;

	while (t[i] != '\0')
	{
		switch (t[i])
		{
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;

			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;

			default:
				s[j++] = t[i];
				break;
		}

		i++;
	}

	s[j] = '\0';
}

void escape_revese(char s[], char t[])
{
	int i = 0;
	int j = 0;

	while (t[i] != '\0')
	{
		if (t[i] == '\\')
		{
			switch (t[++i])
			{
				case 't':
					s[j++] = '\t';
					break;

				case 'n':
					s[j++] = '\n';
					break;
			}
		}
		else
		{
			s[j++] = t[i];
		}

		i++;
	}

	s[j] = '\0';
}