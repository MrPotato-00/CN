#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

/*
 
notes section:

-> 127.0.0.1 -- local host address
-> any port > 5000 is freely available


*/

int main(){

	char *ip= "127.0.0.1";
	int port= 5566;

	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	
	socklen_t addr_size;
	char buffer[1024]; // this will store the message
	int n;

	server_sock= socket(AF_INET, SOCK_STREAM, 0);   // SOCK_STREAM refers to the TCP server that is to be created
	if(server_sock<0){
		perror("[-] Socket error");
		exit(1);
	}

	printf("[+] Server socket created.\n");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family= AF_INET; // this is the IPV4 connection
	server_addr.sin_port= port;      // this is the port number defined
	server_addr.sin_addr.s_addr= inet_addr(ip);

	// bind them 
	n= bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(n<0){
		perror("[-] Bind error");
		exit(1);
	}

	printf("[+] Bind to the port number: %d\n", port);
	
	listen(server_sock, 1);  // 1 refers to the no of clients that are supposed to be connecting
	printf("listening...\n");


	client_sock= accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
	printf("[+] Client connected.\n");
	//bzero(buffer,1024);
	printf( "Hi, This is server use 420 to exit\n");
	bzero(buffer,1024);
	strcpy(buffer, "Hi, This is server");
	send(client_sock, buffer, sizeof(buffer),0);
		
	while(1){

		bzero(buffer, 1024);
		recv(client_sock, buffer, sizeof(buffer),0);
		printf("Client: %s\n", buffer);

		bzero(buffer, 1024);
		//strcpy(buffer, "Hi, This is the server");
		fgets(buffer, sizeof(buffer), stdin);
		if(strcmp(buffer, "420")==0){
			close(client_sock);
			printf("[+] Client is disconnected");
			break;
		}
		printf("Server: %s\n", buffer);
		send(client_sock, buffer, strlen(buffer), 0);
	}
	//close(client_sock);
	//printf("[+] Client is disconnected.\n\n");
	



	return 0;
}
