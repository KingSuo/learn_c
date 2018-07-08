#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);

int main(int argc, char const *argv[])
{
	char s[] = "asdfghjkl";
	char t[] = "fgh";
	printf("%d\n", strrindex(s, t));
	return 0;
}

int strrindex(char s[], char t[]) {
	int i, j, k;

	for (i = strlen(s) - 1; i >= strlen(t) - 1; i--) {
		j = strlen(t) - 1;
		for (k = i; j >= 0 && s[k] == t[j]; k--, j--);
		if (j < 0)
			return k;
	}
	return -1;
}