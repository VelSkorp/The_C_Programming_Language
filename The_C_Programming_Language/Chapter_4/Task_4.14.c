#include <stdio.h>

#define swap(t, x, y) { t temp = x;\
						x = y;\
						y = temp;\
					  }

#define swap1(x, y) x ^= y ^= x ^= y;

main()
{
	int x = 5;
	int y = 1;

	printf("%d\t%d\n", x, y);

	swap(int, x, y);
	printf("%d\t%d\n", x, y);

	swap1(x, y);
	printf("%d\t%d\n", x, y);
}