// client : gcc -o c tcp_client.c 
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
	int socket_id;
	struct sockaddr_in socket_server_addr;
	char *buf_send[5] = {"abctrtr", "qwrwq", "mkop", "fresafgsgasd", "quit"};
	char temp_buf[100];
	int n, i;

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

	/* send message to server & receive message from server */
	for (i = 0; i < 5; i++) {
		printf("data send to server: %s\n", buf_send[i]);
		send(socket_id, buf_send[i], 100, 0);
		n = recv(socket_id, temp_buf, 100, 0);
		// printf("data send to server: %s\n", buf_send);
		printf("data receive from server: %s\n", temp_buf);
		if (strncmp(temp_buf, "quit", 4) == 0) {
			printf("Quit Client!\n");
			break;
		}
	}

	close(socket_id);

	return 0;
}