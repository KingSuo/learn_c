#include "stdio.h"

int practice_1_8(){		/*counter space, tab, enter*/
	printf("===========practice 1.8 start===========\n");	
	int c, space_num, tab_num, enter_num;
	c = 0;
	space_num = 0;
	tab_num = 0;
	enter_num = 0;

	while ((c = getchar()) != 'q') {
		if (c == ' ')
			++space_num;
		if (c == '\t')
			++tab_num;
		if (c == '\n')
			++enter_num;
	}
	printf("space tab enter\n");
	printf(" %1d %5d %5d\n", space_num, tab_num, enter_num);
	printf("===========practice 1.8 end===========\n");	

	return 0;	
}

int practice_1_9(){
	printf("===========practice 1.9 start===========\n");	
	int c, space_num;
	space_num = 0;
	while ((c = getchar()) != 'q') {
		if (c != ' ') {
			space_num = 0;
			putchar(c);
		}else {
			if (space_num == 0) {
				putchar(c);
			}
			++space_num;
		}
	}
	printf("===========practice 1.9 end===========\n");	

	return 0;	
}

int practice_1_10(){
	printf("===========practice 1.10 start===========\n");	
	int c;
	c = 0;

	while ((c = getchar()) != 'q') {		
		if (c == '\t') {
			putchar('\\');
			putchar('t');
		}else if (c == '\n') {		
			putchar('\\');
			putchar('n');
		}else if (c == '\b') {
			putchar('\\');
			putchar('b');
		}else {
			putchar(c);
		}
	}
	printf("===========practice 1.10 end===========\n");	

	return 0;	
}

int main(int argc, char const *argv[])
{
	practice_1_8();
	practice_1_9();
	practice_1_10();

	return 0;
}