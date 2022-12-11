#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{	  	    
	//Read the chosen port number from the commandline.
	int portno = atoi( argv[1] );

	//Create a socket (internet, continuous stream, tcp).
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Create a structure for storing an internet address.
	struct sockaddr_in serv_addr; 

	//Zero-fill the structure.
	bzero( (char *)&serv_addr, sizeof(serv_addr) );

	//Initialize the structure.
	serv_addr.sin_family = AF_INET; //internet domain
	serv_addr.sin_addr.s_addr = INADDR_ANY; //address of the server i.e. the localhost
	serv_addr.sin_port = htons(portno); //host to network conversion of port number to bytes
	
	//Bind the socket to the address containined in the structure. I.e. bind the socket to the localhost
     	bind( sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr) );

	//Listen on our socket, backlog queue (max waiting connections) of 5
	listen(sockfd, 5);

	//Create a structure to store the address details of a client when it connects.
	struct sockaddr_in cli_addr;

	//Get the size of this structure.
	socklen_t clilen = sizeof(cli_addr);

	//Create a buffer and zero-fill
	char buffer[256];
	bzero(buffer, 256);

	//Wait for and then accept incoming connection. Store the details of the client in the structure.
	int newsockfd = accept( sockfd, (struct sockaddr *)&cli_addr, &clilen );

	//Read up to 255 characters from the socket into the buffer. Returns total bytes read.
	int n = read(newsockfd, buffer, 255);
	     
	//Print the message to the console.
	printf("Here is the message: %s\n", buffer);

	//Write a reply to the client.
	write(newsockfd, "I got your message", 18);
	 
	//Close the sockets.
	close(newsockfd);
	close(sockfd);
		
	//Exit
	return 0; 
}
