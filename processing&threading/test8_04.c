#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void bye1 (void);
void bye2 (void);

int main(int argc, char const *argv[])
{
	pid_t pid1, pid2, pid1_wait, pid2_wait;
	int status1, status2;
	int stop1, stop2;

	pid1 = fork();
	pid2 = fork();

	if (-1 == pid1) {
		printf("Error to create sub process1!\n");
	}else if (pid1 == 0) {
		printf("Child process1!\n");
		stop1 = atexit(bye1);
		if (stop1 != 0) {
			fprintf(stderr, "Cannot set exit function bye1! Error code: %d\n", stop1);
			return EXIT_FAILURE;
		}

	}else {
		printf("Parent process! Child1 ID:%d\n", pid1);
		pid1_wait = waitpid(pid1, &status1, 0);
		printf("Child process1 stop!Child ID:%d\n", pid1);
	}

	if (-1 == pid2) {
		printf("Error to create sub process2!\n");
	}else if (pid2 == 0) {
		printf("Child process2!\n");
		stop2 = atexit(bye2);
		if (stop2 != 0) {
			fprintf(stderr, "Cannot set exit function bye1! Error code: %d\n", stop2);
			return EXIT_FAILURE;
		}
	}else {
		printf("Parent process! Child2 ID:%d\n", pid2);
		pid2_wait = waitpid(pid2, &status2, 0);
		printf("Child process2 stop!Child ID:%d\n", pid2);
	}

	return 0;
}

void bye1 (void) {
	printf("This is bye1().\n");
}

void bye2 (void) {
	printf("This is bye2().\n");
}