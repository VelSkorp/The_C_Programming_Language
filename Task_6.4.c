#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXWORD 100

struct tnode
{
	char* word;
	int count;
	struct tnode* left;
	struct tnode* right;
};

struct numwordnode
{
	int number;
	struct words* wordslist;
	struct numwordnode* left;
	struct numwordnode* right;
};

struct words
{
	char* word;
	struct words* nextword;
};

struct tnode* addtree(struct tnode*, char*);
struct numwordnode* addnumtree(struct numwordnode*, int, char*);
struct numwordnode* traverse(const struct tnode*, struct numwordnode*);
struct words* addwordtolist(struct words*, char*);
void printwords(const struct words*, const int);
void treeprint(const struct numwordnode*);
int getword(char*, int);

main(int argc, char* argv[])
{
	char word[MAXWORD];
	struct tnode* root = NULL;
	struct numwordnode* numwordroot = NULL;

	while (getword(word, MAXWORD) != EOF)
	{
		if (isalpha(word[0]))
		{
			root = addtree(root, word);
		}
	}

	numwordroot = traverse(root, numwordroot);

	printf("Words and their frequencies:\n");

	treeprint(numwordroot);

	return 0;
}

struct tnode* talloc(void);
struct numwordnode* numwordalloc(void);
struct words* wordsalloc(void);
char* mstrdup(char*);

struct tnode* addtree(struct tnode* p, char* w)
{
	int cond;

	if (p == NULL)
	{
		p = talloc();
		p->word = mstrdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->count++;
	}
	else if (cond < 0)
	{
		p->left = addtree(p->left, w);
	}
	else
	{
		p->right = addtree(p->right, w);
	}

	return p;
}

struct numwordnode* addnumtree(struct numwordnode* p, int count, char* w)
{
	if (p == NULL)
	{
		p = numwordalloc();
		p->number = count;
		p->wordslist = p->left = p->right = NULL;
		p->wordslist = addwordtolist(p->wordslist, w);
		
	}
	else if (count < p->number)
	{
		p->left = addnumtree(p->left, count, w);
	}
	else
	{
		p->right = addnumtree(p->right, count, w);
	}

	return p;
}

struct words* addwordtolist(struct words* list, char* w)
{
	if (list == NULL)
	{
		list = wordsalloc();
		list->word = mstrdup(w);
		list->nextword = NULL;
	}
	else
	{
		list->nextword = addwordtolist(list->nextword, w);
	}

	return list;
}

void treeprint(const struct numwordnode* p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printwords(p->wordslist, p->number);
		treeprint(p->right);
	}
}

void printwords(const struct words* w, const int count)
{
	if (w != NULL)
	{
		printf("%d %s\n", count, w->word);
		w = w->nextword;
	}
}

struct numwordnode* traverse(const struct tnode* p, struct numwordnode* q)
{
	if (p != NULL)
	{
		q = traverse(p->left, q);
		q = addnumtree(q, p->count, p->word);
		q = traverse(p->right, q);
	}
	return q;
}

struct tnode* talloc(void)
{
	return (struct tnode*)malloc(sizeof(struct tnode));
}

struct numwordnode* numwordalloc(void)
{
	return (struct numwordnode*)malloc(sizeof(struct numwordnode));
}

struct words* wordsalloc(void)
{
	return (struct words*)malloc(sizeof(struct words));
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

int getword(char* word, int lim)
{
	int c, t;
	char* w = word;

	int getch(void);
	void ungetch(int);

	while (isspace(c = getch()))
		;

	if (c != EOF)
	{
		*w++ = c;
	}

	if (!isalpha(c))
	{
		if (c == '\"')
		{
			for (c = getch(); c != '\"'; c = getch())
				;
		}
		else if (c == '#')
		{
			for (c = getch(); c != '\n'; c = getch())
				;
		}
		else if (c == '/')
		{
			if ((c = getch()) == '/')
			{
				for (c = getch(); c != '\n'; c = getch())
					;
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
		else
		{
			for (; !isspace(c) && c != EOF; c = getch())
				;
		}

		if (c != '\"' && c != '\n' && c != '/')
		{
			ungetch(c);
		}

		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
	{
		if (!isalnum(*w = getch()))
		{
			if (!isspace(*w))
			{
				ungetch(*w);
				return *w;
			}
			else
			{
				ungetch(*w);
				break;
			}
		}
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