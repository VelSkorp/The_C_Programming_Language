#include <stdio.h>
#include <ctype.h>

#define SIZE 1000

int getch(void);
int getfloat(float*);
void ungetch(int);

main()
{
	int n, s, res;
	float array[SIZE];

	for (n = 0; n < SIZE && (res = getfloat(&array[n])) != EOF; (res != 0) ? n++ : 0)
	{
		printf("storing in n = %d, getfloat %f\n", n, array[n]);
	}

	for (s = 0; s < n; s++)
	{
		printf("%f ", array[s]);
	}

	return 0;
}

int getfloat(float* pn)
{
	int c, sign;
	float power;

	while (isspace(c = getch()))
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c);
		return -1;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
	{
		c = getch();
	}

	if (!isdigit(c))
	{
		return 0;
	}

	for (*pn = 0.0; isdigit(c); c = getch())
	{
		*pn = 10.0 * *pn + (c - '0');
	}

	if (c == '.')
	{
		c = getchar();
	}

	for (power = 1.0; isdigit(c); c = getch())
	{
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}

	*pn *= sign / power;

	if (c != EOF)
	{
		ungetch(c);
	}

	return c;
}

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters\n");
	}
	else
	{
		buf[bufp++] = c;
	}
}