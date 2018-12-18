/* https://www.binarytides.com/server-client-example-c-sockets-linux */

/*
 C socket server example
 */

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include <json-c/json.h>

int main(int argc, char *argv[]) {
	enum json_type type;
	int socket_desc, client_sock, c, read_size, connType;
	struct sockaddr_in server, client;
	char client_message[2000];
	char *return_message = "Got it\n";

	if (argc > 1)
		connType = atoi(argv[1]);
	else
		connType = SOCK_STREAM;

	//Create socket
	// connType 1: TCP/STREAM  connType 2: UDP/DGRAM
	socket_desc = socket(AF_INET, connType, 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *) &client,
			(socklen_t*) &c);
	if (client_sock < 0) {
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");

	//Receive a message from client
	while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {

		// process json information
		json_object * jobj = json_tokener_parse(client_message);

		json_object_object_foreach(jobj, key, val) {
			printf("key: %s\n",key);

			printf("type: ");
			type = json_object_get_type(val);

			switch (type) {
			case json_type_null:
				printf("json_type_null\n");
				break;
			case json_type_boolean:
				printf("json_type_boolean\n");
				break;
			case json_type_double:
				printf("json_type_double\n");
				break;
			case json_type_int:
				printf("json_type_int: %d\n",json_object_get_int(val));
				break;
			case json_type_object:
				printf("json_type_object\n");
				break;
			case json_type_array:
				printf("json_type_array\n");
				break;
			case json_type_string:
				printf("json_type_string: %s\n",json_object_get_string(val));
				break;
			}

		}

		//Send the message back to client
		write(client_sock, return_message, strlen(return_message));
	}

	if (read_size == 0) {
		puts("Client disconnected");
		fflush(stdout);
	} else if (read_size == -1) {
		perror("recv failed");
	}

	return 0;
}


