#include <stdio.h>

double fahr_to_celsius(double fahr);

main()
{
	double fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 30;
	fahr = lower;

	printf("Degrees:\nFahrengate\tCelsius\n");

	while (fahr <= upper)
	{
		celsius = fahr_to_celsius(fahr);

		printf("%6.0f %15.1f\n", fahr, celsius);

		fahr = fahr + step;
	}

	return 0;
}

double fahr_to_celsius(double fahr)
{
	double celsius = (5.0 / 9.0) * (fahr - 32.0);

	return celsius;
}