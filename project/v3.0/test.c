#include <stdio.h>
#include <pthread.h>

#define MAX_THREAD_NUM 5

int subthreads_num = 5;
int created_num = 0;
int created_list[MAX_THREAD_NUM];
pthread_t subthread_ids[MAX_THREAD_NUM];

void thread_create_subthread(void *arg);
void thread_print(void *arg);

int main(int argc, char const *argv[])
{
	pthread_t create_subthread_id;

	if (pthread_create(&create_subthread_id, NULL, thread_create_subthread, NULL)) {
		perror("Create create_subthread error!");
		return 0;
	}
	sleep(1);
	printf("Main func!\n");
	
	return 0;
}

void thread_create_subthread(void *arg) {
	extern int subthreads_num;
	extern int created_num;
	extern int created_list[MAX_THREAD_NUM];
	extern pthread_t subthread_ids[MAX_THREAD_NUM];

	while (1) {
		if (created_num < subthreads_num) {
			created_list[created_num] = created_num;
			if (pthread_create(&subthread_ids[created_num], NULL, thread_print, &created_list[created_num])) {
				perror("Create subthread_id error!")
				return 0;
			}else {
				printf("Create subthread %d OK!\n", created_num);
			}
			created_num++;
		}
		if (created_num >= subthreads_num) {
			break;
		}
	}
}

void thread_print(void *arg) {
	int* i = (int*) arg;
	printf("%d\n", *i);
}