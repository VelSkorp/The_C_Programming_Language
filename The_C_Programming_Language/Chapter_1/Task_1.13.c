#include <stdio.h>

#define IN 1
#define OUT 0

#define ARRSIZE 100

main()
{
	int wordLengths[ARRSIZE];
	int c, state, wMaxLength, wLength, counter;

	wMaxLength = 0;
	counter = 0;
	wLength = 0;
	state = IN;

	for (int i = 0; i < ARRSIZE; i++)
	{
		wordLengths[i] = 0;
	}

	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\n' || c == '\t')
		{
			state = OUT;
		}
		else if (state == OUT)
		{
			wordLengths[counter++] = wLength;
			wLength = 0;
			state = IN;
		}

		if (state == IN)
		{
			wLength++;
		}
	}

	wordLengths[counter++] = wLength;

	for (int i = 0; i < counter; i++)
	{
		if (wordLengths[i] > wMaxLength)
		{
			wMaxLength = wordLengths[i];
		}
	}

	for (int i = wMaxLength; i > 0; i--)
	{
		for (int j = 0; j < counter; j++)
		{
			if (wordLengths[j] >= i)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}

		printf("\n");
	}
}