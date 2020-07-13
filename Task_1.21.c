#include <stdio.h>

#define MAXLINE 1000
#define SPACES 8

char line[MAXLINE];

int getline(void);

main()
{
	int len;

	while ((len = getline()) > 0)
	{
		printf("%s", line);
	}

	return 0;
}

int getline(void)
{
	int c, i, spacecounter;
	extern char line[];

	i = 0;
	spacecounter = 0;

	while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n')
	{
		if (c == ' ')
		{
			spacecounter++;
			
			if (spacecounter == SPACES)
			{
				line[i++] = '\t';
				spacecounter = 0;
			}
		}
		else
		{
			for (int j = 0; j < spacecounter; j++)
			{
				line[i++] = ' ';
			}

			line[i++] = c;
		}
	}

	if (c == '\n')
	{
		line[i++] = c;
	}

	line[i] = '\0';

	return i;
}