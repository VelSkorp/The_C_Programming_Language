#include <stdio.h>

main() 
{
	double fahr, celsius;
	double lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;
	celsius = lower;

	printf("Degrees\nCelsius\tFahrengate\n");

	while (celsius <= upper)
	{
		fahr = (celsius * 9.0 / 5.0) + 32.0;

		printf("%4.0f %10.0f\n", celsius, fahr);

		celsius = celsius + step;
	}
}