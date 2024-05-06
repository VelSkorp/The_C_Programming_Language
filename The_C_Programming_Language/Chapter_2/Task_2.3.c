#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAXLINE 1000
#define HEX 16

int htol(const char* str);

main() 
{
	char s[MAXLINE];

	gets(s);

	int res = htol(s);

	if (res == -1)
	{
		printf("this string is not hex digit (format 0xFFF)");
	}
	else
	{
		printf("%d\n", res);
	}
}

int htol(const char* str) 
{
	if (str[0] != 0 && tolower(str[1]) != 'x')
	{
		return -1;
	}

	int len = strlen(str) - 1;
	int index = 0;
	int c = 0;
	int result = 0;

	for (int i = len; i > 1; i--)
	{
		switch (toupper(str[i]))
		{

		case 'A':
			c = 10;
			break;

		case 'B':
			c = 11;
			break;

		case 'C':
			c = 12;
			break;

		case 'D':
			c = 13;
			break;

		case 'E':
			c = 14;
			break;

		case 'F':
			c = 15;
			break;

		default:
			if (isdigit(str[i]))
			{
				c = str[i] - '0';
			}
			break;
		}

		result += c * pow(HEX, index++);
	}

	return result;
}