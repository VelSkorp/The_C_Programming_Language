#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void minscanf(char* fmt, ...);

main()
{
	void* a;
	int b = 5; //0x00000005
	unsigned short c;

	minscanf("%p", &a);
	printf("%d\n", (int*)a);

	minscanf("%hu", &c);
	printf("%hu\n", c);

	return 0;
}

void minscanf(char* fmt, ...)
{
	va_list ap;
	char* p;
	char format[4] = { '%', ' ', '\0', '\0' };

	int* ival;
	short* sival;
	unsigned* uival;
	long int* lival;
	long double* ldval;
	char * sval;
	void* ptr;
	float* fval;
	double* dval;

	va_start(ap, fmt);

	for (p = fmt; *p; p++)
	{
		if (*p != '%')
		{
			continue;
		}

		switch (*++p)
		{
		case 'd':
		case 'i':
		case 'o':
		case 'x':
			ival = va_arg(ap, int*);
			format[1] = *p;
			scanf(format, ival);
			break;

		case 'p':
			ptr = va_arg(ap, void*);
			scanf("%p", ptr);
			break;

		case 'u':
			uival = va_arg(ap, unsigned int*);
			scanf("%u", uival);
			break;

		case 'c':
		case 's':
			sval = va_arg(ap, char*);
			format[1] = *p;
			scanf(format, sval);
			break;

		case 'f':
		case 'g':
		case 'e':
			fval = va_arg(ap, float*);
			format[1] = *p;
			scanf(format, fval);
			break;

		case 'l':
			format[1] = *p;

			if (*++p == 'f' || *p == 'g' || *p == 'e')
			{
				dval = va_arg(ap, double*);
				format[2] = *p;
				scanf(format, dval);
			}
			else if(*++p == 'd' || *p == 'i' || *p == 'o' || *p == 'u' || *p == 'x')
			{
				lival = va_arg(ap, long*);
				format[2] = *p;
				scanf(format, lival);
			}
			else
			{
				p--;
				continue;
			}
			break;

		case 'L':
			format[1] = *p;

			if (*++p == 'f' || *p == 'g' || *p == 'e')
			{
				ldval = va_arg(ap, long double*);
				format[2] = *p;
				scanf(format, ldval);
			}
			else
			{
				p--;
				continue;
			}
			break;

		case 'h':
			format[1] = *p;

			if (*++p == 'd' || *p == 'i' || *p == 'o'|| *p == 'u'|| *p == 'x')
			{
				sival = va_arg(ap, short*);
				format[2] = *p;
				scanf(format, sival);
			}
			else
			{
				p--;
				continue;
			}
			break;
		}
	}

	va_end(ap);
	return 0;
}