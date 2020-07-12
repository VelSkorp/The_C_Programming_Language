#include <stdio.h>

#define IN 1
#define OUT 0

#define ARRSIZE 100

main()
{
	int frequency[ARRSIZE], symbols[ARRSIZE];
	int c, counter, state, maxChars;

	counter = 0;
	maxChars = 0;

	for (int i = 0; i < ARRSIZE; i++)
	{
		frequency[i] = symbols[i] = 0;
	}

	while ((c = getchar()) != EOF)
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
		if (frequency[i] > maxChars)
		{
			maxChars = frequency[i];
		}
	}

	for (int i = maxChars; i > 0; i--)
	{
		for (int j = 0; j < ARRSIZE; j++)
		{
			if (frequency[j] >= i)
			{
				printf("#");
			}
			else if(frequency[j] != 0)
			{
				printf(".");
			}
		}

		printf("\n");
	}

	for (int i = 0; i < ARRSIZE; i++)
	{
		if (symbols[i] != 0)
		{
			putchar(symbols[i]);
		}
	}
}