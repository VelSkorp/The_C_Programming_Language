#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define LINESPERPAGE 10
#define MAXLINE 1000

void printpages(FILE*, FILE*);

main(int argc, char* argv[])
{
	FILE* f1;

	if (argc == 1)
	{
		fprintf(stderr, "No files given");
		printpages(stdin, stdout);
	}
	else
	{
		while (--argc > 0)
		{
			if ((f1 = fopen(*++argv, "r")) == NULL)
			{
				fprintf(stderr, "%s: can't open %s\n", argv[0], *argv);
				return 1;
			}
			else
			{
				fprintf(stdout, "\n\n\t\t\tFile: %s\n\n", *argv);
				printpages(f1, stdout);
				fclose(f1);
			}
		}
	}

	return 0;
}

void printpages(FILE* f1, FILE* f2)
{
	int nline = 0;
	int page = 1;
	char line[MAXLINE];

	while (fgets(line, MAXLINE, f1) != NULL)
	{
		fputs(line, f2);
		nline++;

		if (nline == LINESPERPAGE)
		{
			fprintf(stdout, "\n\t\t\tPage %d End.\n\n", page++);
			nline = 0;
		}
	}
}