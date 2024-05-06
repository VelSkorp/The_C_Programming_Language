#include <stdio.h>

main()
{
	int c, nl, spaces, tabs;
	
	nl = 0;
	spaces = 0;
	tabs = 0;

	
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			nl++;
		}

		if (c == ' ') 
		{
			spaces++;
		}

		if (c == '\t') 
		{
			tabs++;
		}
	}

	printf("new lines: %d\nspaces: %d\ntabs: %d\n", nl, spaces, tabs);
}