#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i, lim, c;
	char s[100];
	lim	= 10;
	for (i = 0; i < lim; ++i) {
		if ((c = getchar()) != '\n') {
			if (c != EOF)
				s[i] = c;
		}
	}

	return 0;
}