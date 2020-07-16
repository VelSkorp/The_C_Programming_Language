#include <stdio.h>
#include <limits.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

main() 
{
	printf("%d", setbits(10, 3, 3, 127));
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return x | ((y & ~(UINT_MAX << n)) << p);
}