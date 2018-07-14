// write.c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int shmid;
	char *shmp;

	shmid = shmget(0x09, sizeof(int), SHM_W|SHM_R|IPC_EXCL);
	if (-1 == shmid)
		perror("create share memory");

	shmp = (char *)shmat(shmid, 0, 0);
	if ((char *)-1 == shmp)
		perror("get share memory address");
	printf("shmp: %p\n", shmp);
	printf("shmid: %d\n", shmid);
	printf("String in share memory: %s\n", shmp);
	shmdt(shmp);

	return 0;
}