// server : gcc -o s tcp_server.c 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define EHCO_PORT 8080
#define MAX_CLIENT_NUM 10

int main(int argc, char const *argv[])
{
	int server_socket_id, client_socket_id;
	struct sockaddr socket_server_addr, socket_client_addr;
	char buf_rec[101], *buf_send;
	int len, n;

	/* create socket */
	server_socket_id = socket(AF_IENT, SOCK_STREAM, 0);
	if (server_socket_id == -1) {
		printf("Error to create socket! %d\n", errno);
		return 0;
	}else{
		printf("Create socket successfully! Socket ID: %d\n", server_socket_id);
	}

	/* Set struct of socket_addr */
	bzero(&socket_server_addr, sizeof(socket_server_addr));
	socket_server_addr.sin_family = AF_IENT;
	socket_server_addr.sin_port = htons(EHCO_PORT);
	socket_server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	bzero(&(socket_server_addr.sin_zero), 8);

	/* Bind to port */
	if (bind(server_socket_id, (struct sockaddr*)&socket_server_addr, sizeof(socket_server_addr)) != 0) {
		printf("Error to bind to port! %d\n", errno);
		return 0;
	}else {
		printf("Bind to port successfully!\n");
	}

	/* Listen to port */
	if (listen(server_socket_id, MAX_CLIENT_NUM) == -1) {
		printf("Error to listen to port! %d\n", errno);
		close(server_socket_id);
		return 0;
	}else {
		printf("Listen to port successfully!\n");
	}

	/* Accept to client tcp */
	len = sizeof(socket_client_addr)
	client_socket_id = accept(server_socket_id, (struct socetaddr*)socket_client_addr, &len-);
	if (client_socket_id == -1) {
		printf("Error to accept to client! %d\n", errno);
		close(server_socket_id);
		return 0;
	}else {
		printf("Accept to client successfully!\n");
	}

	/* receive message from client & send some message to client */
	while (n = recv(client_socket_id, buf_rec, 100, 0) > 0) {
		buf_rec[n] = '\0';
		printf("Receive %d datas from client: %s\n", n, buf_rec);
		fflush(stdout);
		buf_send = "receive datas: ";
		strcat(buf_send, (char *)n);
		if (strcmp(buf_rec, "quit", 4) == 0) {
			printf("Quit Server!\n");
			buf_send = "quit"
			break;
		}

		/* send message to client */
		send(client_socket_id, buf_send, 100, 0);
		
	}
	close(client_socket_id);
	close(server_socket_id);

	return 0;
}