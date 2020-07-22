#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define NAME_WAS_FOUND 'n'

int getop(char[]);

double pop(void);
double peek(void);

void push(double);
void mathfnc(char[]);

void showStack(void);
void clear(void);
void cloneLast(void);
void swapLastTwo(void);

main()
{
	int type = 0;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push(atof(s));
			break;

		case NAME_WAS_FOUND:
			mathfnc(s);
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

		case'%':
			op2 = pop();

			if (op2 != 0.0)
			{
				push(fmod(pop(), op2));
			}
			else
			{
				printf("error: zero divisor\n");
			}
			break;

		case 'p':
			printf("%g\n", peek());
			break;

		case 's':
			showStack();
			break;

		case 'd':
			cloneLast();
			break;

		case 'w':
			swapLastTwo();
			break;

		case 'c':
			clear();
			break;

		case '\n':
			break;

		default:
			printf("error: unknown command %s\n", s);
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

double peek()
{
	if (sp > 0)
	{
		return val[sp - 1];
	}
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

void showStack()
{
	for (int i = sp - 1; i >= 0; i--)
	{
		printf("show stack\tindex[%d] - value[%f]\n", i, val[i]);
	}
}

void clear()
{
	sp = 0;
}

void cloneLast()
{
	push(peek());
}

void swapLastTwo()
{
	double last = pop();
	double unlast = pop();

	push(last);
	push(unlast);
}

void mathfnc(char s[])
{
	double op2;

	if (strcmp(s, "sin") == 0)
	{
		push(sin(pop()));
	}
	else if (strcmp(s, "exp") == 0)
	{
		push(exp(pop()));
	}
	else if (strcmp(s, "pow") == 0)
	{
		op2 = pop();
		push(pow(pop(), op2));
	}
	else
	{
		printf("error: %s is not supported\n", s);
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	i = 0;

	if (islower(c))
	{
		while (islower(s[++i] = c = getch()))
			;

		s[i] = '\0';

		if (c != EOF)
		{
			ungetch(c);
		}

		if (strlen(s) > 1)
		{
			return NAME_WAS_FOUND;
		}
		else
		{
			return s[i-1];
		}
	}

	if (!isdigit(c) && c != '.' && c != '-')
	{
		return c;
	}

	if (c == '-' || isdigit(c))
	{
		while (isdigit(s[++i] = c = getch()))
			;
	}

	if (c == '.')
	{
		while (isdigit(s[++i] = c = getch()))
			;
	}

	s[i] = '\0';

	if (c != EOF)
	{
		ungetch(c);
	}

	if (strcmp(s, "-") == 0)
	{
		return '-';
	}

	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
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