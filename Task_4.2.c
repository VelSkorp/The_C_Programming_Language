#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

double atof(char s[]);
int getline(char s[], int lim);
int pow(int base, int exp);

main() 
{
	double sum, atof(char[]);
	char line[MAXLINE];
	int getline(char line[], int max);

	sum = 0;

	while (getline(line, MAXLINE) > 0)
	{
		printf("\t%g\n", sum += atof(line));
	}

	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
	{
		s[i++] = c;
	}

	if (c == '\n')
	{
		s[i++] = c;
	}

	s[i] = '\0';

	return i;
}

double atof(char s[])
{
	double val, power;
	int i, sign, esign = 0, exp;
	int pow(int base, int exp);

	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
	{
		i++;
	}

	for (val = 0.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
	}

	if (s[i] == '.')
	{
		i++;
	}

	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	if (s[i] == 'e' || s[i] == 'E')
	{
		i++;
	}

	if (s[i] == '+' || s[i] == '-')
	{
		esign = s[i++];
	}

	for (exp = 0; isdigit(s[i]); i++)
	{
		exp = 10.0 * exp + (s[i] - '0');
	}

	if (esign == '-')
	{
		return sign * (val / power) / pow(10, exp);
	}
	else
	{
		return sign * (val / power) * pow(10, exp);
	}
}

int pow(int base, int exp)
{
	int power;

	power = 1;

	while (exp-- > 0)
	{
		power *= base;
	}

	return power;
}