#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

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
	struct nlist* table[] = {
			(install("key", "value")),
			(install("key1", "value1")),
			(install("key2", "value2")),
			(install("key3", "value3"))
	};

	for (int i = 0; i < 4; i++)
	{
		printf("%s->%s\n", table[i]->name, table[i]->defn);
	}

	undef("key");
	undef("key3");

	struct nlist* result;

	char* keys[] = {
			"key",
			"key1",
			"key2",
			"key3"
	};

	for (int i = 0; i < 4; i++)
	{
		if ((result = lookup(keys[i])) == NULL)
		{
			printf("\nkey not found");
		}
		else
		{
			printf("\n%s->%s", result->name, result->defn);
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