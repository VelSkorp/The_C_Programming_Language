#include <stdio.h>
#include <ctype.h>
#include <string.h>

main(int argc, char* argv[])
{
	int c;

	if (strstr(argv[0], ".lower"))
	{
		while ((c = getchar()) != EOF)
		{
			putchar(tolower(c));
		}
	}
	else
	{
		while ((c = getchar()) != EOF)
		{
			putchar(toupper(c));
		}
	}

	return 0;
}