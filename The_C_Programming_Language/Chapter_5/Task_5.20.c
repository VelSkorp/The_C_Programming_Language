#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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
void errmsg(char*);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int prevtoken = NO;

main()
{
	while (gettoken() != EOF)
	{
		strcpy(datatype, token);

		out[0] = '\0';

		dcl();

		if (tokentype != '\n')
		{
			printf("syntax error\n");
		}

		printf("%s; %s %s\n", name, out, datatype);
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
	void parmdcl(void);

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
		if (name[0] == '\0')
		{
			strcpy(name, token);
		}
	}
	else
	{
		prevtoken = YES;
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
	{
		if (type == PARENS)
		{
			strcat(out, " function returning");
		}
		else if (type == '(')
		{
			strcat(out, " function expecting");
			parmdcl();
			strcat(out, " and returning");
		}
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

void errmsg(char* msg)
{
	printf("%s", msg);
	prevtoken = YES;
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

void dclspec(void);
int typespec(void);
int typequal(void);
int compare(char**, char**);

void parmdcl(void)
{
	do
	{
		dclspec();
	} while (tokentype == ',');

	if (tokentype != ')')
	{
		errmsg("missing ) in parameter declaration \n");
	}
}

void dclspec(void)
{
	char temp[MAXTOKEN];

	temp[0] = '\0';
	gettoken();

	do
	{
		if (tokentype != NAME)
		{
			prevtoken = YES;
			dcl();
		}
		else if (typespec() == YES)
		{
			strcat(temp, " ");
			strcat(temp,  token);
			gettoken();
		}
		else if (typequal() == YES)
		{
			strcat(temp, " ");
			strcat(temp, token);
			gettoken();
		}
		else
		{
			errmsg("unknown type in parameter list \n");
		}
	} while (tokentype != ',' && tokentype != ')');

	strcat(out, temp);

	if (tokentype == ',')
	{
		strcat(out, ",");
	}
}

int typespec(void)
{
	static char* type[] =
	{
		"char",
		"int",
		"void"
	};

	char* pt = token;

	if (bsearch(&pt, type, sizeof(type) / sizeof(char*), sizeof(char*), compare) == NULL)
	{
		return NO;
	}
	else
	{
		return YES;
	}
}

int typequal(void)
{
	static char* typeq[] =
	{
		"const",
		"volatile"
	};

	char* pt = token;

	if (bsearch(&pt, typeq, sizeof(typeq) / sizeof(char*), sizeof(char*), compare) == NULL)
	{
		return NO;
	}
	else
	{
		return YES;
	}
}

int compare(char** s, char** t)
{
	return strcmp(*s, *t);
}