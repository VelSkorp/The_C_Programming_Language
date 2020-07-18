#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

main()
{
	int mas[1000];
	int i;
	clock_t clock1;
	clock_t clock2;

	for (i = 0; i < 1000; i++)
	{
		mas[i] = i;
	}

	clock1 = clock();
	binsearch(4, mas, 1000);
	clock2 = clock();
	printf("binsearch() time = %lu\n", (unsigned long int)(clock2 - clock1));

	clock1 = clock();
	binsearch2(4, mas, 1000);
	clock2 = clock();
	printf("binsearch2() time = %lu\n", (unsigned long int)(clock2 - clock1));
}

int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (x < v[mid])
		{
			high = mid - 1;
		}
		else if (x > v[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}

int binsearch2(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;

	while (low <= high && x != v[mid])
	{
		if (x < v[mid])
		{
			high = mid - 1;
		}
		else 
		{
			low = mid + 1;
		}

		mid = (low + high) / 2;
	}

	if (x == v[mid])
	{
		return mid;
	}

	return -1;
}