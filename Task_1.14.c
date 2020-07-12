#include <stdio.h>

#define IN 1
#define OUT 0

#define ARRSIZE 100

main()
{
	int frequency[ARRSIZE], symbols[ARRSIZE];
	int c, counter, state;

	counter = 0;

	for (int i = 0; i < ARRSIZE; i++)
	{
		frequency[i] = symbols[i] = 0;
	}

	while ((c = getchar()) != '\n')
	{
		state = OUT;

		for (int i = 0; i < ARRSIZE; i++)
		{
			if (symbols[i] == c)
			{
				frequency[i]++;
				state = IN;
			}
		}

		if (state == OUT)
		{
			symbols[counter] = c;
			++frequency[counter++];
		}
	}

	for (int i = 0; i < ARRSIZE; i++)
	{
		if (symbols[i] != 0)
		{
			putchar(symbols[i]);
			printf(" : %d\n", frequency[i]);
		}
	}
}