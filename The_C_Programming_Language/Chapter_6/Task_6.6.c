#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 1000

unsigned hash(char*);
struct nlist* lookup(char*);
struct nlist* install(char*, char*);
struct nlist* undef(char*);
char* mstrdup(char*);

struct nlist
{
	struct nlist* next;
	char* name;
	char* defn;
};

static struct nlist* hashtab[HASHSIZE];

main()
{
	char word[MAXWORD], key[MAXWORD], value[MAXWORD];
	struct nlist* result;
	
	while (getword(word, MAXWORD) != EOF)
	{
		if (strcmp(word, "#define") == 0)
		{
			getword(key, MAXWORD);
			getword(value, MAXWORD);
			install(key, value);
			result = lookup(key);
			printf("%s->%s\n", result->name, result->defn);
		}
	}

	return 0;
}

unsigned hash(char* s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
	{
		hashval = *s + 31 * hashval;
	}

	return hashval & HASHSIZE;
}

struct nlist* lookup(char* s)
{
	struct nlist* np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	{
		if (strcmp(s, np->name) == 0)
		{
			return np;
		}
	}
	return NULL;
}

struct nlist* install(char* name, char* defn)
{
	struct nlist* np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL)
	{
		np = (struct nlist*)malloc(sizeof(*np));

		if (np == NULL || (np->name = mstrdup(name)) == NULL)
		{
			return NULL;
		}

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
	{
		free((void*)np->defn);
	}

	if ((np->defn = mstrdup(defn)) == NULL)
	{
		return NULL;
	}
	return np;
}

char* mstrdup(char* s)
{
	char* p = (char*)malloc(strlen(s) + 1);

	if (p != NULL)
	{
		strcpy(p, s);
	}

	return p;
}

struct nlist* undef(char* name)
{
	struct nlist* np = lookup(name);

	if (np == NULL)
	{
		return NULL;
	}
	else
	{
		if (np->next != NULL)
		{
			np->next = np->next->next;
			np = np->next;
		}
		else
		{
			hashtab[hash(name)] = NULL;
			free((void*)np);
		}
	}
	return np;
}

int getword(char* word, int lim)
{
	int c, t;
	char* w = word;

	int getch(void);
	void ungetch(int);

	while (isspace(c = getch()))
		;

	for (; --lim > 0; w++)
	{
		if (c == '\"')
		{
			for (c = getch(); c != '\"'; c = getch())
				;
		}
		else if (c == '/')
		{
			if ((c = getch()) == '/')
			{
				for (c = getch(); c != '\n'; c = getch())
					;
				break;
			}
			else if (c == '*')
			{
				for (c = getch(), t = getch(); c != '*' && t != '/'; c = getch(), t = getch())
				{
					ungetch(t);
				}
			}
			else
			{
				ungetch(c);
			}
		}
		else if (!isspace(c))
		{
			*w = c;
		}
		else
		{
			break;
		}

		c = getch();
	}

	*w = '\0';
	return word[0];
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