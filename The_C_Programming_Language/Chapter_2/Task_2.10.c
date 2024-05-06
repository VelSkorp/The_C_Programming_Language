#include <stdio.h>
#include <ctype.h>

int lower(int ch);

main()
{
	printf("%c\n", lower('B'));
}

int lower(int ch)
{
	return isupper(ch) ? tolower(ch) : ch;
}