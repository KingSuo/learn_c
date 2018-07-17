#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i, i_arr[5];

	for (i = 0; i < 5; i++) {
		i_arr[i] = i;
		printf("%p\n", &i_arr[i]);
	}
	return 0;
}