#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define MAXLINE 100
#define MAXOP 100

void push(double);
double pop(void);
int getop(char*);
void ungetch(int с);
int getch(void);

int sp = 0;
int bufp = 0;
double val[MAXVAL];
char buf[BUFSIZE];

main()
{
	int type;
	double op2;
	char s[MAXLINE];

	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push(atof(s));
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

		case '\n':
			printf("\t%.8g\n", pop());
			break;

		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}

	return 0;
}

int getop(char* s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;

	*(s + 1) = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	if (isdigit(c))
		while (isdigit(*++s = c = getch()))
			;

	if (c == '.')
		while (isdigit(*++s = c = getch()))
			;

	*s = '\0';

	if (c != EOF)
		ungetch(c);

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

int getch(void)
{
	char c;

	if (bufp > 0)
	{
		return buf[--bufp];
	}
	else
	{
		scanf("%c", &c);
		return c;
	}
}

void ungetch(int с)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: слишком много символов\n");
	}
	else
	{
		buf[bufp++] = с;
	}
}