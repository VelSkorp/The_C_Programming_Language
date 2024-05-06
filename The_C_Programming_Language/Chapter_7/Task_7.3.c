#include <stdio.h>
#include <stdarg.h>

void minprintf(char* fmt, ...);

main()
{
	char* a = "Hello world!";
	minprintf("%s\n", a);
	return 0;
}

void minprintf(char* fmt, ...)
{
	va_list ap;
	char* p, * sval;
	void* ptr;
	int ival;
	unsigned int uival;
	double dval;

	va_start(ap, fmt);

	for (p = fmt; *p; p++)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}

		switch (*++p)
		{
		case 'd':
		case 'i':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;

		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;

		case 'x':
		case 'X':
			uival = va_arg(ap, unsigned int);
			printf("%x", uival);
			break;

		case 'u':
			uival = va_arg(ap, unsigned int);
			printf("%u", uival);
			break;

		case 'c':
			ival = va_arg(ap, int);
			printf("%c", ival);
			break;

		case 's':
			for (sval = va_arg(ap, char*); *sval; sval++)
			{
				putchar(*sval);
			}
			break;

		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;

		case 'e':
		case 'E':
			dval = va_arg(ap, double);
			printf("%e", dval);
			break;

		case 'g':
		case 'G':
			dval = va_arg(ap, double);
			printf("%g", dval);
			break;

		case 'p':
			ptr = va_arg(ap, void*);
			printf("%p", ptr);
			break;

		default:
			putchar(*p);
			break;
		}
	}

	va_end(ap);
	return 0;
}