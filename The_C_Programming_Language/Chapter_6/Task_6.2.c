#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXWORD 100
#define DEFAULT_COMP_LEN 6

struct tnode 
{
	char* word;
	int count;
	struct tnode* left;
	struct tnode* right;
};

struct simroot
{
	struct simword* firstword;
	struct simword* nextroot;
};

struct simword
{
	char* word;
	int count;
	struct simword* nextword;
};

struct tnode* addtree(struct tnode*, char*);
void treeprint(struct tnode*);
int getword(char*, int);
struct simroot* addroot(struct simroot*, struct tnode*, int);
struct simroot* parse(struct tnode*, int);
void printlist(struct simroot*, int);
void printwords(struct simword*);

main(int argc, char* argv[])
{
	int len;
	char word[MAXWORD];
	struct tnode* root = NULL;
	struct simroot* listroot = NULL;

	while (getword(word, MAXWORD) != 'x')
	{
		if (isalpha(word[0]))
		{
			root = addtree(root, word);
		}
	}

	if (argc == 1)
	{
		len = DEFAULT_COMP_LEN;
	}
	else if (argc == 3)
	{
		len = atoi(argv[1]);
	}
	else
	{
		printf("Incorrect number of arguments.\n");
		return 1;
	}

	listroot = parse(root, len);
	treeprint(root);
	printf("\nDuplicate list:\n\n");
	printlist(listroot, len);

	return 0;
}

struct simroot* parse(struct tnode* node, int len)
{
	struct tnode* temp;
	int this_len;
	static struct simroot* root = NULL;

	if (node == NULL)
	{
		return NULL;
	}

	this_len = strlen(node->word);

	parse(node->left, len);

	temp = node->left;

	if (temp != NULL)
	{
		while (temp->right != NULL)
		{
			temp = temp->right;
		}

		if (this_len >= len && strcmp(temp->word, node->word, len) == 0)
		{
			root = addroot(root, temp, len);
			addroot(root, node, len);
		}
	}

	temp = node->right;

	if (temp != NULL)
	{
		while (temp->left != NULL)
		{
			temp = temp->left;
		}

		if (this_len >= len && strcmp(temp->word, node->word, len) == 0)
		{
			root = addroot(root, node, len);
			addroot(root, temp, len);
		}
	}

	parse(node->right, len);
	return root;
}

void printlist(struct simroot* p, int len)
{
	if (p == NULL)
	{
		return;
	}

	for (int i = 0; i < len; i++)
	{
		putchar(p->firstword->word[i]);
	}

	putchar('\n');
	printwords(p->firstword);
	printlist(p->nextroot, len);
}

void printwords(struct simword* p)
{
	printf("  %4d %s\n", p->count, p->word);
	if (p->nextword != NULL)
	{
		printwords(p->nextword);
	}
}

struct tnode* talloc(void);
char* mstrdup(char*);
struct simword* walloc(struct simword*, struct tnode*);
void addword(struct simword*, struct tnode*);

struct simroot* addroot(struct simroot* p, struct tnode* n, int len)
{
	if (p == NULL)
	{
		p = (struct simroot*) malloc(sizeof(struct simroot));
		p->nextroot = NULL;
		p->firstword = walloc(p->firstword, n);
	}
	else if (strcmp(p->firstword->word, n->word, len) == 0)
	{
		addword(p->firstword, n);
	}
	else
	{
		p->nextroot = addroot(p->nextroot, n, len);
	}
	return p;
}

void addword(struct simword* p, struct tnode* n)
{
	if (strcmp(p->word, n->word) == 0)
	{
		return;
	}
	
	if (p->nextword == NULL)
	{
		p->nextword = walloc(p->nextword, n);
	}
	else
	{
		addword(p->nextword, n);
	}
}

struct simword* walloc(struct simword* p, struct tnode* n)
{
	p = (struct simword*)malloc(sizeof(struct simword));
	
	if (p != NULL)
	{
		p->word = n->word;
		p->count = n->count;
		p->nextword = NULL;
	}

	return p;
}

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

void treeprint(struct tnode* p)
{
	if (p != NULL)
	{
		treeprint(p->left); 
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode* talloc(void)
{
	return (struct tnode*)malloc(sizeof(struct tnode));
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