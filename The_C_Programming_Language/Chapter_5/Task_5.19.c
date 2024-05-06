#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum
{
	NAME, PARENS, BRACKETS
};

enum
{
	NO, YES
};

void dcl(void);
void dirdcl(void);
int gettoken(void);
int nexttoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char out[1000];
int prevtoken = NO;

main()
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) 
	{
		strcpy(out, token);

		while ((type = gettoken()) != '\n')
		{
			if (type == PARENS || type == BRACKETS)
			{
				strcat(out, token);
			}
			else if (type == '*')
			{
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
				{
					sprintf(temp, "(*%s)", out);
				}
				else
				{
					sprintf(temp, "*%s", out);
				}
				
				strcpy(out, temp);
			}
			else if (type == NAME)
			{
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
			{
				printf("invalid input at %s \n", token);
			}
		}

		printf("%s\n", out);
	}

	return 0;
}

void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*';)
	{
		ns++;
	}

	dirdcl();

	while (ns-- > 0)
	{
		strcat(out, " pointer to");
	}
}

void dirdcl(void)
{
	int type;

	if (tokentype == '(')
	{
		dcl();

		if (tokentype != ')')
		{
			printf("error: missing ) \n");
		}
	}
	else if (tokentype == NAME)
	{
		strcpy(name, token);
	}
	else
	{
		printf("error: expected name or (dcl) \n");
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if (type == PARENS)
		{
			strcat(out, " function returning");
		}
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

int gettoken(void)
{
	int c;
	char* p = token;

	int getch(void);
	void ungetch(int);

	if (prevtoken == YES)
	{
		prevtoken = NO;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t')
		;

	if (c == '(')
	{
		if ((c = getchar()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[')
	{
		for (*p++ = c; (*p++ = getch()) != ']';)
			;

		*p = '\0';

		return tokentype = BRACKETS;
	}
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch());)
		{
			*p++ = c;
		}

		*p = '\0';

		ungetch(c);

		return tokentype = NAME;
	}
	else
	{
		return tokentype = c;
	}
}

int nexttoken(void)
{
	int type = gettoken();
	prevtoken = YES;
	return type;
}

#define BUFSIZE 100

int bufp = 0;
char buf[BUFSIZE];

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int ñ)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters\n");
	}
	else
	{
		buf[bufp++] = ñ;
	}
}