#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
void month_day(int, int, int*, int*);

main(void)
{
	int yearday, mo, day;

	yearday = day_of_year(1988, 2, 29);
	printf("yearday: %d\n", yearday);
	month_day(1988, yearday, &mo, &day);
	printf("month: %d\nday: %d\n", mo, day);

	return 0;
}

int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > daytab[leap][month])
	{
		return -1;
	}

	for (i = 1; i < month; i++)
	{
		day += daytab[leap][i];
	}

	return day;
}

void month_day(int year, int yearday, int* pmonth, int* pday)
{
	if (year < 1 || yearday < 1)
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (leap == 1 && yearday > 366)
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	if (leap == 0 && yearday > 365)
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	for (i = 1; yearday > daytab[leap][i]; i++)
	{
		yearday -= daytab[leap][i];
	}

	*pmonth = i;
	*pday = yearday;
}