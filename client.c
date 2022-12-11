#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	//Create a structure for storing the address of	
	struct hostent *server;

	//Get the port number from the console.
	int portno = atoi(argv[2]);

	//Create a new socket in the internet domain using a tcp stream.
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Create a structure for storing the server's address detaisl.
	struct sockaddr_in serv_addr;

	//Zero-fill the structure.   
	bzero( (char *)&serv_addr, sizeof(serv_addr) );

	//Get the server name from teh console.
	server = gethostbyname(argv[1]);

	//Initialize the structure.
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length );
	serv_addr.sin_port = htons(portno);

	//Connect the socket to the server.
	connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr) );

	//Create and zero-fill a buffer.
	char buffer[256];
	bzero(buffer, 256);

	//Prompt user for a message to send.	
	printf("Please enter the message: ");

	//Read the user input to the buffer
    	fgets(buffer, 255, stdin);

	//Write the buffer to the stream.	
	int n = write(sockfd, buffer, strlen(buffer) );

	//Zero-fill the buffer again.
	bzero(buffer,256);

	//Read from teh stream back intot eh buffer.
    	n = read(sockfd, buffer, 255);

	//Print the buffer contents to the console.
   	printf("%s\n",buffer);

	//Close the socket.
	close(sockfd);

	//Quit	
	return 0;
}
