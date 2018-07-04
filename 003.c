#include <stdio.h>

int main(int argc, char const *argv[])
{
	// int c;
	// long nc;
	// nc = 0;
	// while ((c = getchar()) != EOF) {
	// 	putchar(c);
	// 	++nc;
	// }
	// printf("%ld\n", nc);

	double nc;
	for (nc = 0; getchar() != 'q'; ++nc)
		;
	printf("%.0f\n", nc);

	return 0;
}