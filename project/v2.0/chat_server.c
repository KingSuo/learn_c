// server : gcc -o s tcp_server.c -lpthread
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

int server_socket_id, client_socket_ids[MAX_CLIENT_NUM];
struct sockaddr_in socket_server_addr, socket_client_addr;
int flag = 1;
int client_num = 0;

pthread_t thread_accept_id, thread_recv_ids[MAX_CLIENT_NUM], thread_send_ids[MAX_CLIENT_NUM], thread_quit_id;

void* thread_accept(void *arg);
void* thread_recv(void *arg);
void* thread_send(void *arg);
void* thread_quit(void *arg);

int main(int argc, char const *argv[])
{
	extern int server_socket_id, client_socket_ids[MAX_CLIENT_NUM];
	extern struct sockaddr_in socket_server_addr, socket_client_addr;
	extern int client_num;
	extern pthread_t thread_accept_id, thread_recv_ids[MAX_CLIENT_NUM], thread_send_ids[MAX_CLIENT_NUM], thread_quit_id;
	pthread_t thread_recv_id, thread_send_id;

	int i, i_arr[MAX_CLIENT_NUM];
	int client_socket_id;

	/* create socket */
	server_socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket_id == -1) {
		printf("Error to create socket! %d\n", errno);
		return 0;
	}else{
		printf("Create socket successfully! Socket ID: %d\n", server_socket_id);
	}

	/* Set struct of socket_addr */
	bzero(&socket_server_addr, sizeof(socket_server_addr));
	socket_server_addr.sin_family = AF_INET;
	socket_server_addr.sin_port = htons(EHCO_PORT);
	socket_server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	bzero(&(socket_server_addr.sin_zero), 8);

	/* Bind to port */
	if (bind(server_socket_id, (struct sockaddr*)&socket_server_addr, sizeof(socket_server_addr)) != 0) {
		printf("Error to bind to port! %d\n", errno);
		return 0;
	}else {
		printf("Bind to port %d successfully!\n", EHCO_PORT);
	}

	/* Listen to port */
	if (listen(server_socket_id, MAX_CLIENT_NUM) == -1) {
		printf("Error to listen to port! %d\n", errno);
		close(server_socket_id);
		return 0;
	}else {
		printf("Listen to port successfully!\n");
	}

	if (pthread_create(&thread_accept_id, NULL, thread_accept, NULL)) {
		perror("Create accept thread error!");
		return 0;
	}

	for (i = 0; i < client_num; i++) {
		thread_recv_id = thread_recv_ids[i];
		i_arr[i] = i;
		if (pthread_create(&thread_recv_id, NULL, thread_recv, &i_arr[i])) {
			perror("Create recv thread error!");
			return 0;
		}	
	}
	
	for (i = 0; i < client_num; i++) {
		thread_send_id = thread_send_ids[i];
		if (pthread_create(&thread_send_id, NULL, thread_send, &i)) {
			perror("Create send thread error!");
			return 0;
		}	
	}
	
	if (pthread_create(&thread_quit_id, NULL, thread_quit, NULL)) {
		perror("Create quit thread error!");
		return 0;
	}

	if (pthread_join(thread_accept_id, NULL)) {
		perror("Wait accept thread error!");
		return 0;
	}
	for (i = 0; i < client_num; i++) {
		thread_recv_id = thread_recv_ids[i];
		if (pthread_join(thread_recv_id, NULL)) {
			perror("Wait recv thread error!");
			return 0;
		}else {
			printf("Join thread %lu OK!\n", thread_recv_id);
		}
	}
	for (i = 0; i < client_num; i++) {
		thread_send_id = thread_send_ids[i];
		if (pthread_join(thread_send_id, NULL)) {
			perror("Wait send thread error!");
			return 0;
		}	
	}
	
	if (pthread_join(thread_quit_id, NULL)) {
		perror("Wait quit thread error!");
		return 0;
	}

	pthread_cancel(thread_quit_id);

	for (i = 0; i < client_num; i++) {
		client_socket_id = client_socket_ids[i];
		if (client_socket_id != -1 && client_socket_id != 0) {
			close(client_socket_id);
		}
	}
	close(server_socket_id);

	return 0;
}
	
void* thread_accept(void *arg) {		// Accept to client tcp 
	extern int client_socket_ids[MAX_CLIENT_NUM];
	extern int server_socket_id;
	extern struct sockaddr_in socket_client_addr;
	extern int client_num;

	int i, client_socket_id;
	socklen_t len;
	len = sizeof(socket_client_addr);

	while(1) {
		client_socket_id = accept(server_socket_id, (struct sockaddr*)&socket_client_addr, &len);
		if (client_socket_id == -1) {
			printf("Error to accept to client! %d\n", errno);
			close(server_socket_id);
			return 0;
		}else {
			printf("Accept to client successfully! Client ID:%d\n", client_socket_id);
			if (client_num == 0) {
				client_socket_ids[0] = client_socket_id;
				client_num = 1;
			}
			for(i = 0;i < client_num;i++) {
				if (client_socket_ids[i] == client_socket_id) {
					break;
				}
			}
			if (i == client_num) {
				client_socket_ids[client_num] = client_socket_id;
				client_num++;
				if (client_num > MAX_CLIENT_NUM) {
					perror("Cannot connect more client!");
					break;
				}
			}
		}
	}
}
	
void* thread_recv(void *arg) {	// receive message from client
	extern int client_socket_ids[MAX_CLIENT_NUM];
	extern int client_num;
	int* i = (int*)arg;
	int n, j, k; 
	int client_socket_id = client_socket_ids[*i];
	char buf_rec[101];

	while (1) {
		if (client_socket_id != -1) {
			n = recv(client_socket_id, buf_rec, 100, 0);
			if (n > 0) {
				printf("Client %d: %s\n", client_socket_id, buf_rec);
				
				if (strncmp(buf_rec, "quit", 4) == 0) {
					printf("Client %d quit!\n", client_socket_id);
					client_socket_ids[*i] = -1;
				}	
			}	
		}else {
			perror("Error for connection to client!");
		}
		for (k = 0; k < client_num; k++) {
			if (client_socket_ids[k] == -1) {
				for (j = client_num - 1; j > k; j--) {
					if (client_socket_ids[j] != -1) {
						client_socket_ids[k] = client_socket_ids[j];
						client_num--;
						break;
					}else {
						client_num--;
					}
				}
				if (k == 0 && client_num == 1) {
					client_num = 0;
				}
			}
		}
	}
}

void* thread_send(void *arg) {	// send message to client
	extern int client_socket_ids[MAX_CLIENT_NUM];
	extern int server_socket_id;
	extern int flag;
	int *i = (int*)arg;
	int client_socket_id = client_socket_ids[*i];
	char send_msg[101];

	while(1) {
		scanf("%s[^\n]", send_msg);
		if (client_socket_id != -1 && client_socket_id != 0) {
			send(client_socket_id, send_msg, 100, 0);
			printf("Server %d: %s\n", server_socket_id, send_msg);
			if (strncmp(send_msg, "quit", 4) == 0) {
				flag = 0;
				break;
			}
		}else {
			printf("No client connected!\n");
		}

		if (strncmp(send_msg, "quit", 4) == 0) {
			flag = 0;
			break;	
		}				
	}
}

void* thread_quit(void *arg) {	//quit thread
	extern int flag;
	extern int client_num;
	extern pthread_t thread_accept_id, thread_recv_ids[MAX_CLIENT_NUM], thread_send_ids[MAX_CLIENT_NUM];
	pthread_t thread_recv_id, thread_send_id;
	int i;

	while(1) {
		if (!flag) {
			for (i = 0; i < client_num; i++) {
				thread_recv_id = thread_recv_ids[i];
				thread_send_id = thread_send_ids[i];
				printf("Cancel accept thread!\n");
				pthread_cancel(thread_accept_id);
				printf("Cancel recv thread!\n");
				pthread_cancel(thread_recv_id);
				printf("Cancel send thread!\n");
				pthread_cancel(thread_send_id);
			}
			break;	
		}
	}
}