// client : gcc -o c tcp_client.c -lpthread
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define EHCO_PORT 8080
#define MAX_CLIENT_NUM 10

int socket_id, flag = 1;
pthread_t thread_recv_id, thread_send_id, thread_quit_id;

void* thread_recv(void *arg);
void* thread_send(void *arg);
void* thread_quit(void *arg);

int main(int argc, char const *argv[])
{
	extern int socket_id;
	struct sockaddr_in socket_server_addr;

	/* create socket */
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_id == -1) {
		printf("Error to create socket! %d\n", errno);
		return 0;
	}else{
		printf("Create socket successfully! Socket ID: %d\n", socket_id);
	}

	/* Set struct of socket_addr */
	bzero(&socket_server_addr, sizeof(socket_server_addr));
	socket_server_addr.sin_family = AF_INET;
	socket_server_addr.sin_port = htons(EHCO_PORT);
	socket_server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	bzero(&(socket_server_addr.sin_zero), 8);

	/* connect to server */
	if (connect(socket_id, (struct sockaddr*)&socket_server_addr, sizeof(socket_server_addr)) == -1) {
		perror("Connect to server error!");
		close(socket_id);
		return 0;
	}else {
		printf("Connect to server successfully\n");
	}


	/* Create threads */
	if (pthread_create(&thread_recv_id, NULL, thread_recv, NULL)) {
		perror("Create recv thread error!");
		return 0;
	}

	if (pthread_create(&thread_send_id, NULL, thread_send, NULL)) {
		perror("Create send thread error!");
		return 0;
	}

	if (pthread_create(&thread_quit_id, NULL, thread_quit, NULL)) {
		perror("Create quit thread error!");
		return 0;
	}
	/* Wait for threads */
	if (pthread_join(thread_recv_id, NULL)) {
		perror("Wait recv thread error!");
		return 0;
	}
	if (pthread_join(thread_send_id, NULL)) {
		perror("Wait send thread error!");
		return 0;
	}
	if (pthread_join(thread_quit_id, NULL)) {
		perror("Wait quit thread error!");
		return 0;
	}

	pthread_cancel(thread_quit_id);

	close(socket_id);

	return 0;
}

void* thread_recv(void *arg) {	// receive message from client
	int n; 
	char buf_rec[101];
	extern int flag;
	extern int socket_id;
	while (1) {
		n = recv(socket_id, buf_rec, 100, 0);
		if (n > 0) {
			printf("Server %d: %s\n", socket_id, buf_rec);
			
			if (strncmp(buf_rec, "quit", 4) == 0) {
				printf("Server %d quit!\n", socket_id);
				flag = 0;
				break;
			}	
		}
	}
}

void* thread_send(void *arg) {	// send message to client
	extern int socket_id;
	extern int flag;
	char send_msg[101];

	while(1) {
		scanf("%s[^\n]", send_msg);
		if (socket_id) {
			send(socket_id, send_msg, 100, 0);
			printf("Client %d: %s\n", socket_id, send_msg);
			if (strncmp(send_msg, "quit", 4) == 0) {
				flag = 0;
				break;
			}
		}else {
			printf("No client connected!\n");
		}
	}
}

void* thread_quit(void *arg) {	//quit thread
	extern int flag;
	extern pthread_t thread_recv_id, thread_send_id;

	while(1) {
		if (!flag) {
			printf("Cancel recv thread!\n");
			pthread_cancel(thread_recv_id);
			printf("Cancel send thread!\n");
			pthread_cancel(thread_send_id);
			break;	
		}
	}
}