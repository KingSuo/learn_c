#include "stdio.h"

int func_4 (){
	int c, nl;
	nl = 0;

	while ((c = getchar()) != 'q') {
		if (c == '\n')
			nl++;	
	}
	printf("%d\n", nl);
	return 0;
}

int main(int argc, char const *argv[])
{
	func_4();
	return 0;
}