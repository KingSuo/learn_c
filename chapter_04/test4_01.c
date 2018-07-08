#include <stdio.h>
#include <string.h>

#define MAXLENGTH 50

int getline2(char s[]);
int grep(char s[], char v[]);

int main(int argc, char const *argv[])
{
	char s[MAXLENGTH];
	char v[] = "char";
	printf("%d\n", grep(s, v));

	return 0;
}

int getline2(char s[]) {
	char c;
	int i = 0;
	while ((c = getchar()) != '\n' && c != EOF) {
		s[i++] = c;
	}
	s[i] = '\0';
	if (c == EOF) {
		return -1;
	}else
		return i;
}

int grep(char s[], char v[]) {
	int len;
	int i, j, k;
	int num = 0;
	while ((len = getline2(s)) >= 0) {
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
