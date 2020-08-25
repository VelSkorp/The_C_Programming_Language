#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

main()
{
	int type = 0;
	double op2;
	char op[MAXOP];

	while ((type = getop(op)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push(atof(op));
			break;

		case'+':
			push(pop() + pop());
			break;

		case'-':
			op2 = pop();
			push(pop() - op2);
			break;

		case'*':
			push(pop() * pop());
			break;

		case'/':
			op2 = pop();

			if (op2 != 0.0)
			{
				push(pop() / op2);
			}
			else
			{
				printf("error: zero divisor\n");
			}
			break;

		case '\n':
			printf("\t%.8g\n", pop());
			break;

		default:
			printf("error: unknown command %s\n", op);
			break;
		}
	}

	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
	{
		val[sp++] = f;
	}
	else
	{
		printf("error:stack full, cant push %g\n", f);
	}
}

double pop()
{
	if (sp > 0)
	{
		return val[--sp];
	}
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getop(char s[])
{
	int i, c;
	static int buf = EOF;

	if (buf != EOF && buf != ' ' && buf != '\t' && !isdigit(buf) && buf != '.')
	{
		c = buf;
		buf = EOF;
		return c;
	}

	if (buf == EOF || buf == ' ' || buf == '\t')
	{
		while ((s[0] = c = getchar()) == ' ' || c == '\t')
			;
	}
	else
	{
		s[0] = c = buf;
	}

	buf = EOF;

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
	{
		return c;
	}

	i = 0;

	if (isdigit(c))
	{
		while (isdigit(s[++i] = c = getchar()))
			;
	}

	if (c == '.')
	{
		while (isdigit(s[++i] = c = getchar()))
			;
	}

	s[i] = '\0';

	buf = c;
	return NUMBER;
}