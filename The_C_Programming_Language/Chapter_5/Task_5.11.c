#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC 8
#define YES 1
#define NO 0

void esettab(int, char* [], char*);
void detab(char*);
void entab(char*);
int tabpos(int, char*);

main(int argc, char* argv[])
{
	char tab[MAXLINE + 1];

	esettab(argc, argv, tab);

	printf("detab:\n");
	detab(tab);

	printf("entab:\n");
	entab(tab);

	return 0;
}

void esettab(int argc, char* argv[], char* tab)
{
	int i, inc, pos;

	if (argc <= 1)
	{
		for (i = 1; i <= MAXLINE; i++)
		{
			if (i % TABINC == 0)
			{
				tab[i] = YES;
			}
			else
			{
				tab[i] = NO;
			}
		}
	}
	else
	{
		for (i = 1; i <= MAXLINE; i++)
		{
			tab[i] = NO;
		}

		while (--argc > 0)
		{
			pos = atoi(*++argv);

			if (pos > 0 && pos <= MAXLINE)
			{
				tab[pos] = YES;
			}
		}
	}
}

void detab(char* tab)
{
	int c, pos = 1;

	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			do
			{
				putchar(' ');
			} while (tabpos(pos++, tab) != YES);
		}
		else if (c == '\n')
		{
			putchar(c);
			pos = 1;
		}
		else
		{
			putchar(c);
			pos++;
		}
	}
}

void entab(char* tab)
{
	int c, pos;
	int nb = 0;
	int nt = 0;

	for (pos = 1; (c = getchar()) != EOF; pos++)
	{
		if (c == ' ')
		{
			if (tabpos(pos, tab) == NO)
			{
				nb++;
			}
			else
			{
				nb = 0;
				nt++;
			}
		}
		else
		{
			for (; nt > 0; nt--)
			{
				putchar('\t');
			}

			if (c == '\t')
			{
				nb = 0;
			}
			else
			{
				for (; nb > 0; nb--)
				{
					putchar(' ');
				}
			}

			putchar(c);

			if (c == '\n')
			{
				pos = 0;
			}
			else if (c == '\t')
			{
				while (tabpos(pos, tab) != YES)
				{
					pos++;
				}
			}
		}
	}
}

int tabpos(int pos, char* tab)
{
	if (pos > MAXLINE)
	{
		return YES;
	}
	else
	{
		return tab[pos];
	}
}