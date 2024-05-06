#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

main()
{
	printf("%d", invert(255, 2, 1));
}

unsigned invert(unsigned x, int p, int n)
{
	return x ^ (~(~0 << n) << p);
}