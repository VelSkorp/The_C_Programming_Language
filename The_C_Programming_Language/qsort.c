#include <stdio.h>

void qsort(int[], int, int);

main() 
{
	int mas[] = {3,9,2,34,6,1,8,74,7,12 };

	qsort(mas, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", mas[i]);
	}
}

void qsort(int v[], int left, int right)
{
	int i, last;

	void swap(int v[], int i, int j);

	if (left >= right)
	{
		return;
	}

	swap(v, left, (left + right) / 2);

	last = left;

	for (i = last + 1; i <= right; i++)
	{
		if (v[i] < v[left])
		{
			swap(v, ++last, i);
		}
	}

	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(int v[], int i, int j)
{
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}