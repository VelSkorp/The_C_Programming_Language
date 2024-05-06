#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXVAL 100

void push(double);
double pop(void);

double val[MAXVAL];
int sp = 0;

main(int argc, char* argv[])
{
	int type;
	double op2;

	while (--argc > 0)
	{
		type = getop(*++argv);

		switch (type)
		{
		case NUMBER:
			push(atof(*argv));
			break;

		case '+':
			push(pop() + pop());
			break;

		case '*':
			push(pop() * pop());
			break;

		case '-':
			op2 = pop();
			push(pop() - op2);
			break;

		case '/':
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

		default:
			printf("error: unknown command %s\n", *argv);
			break;
		}
	}

	printf("\t= %.8g", pop());

	return 0;
}

int getop(char* s)
{
	int c = *s++;

	if (!isdigit(c) && c != '.')
		return c;

	if (isdigit(c))
		while (isdigit(c = *++s))
			;

	if (c == '.')
		while (isdigit(c = *++s))
			;

	return NUMBER;
}

void push(double f)
{
	if (sp < MAXVAL)
	{
		val[sp++] = f;
	}
	else
	{
		printf("error: stack full,can't push %g\n", f);
	}
}

double pop(void)
{
	if (sp > 0)
	{
		return val[--sp];
	}
	else
	{
		printf("error: stack empty \n");
		return 0.0;
	}
}