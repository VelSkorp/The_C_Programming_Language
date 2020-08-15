#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void filecmp(FILE*, FILE*);

main(int argc, char* argv[])
{
	FILE* fp1;
	FILE* fp2;

	if (argc == 1)
	{
		printf("Please provide two files");
		return 1;
	}
	else if (argc == 3)
	{
		if ((fp1 = fopen(*++argv, "r")) != NULL && (fp2 = fopen(*++argv, "r")) != NULL)
		{
			filecmp(fp1, fp2);
			fclose(fp1);
			fclose(fp2);
		}
		else
		{
			fprintf(stderr, "%s: не могу открыть один из файлов файл\n", argv[0]);
			fclose(fp1);
		}
	}

	return 0;
}

void filecmp(FILE* f1, FILE* f2)
{
	char line1[MAXLINE];
	char line2[MAXLINE];

	while ((fgets(line1, MAXLINE, f1) != NULL) | (fgets(line2, MAXLINE, f2) != NULL))
	{
		if (strcmp(line1, line2) != 0)
		{
			printf("%s -- %s\n", line1, line2);
			break;
		}
	}
}