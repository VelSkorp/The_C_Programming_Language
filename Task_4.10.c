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

#define MAXLINE 100

int getline(char s[], int lim);

int chp = 0;
char s[MAXLINE];

int getop(char op[])
{
	int i;

	if (s[chp] == '\0')
	{
		if (getline(s, MAXLINE) == 0)
		{
			return EOF;
		}
		else
		{
			chp = 0;
		}
	}

	while ((op[0] = s[chp]) == ' ' || s[chp] == '\t')
		chp++;

	op[1] = '\0';

	if (!isdigit(s[chp]) && s[chp] != '.' && s[chp] != '-')
	{
		return s[chp++];
	}

	i = 0;

	if (s[chp] == '-' || isdigit(s[chp]))
	{
		while (isdigit(op[++i] = s[++chp]))
			;
	}

	if (s[chp] == '.')
	{
		while (isdigit(op[++i] = s[++chp]))
			;
	}

	op[i] = '\0';

	return NUMBER;
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