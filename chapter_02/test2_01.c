#include <stdio.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
	/*signed types*/
	printf("signed char min = %d\n", SCHAR_MIN);
	printf("signed char max = %d\n", SCHAR_MAX);
	printf("signed short min = %d\n", SHRT_MIN);
	printf("signed short max = %d\n", SHRT_MAX);
	printf("signed int min = %d\n", INT_MIN);
	printf("signed int max = %d\n", INT_MAX);
	printf("signed long min = %ld\n", LONG_MIN);
	printf("signed long max = %ld\n", LONG_MAX);

	/*unsigned types*/
	printf("unsigned char max = %d\n", UCHAR_MAX);
	printf("unsigned short max = %d\n", USHRT_MAX);
	printf("unsigned int max = %d\n", UINT_MAX);
	printf("unsigned long max = %ld\n", ULONG_MAX);


	return 0;
}