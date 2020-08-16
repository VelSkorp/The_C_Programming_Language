#include <stdio.h>
#include <string.h>

int isupper1(int);
int isupper2(int);

main() 
{
	int c = getchar();

	isupper1(c) ? printf("upper\n") : printf("lower\n");
	isupper2(c) ? printf("upper\n") : printf("lower\n");

	return 0;
}

int isupper1(int c)
{
	return c >= 'A' && c <= 'Z';
}

int isupper2(int c)
{
	return strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL;
}