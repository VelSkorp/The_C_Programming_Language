#include <stdio.h>
#include <limits.h>
#include <float.h>

main() 
{
	printf("char\t\tfrom %d to %d\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char\t      %d\n", UCHAR_MAX);
	printf("short\t\tfrom %d to %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short\t      %d\n", USHRT_MAX);
	printf("int\t\tfrom %d to %d\n", INT_MIN, INT_MAX);
	printf("unsigned int\t      %ul\n", UINT_MAX);
	printf("long\t\tfrom %d to %d\n", LONG_MIN, LONG_MAX);
	printf("unsigned long\t      %ul\n", ULONG_MAX);
	printf("long long\tfrom %lld to %lld\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long    %llu\n", ULLONG_MAX);
	printf("--------------------------------------------------\n");
	printf("float\t\tfrom %e to %e\n", FLT_MIN, FLT_MAX);
	printf("double\t\tfrom %e to %e\n", DBL_MIN, DBL_MAX);
}