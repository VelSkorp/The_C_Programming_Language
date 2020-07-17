#include <stdio.h>

unsigned rightrot(unsigned x, int n);

main()
{
	printf("%u", rightrot(10, 4));
}

unsigned rightrot(unsigned x, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (x & 1)
		{
			x = (x >> 1) | (1U << 31);
		}
		else
		{
			x = x >> 1;
		}
	}

	return x;
}