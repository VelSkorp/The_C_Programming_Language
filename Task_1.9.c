#include <stdio.h>

main() 
{
	int ns, current;

	ns = 0;

	while ((current = getchar()) != EOF)
	{
		if (current == ' ')
		{
			ns++;
		}
		else 
		{
			ns = 0;
		}

		if (ns <= 1)
		{
			putchar(current);
		}
	}
}