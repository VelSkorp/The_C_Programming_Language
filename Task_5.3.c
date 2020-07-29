#include <stdio.h>

#define MAXLEN 1000

void strcat(char*, char*);

main()
{
	char s[MAXLEN] = "hello ";
	char t[MAXLEN] = "world!";

	strcat(s, t);

	printf("%s\n", s);
}

void strcat(char* s, char* t)
{
	while (*s != '\0')
		s++;

	while (*s++ = *t++)
		;
}