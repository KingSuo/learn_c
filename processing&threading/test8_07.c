#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void bye(void);

int main(int argc, char const *argv[])
{
	pid_t pid, pid_wait;
	int status, filedes[2];
	char *rbuf, *wbuf;

	if (pipe(filedes)) {
		perror("Create pipe Error!");
		return 0;
	}

	pid = fork();
	if (-1 == pid) {
		perror("Create process Error!");
		return 0;
	}else if (pid == 0) {
		printf("This is Child process!\n");

		close(filedes[1]);
		while(1) {
			read(filedes[0], rbuf, 100);
			if (strcmp(rbuf, "exit\n")) {
				printf("Exit Child process....\n");
				break;
			}else {
				printf("String from parent: %s\n", rbuf);
			}
		}
		atexit(bye);
	}else {
		printf("This is parent process! Child ID: %d\n", pid);
		close(filedes[0]);
		while(1) {
			scanf("%s", wbuf);
			write(filedes[1], wbuf, 100);
			close(filedes[1]);
			if (wbuf == "quit\n") {
				printf("Exit parent process!\n");
				break;
			}
			pid_wait = waitpid(pid, &status, 0);
			printf("Child process %d returned!\n", pid_wait);
		}
	}

	return 0;
}

void bye(void) {
	printf("This is callback function!\n");
}