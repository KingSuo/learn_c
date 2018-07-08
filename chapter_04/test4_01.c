#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXLENGTH 1000

int grep(char s[], char v[]);
int getline(char s[]);

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

int grep(char s[], char v[]) {
	int len;
	int i, j, k;
	int num = 0;
	while ((len = getline(s)) >= 0) {
		for (i = 0; strlen(s) - i >= strlen(v); i++) {
			j = 0;
			if (s[i] == v[j]) {
				for (k = i; s[k] != '\0' && s[k] == v[j]; k++, j++);
			}
			if (j == strlen(v)) {
				++num;
				printf("%s\n", s);
				break;
			}
		}

	}
	return num;
}

int getline(char s[]) {
	char c;
	int i = 0;
	while ((c = getchar()) != '\n') {
		s[i++] = c;
	}
	s[i++] = c;
	s[i] = '\0';
	return (i - 1)
}