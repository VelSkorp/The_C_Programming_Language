#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define MAXLINE 100
#define MAXOP 100

int getch(void);
void ungetch(int с);
int getop(char*);
void push(double);
double pop(void);

int getline(char*, int );
int strindex(char*, char*);
int atoi(char*);
void itoa(int, char*);
void reverse(char*);

int sp = 0;
int bufp = 0;
double val[MAXVAL];
char buf[BUFSIZE];

char pattern[] = "ould";

main(void)
{
	char line[MAXLINE];

	int found = 0;

	while ((getline(line, MAXLINE)) > 0)
	{
		if (strindex(line, pattern) >= 0)
		{
			printf("%s\n", line);
			found++;
		}
	}

	char* s = "1234";

	printf("%d\n", atoi(s));

	char s1[MAXLINE];
	int i = 12345;

	itoa(i, s1);
	printf("%s\n", s1);
	reverse(s1);
	printf("%s\n", s1);

	int type;
	double op2;
	char s3[MAXOP];

	while ((type = getop(s3)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push(atof(s3));
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
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
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

int getline(char* s, int lim)
{
	int c;
	char* temp = s;

	while (s < s + lim - 1 && (c = getchar()) != EOF && c != '\n')
	{
		*s++ = c;
	}

	if (c == '\n')
	{
		*s++ = c;
	}

	*s = '\0';

	return s - temp;
}

int atoi(char* s)
{
	int n, sign;

	while (isspace(*s))
	{
		s++;
	}

	sign = (*s++ == '-') ? -1 : 1;

	if (*s == '+' || *s == '-')
	{
		s++;
	}

	for (n = 0; isdigit(*s); s++)
	{
		n = 10 * n + (*s - '0');
	}

	return sign * n;
}

void itoa(int n, char* s)
{
	if (n / 10)
	{
		itoa(n / 10, s);
	}
	else
	{
		if (n < 0)
		{
			*s++ = '-';
		}
	}

	*s++ = abs(n) % 10 + '0';
	*s = '\0';
}

void reverse(char* s)
{
	int c;
	char* t;

	for (t = s + (strlen(s) - 1); s < t; s++, t--)
	{
		c = *s;
		*s = *t;
		*t = c;
	}
}

int strindex(char* s, char* t)
{
	char* b = s;
	char* p, * r;

	for (; *s != '\0'; s++)
	{
		for (p = s, r = t; *r != '\0' && *p == *r; p++, r++)
			;

		if (r > t && *r == '\0')
		{
			return s - b;
		}
	}

	return -1;
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
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int с) 
{
	if (bufp >= BUFSIZE)
		printf("ungetch: слишком много символов\n");
	else
		buf[bufp++] = с;
}